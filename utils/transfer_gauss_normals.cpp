#include "transfer_gauss_normals.h"

void transfer_gauss_normals(
  const Eigen::MatrixXd & gaussPos,
	const Eigen::MatrixXd & tarN,
	const Eigen::MatrixXd & N,
	Eigen::MatrixXd & N_snap)
{
    // snapping normals (N) to the closest point on the Gauss map
    N_snap.resize(N.rows(), N.cols());
    for (int ii=0; ii<N.rows(); ii++)
    {
        // find the closest normal
        int minIdx = -1;
        double minDist = 1e10;
        for (int jj=0; jj<gaussPos.rows(); jj++)
        {
          double dist = (gaussPos.row(jj) - N.row(ii)).norm();
          if (dist < minDist)
          {
            minDist = dist;
            minIdx = jj;
          }
        }
        N_snap.row(ii) = tarN.row(minIdx);
    }
}