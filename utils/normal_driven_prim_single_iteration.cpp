#include "normal_driven_prim_single_iteration.h"

void normal_driven_prim_single_iteration(
	const Eigen::MatrixXd & V,
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
        if (data.desiredN.rows() == 0)
        {
            cerr << "desired normal is empty" << endl;
        }
        MatrixXd UN;
        if (nEle == F.rows())
            igl::per_face_normals(U,F,UN);
        else if (nEle == U.rows())
            igl::per_vertex_normals(U,F,UN);
        snap_normals(data.desiredN, UN, data.tarN); 
    }
    
    
    // local step
    MatrixXd RAll;
    {
        PROFC_NODE("local step")
        if (data.useScale)
        {   
            // cout << "use scale \n";
            fit_rotations_normal_scale(F, U, RAll, data);
        }
        else
        {
            // cout << "not use scale \n";
            fit_rotations_normal(F, U, RAll, data);
        }
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

    // recompute desired normal
    {
        PROFC_NODE("snap normals")
        MatrixXd UN;
        if (nEle == F.rows())
            igl::per_face_normals(U,F,UN);
        else if (nEle == U.rows())
            igl::per_vertex_normals(U,F,UN);
        snap_normals(data.desiredN, UN, data.tarN); 
    }

    // print optimization date
    data.reldV = (U-Upre).cwiseAbs().maxCoeff() / (U-V).cwiseAbs().maxCoeff();
    // cout << "reldV:" << scientific << data.reldV << endl;
}

void normal_driven_prim_single_iteration(
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
        if (data.desiredN.rows() == 0)
        {
            cerr << "desired normal is empty" << endl;
        }
        MatrixXd UN;
        if (nEle == F.rows())
            igl::per_face_normals(U,F,UN);
        else if (nEle == U.rows())
            igl::per_vertex_normals(U,F,UN);
        snap_normals(data.desiredN, UN, data.tarN); 
    }
    
    
    // local step
    MatrixXd RAll;
    {
        PROFC_NODE("local step")
        if (data.useScale)
        {   
            // cout << "use scale \n";
            fit_rotations_normal_scale(F, U, RAll, data);
        }
        else
        {
            // cout << "not use scale \n";
            fit_rotations_normal(F, U, RAll, data);
        }
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

    // recompute desired normal
    {
        PROFC_NODE("snap normals")
        MatrixXd UN;
        if (nEle == F.rows())
            igl::per_face_normals(U,F,UN);
        else if (nEle == U.rows())
            igl::per_vertex_normals(U,F,UN);
        snap_normals(data.desiredN, UN, data.tarN); 
    }

    // print optimization date
    // data.reldV = (U-Upre).cwiseAbs().maxCoeff() / (U-V).cwiseAbs().maxCoeff();
    // cout << "reldV:" << scientific << reldV << ", obj:" << data.objVal << endl;
}