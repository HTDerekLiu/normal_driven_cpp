#include "normal_driven_developable_single_iteration.h"

void normal_driven_developable_single_iteration(
	const Eigen::MatrixXi & F,
    Eigen::MatrixXd & U,
    normal_driven_data & data)
{
    using namespace Eigen;
    using namespace std;

    int nV = U.rows();

    if (data.A.size() != F.rows())
        cout << "we need to have developable normals on faces (will have error)\n";

    if (data.tarN.rows() != F.rows())
        developable_normals(U, F, data.tarN, data); 

    // local step
    // MatrixXd RAll(3,F.rows()*3);
    MatrixXd RAll;
    if (data.useScale)
    {   
        fit_rotations_normal_scale(F, U, RAll, data);
    }
    else
    {
        fit_rotations_normal(F, U, RAll, data);
    }
    

    // global step
    MatrixXd Upre = U;
    {
        MatrixXd RAllT = RAll.transpose();
        Map<const VectorXd> Rcol(RAllT.data(), RAllT.size());
        VectorXd Bcol = data.K.transpose() * Rcol;
        for(int dim=0; dim<U.cols(); dim++)
        {
            VectorXd Uc,Bc,bcc;
            Bc = Bcol.block(dim*nV,0,nV,1);
            bcc = data.bc.col(dim);
            min_quad_with_fixed_solve(
                data.solver_data,Bc,bcc,VectorXd(),Uc);
            U.col(dim) = Uc;
        }
    }

    // recompute desired normal
    developable_normals(U, F, data.tarN, data); 

    // print optimization date
    // data.reldV = (U-Upre).cwiseAbs().maxCoeff() / (U-V).cwiseAbs().maxCoeff();
    // cout << "reldV:" << scientific << reldV << ", obj:" << data.objVal << endl;
}