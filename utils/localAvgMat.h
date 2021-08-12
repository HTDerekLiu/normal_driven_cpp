#ifndef LOCALAVGMAT_H
#define LOCALAVGMAT_H

#include <Eigen/Dense>
#include <Eigen/Sparse> 
#include <vector> 
#include <igl/adjacency_list.h>

void localAvgMat(
    const Eigen::MatrixXd & V,
    const Eigen::MatrixXi & F, 
    Eigen::SparseMatrix<double> & L);

#endif