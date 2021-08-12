#include "normal_driven_gauss_single_iteration.h"

void normal_driven_gauss_single_iteration(
	const Eigen::MatrixXi & F,
    Eigen::MatrixXd & U,
    normal_driven_data & data)
{
    using namespace Eigen;
    using namespace std;

    int nEle = data.A.size();
    int nV = U.rows();

    if (data.tarN.rows() != nEle)
    {
        if (data.gaussPos.rows() == 0)
        {
            cerr << "desired gaussPos is empty" << endl;
        }
        MatrixXd UN;
        if (nEle == F.rows())
            igl::per_face_normals(U,F,UN);
        else if (nEle == U.rows())
            igl::per_vertex_normals(U,F,UN);
        transfer_gauss_normals(data.gaussPos, data.desiredN, UN, data.tarN); 
    }
    
    // local step
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
        PROFC_NODE("global step")
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
    // normalize_unitArea(F,U);

    // print optimization date
    // data.reldV = (U-Upre).cwiseAbs().maxCoeff() / (U-V).cwiseAbs().maxCoeff();
    // cout << "reldV:" << scientific << reldV << ", obj:" << data.objVal << endl;
}