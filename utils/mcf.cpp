#include "mcf.h"
void mcf(
    const Eigen::MatrixXd & V,
    const Eigen::MatrixXi & F, 
    Eigen::MatrixXd & U)
{
  using namespace std;
  using namespace Eigen;

  // parameters
  double min_diff = 1e-9;

  SparseMatrix<double> L;
  igl::cotmatrix(V,F,L);

  U = V;
  MatrixXd Upre;
  SparseMatrix<double> M, S;
  for (int ii = 0; ii < 300; ii++)
  {
    Upre = U;

    // construct linear system
    igl::massmatrix(U,F,igl::MASSMATRIX_TYPE_BARYCENTRIC,M);
    S = (M - 0.001*L);
    SimplicialLLT<SparseMatrix<double > > solver(S);
    assert(solver.info() == Success);
    U = solver.solve(M*U).eval();

    // normalize the mesh
    VectorXd dblA;
    igl::doublearea(U,F,dblA);
    double area = 0.5*dblA.sum();
    MatrixXd BC;
    igl::barycenter(U,F,BC);
    RowVector3d centroid(0,0,0);
    for(int i = 0;i<BC.rows();i++)
    {
      centroid += 0.5*dblA(i)/area*BC.row(i);
    }
    U.rowwise() -= centroid;
    U.array() /= sqrt(area);

    // stopping 
    // cout << ((U-Upre).transpose() * M * (U-Upre)).array().square() << endl;
    MatrixXd difference = ((U-Upre).transpose() * M * (U-Upre)).array().abs();
    if (difference.trace() < min_diff)
      break;
  }

  
}