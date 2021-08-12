#include "localAvgMat.h"
void localAvgMat(
    const Eigen::MatrixXd & V,
    const Eigen::MatrixXi & F, 
    Eigen::SparseMatrix<double> & L)
{
  using namespace std;
  using namespace Eigen;

  L.resize(V.rows(),V.rows());
  L.reserve(10*V.rows());

  MatrixXd edges;
  edges.resize(3,2);
  edges << 
    1,2,
    2,0,
    0,1;
  
  vector<vector<int>> A;
  igl::adjacency_list(F,A);

  vector<Triplet<double> > IJV;
  IJV.reserve(F.rows()*edges.rows()*4);
  for(int i = 0; i < F.rows(); i++)
  {
    // loop over edges of element
    for(int e = 0;e<edges.rows();e++)
    {
      int source = F(i,edges(e,0));
      int dest = F(i,edges(e,1));
      IJV.push_back(Triplet<double>(source,dest,0.5/ A[source].size()));
      IJV.push_back(Triplet<double>(dest,source,0.5/ A[dest].size()));
      // IJV.push_back(Triplet<double>(source,source,-C(i,e)));
      // IJV.push_back(Triplet<double>(dest,dest,-C(i,e)));
    }
  }
  L.setFromTriplets(IJV.begin(),IJV.end());
}