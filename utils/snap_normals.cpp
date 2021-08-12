#include "snap_normals.h"

void snap_normals(
	const Eigen::MatrixXd & tarN,
	const Eigen::MatrixXd & N,
	Eigen::MatrixXd & N_snap)
{
    // snapping normals to the closest normals in tarN axis
    N_snap.resize(N.rows(), N.cols());
    for (int ii=0; ii<N.rows(); ii++)
    {
        // find the closest normal
        int minIdx = -1;
        double minDist = 1e10;
        for (int jj=0; jj<tarN.rows(); jj++)
        {
          double dist = (tarN.row(jj) - N.row(ii)).norm();
          if (dist < minDist)
          {
            minDist = dist;
            minIdx = jj;
          }
        }
        N_snap.row(ii) = tarN.row(minIdx);
    }
}