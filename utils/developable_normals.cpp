#include <developable_normals.h>

void developable_normals(
	const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & tarFN,
  normal_driven_data & data)
{
  using namespace std;
  using namespace Eigen;

  // get vertex face adjacency list
  vector<vector<int>> A_VF;
  {
    vector<vector<int>> tmp;
    igl::vertex_triangle_adjacency(V.rows(),F,A_VF,tmp);
  }

  // computer per face normals 
  MatrixXd FN;
  igl::per_face_normals(V,F,FN);

  // compute per face area
  VectorXd FA;
  igl::doublearea(V,F,FA);

  // compute target FN
  tarFN.resize(F.rows(), 3);
  tarFN.setZero();
  for (int ii=0; ii<V.rows(); ii++)
  {
    // VectorXi fIdx(A_VF[ii].data());
    VectorXi fIdx = Map<VectorXi, Eigen::Unaligned>(A_VF[ii].data(), A_VF[ii].size());
    MatrixXd FNi;
    igl::slice(FN,fIdx,1,FNi);

    VectorXd FAi;
    igl::slice(FA,fIdx,FAi);

    // GS process
    Matrix3d A = FNi.transpose() * FAi.asDiagonal() * FNi;
    Matrix3d U, Vt;
    Vector3d S;
    igl::svd3x3(A, U, S, Vt);

    // make sure S(2) is the smallest eVal
    assert(S(2) <= S(1));
    assert(S(2) <= S(0));

    // remove the S(2) component
    {
      Vector3d vec = U.col(2);
      
      VectorXd len = FNi*vec; 
      for (int jj=0; jj<fIdx.size(); jj++)
        FNi.row(jj) -= len(jj) * vec.transpose();
    }
    // if S(1) small, remove the S(1) component
    if (S(1) < data.developable_threshold)
    {
      Vector3d vec = U.col(1);
      VectorXd len = FNi*vec; 
      for (int jj=0; jj<fIdx.size(); jj++)
        FNi.row(jj) -= len(jj) * vec.transpose();
    }

    // set FNi to tarFN
    for (int jj=0; jj<fIdx.size(); jj++)
      tarFN.row(fIdx(jj)) += FNi.row(jj);

  }
  tarFN.rowwise().normalize();
}