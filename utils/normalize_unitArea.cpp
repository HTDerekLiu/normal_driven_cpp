#include "normalize_unitArea.h"

void normalize_unitArea(
	const Eigen::MatrixXi & F,
    Eigen::MatrixXd & V)
{
    using namespace Eigen;
    
    VectorXd dblA;
    igl::doublearea(V,F,dblA);
    double area = 0.5*dblA.sum();
    MatrixXd BC;
    igl::barycenter(V,F,BC);
    RowVector3d centroid(0,0,0);
    for(int i = 0;i<BC.rows();i++)
    {
        centroid += 0.5*dblA(i)/area*BC.row(i);
    }
    V.rowwise() -= centroid;
    V.array() /= sqrt(area);
}