#ifndef MCF_H
#define MCF_H

#include <Eigen/Dense>
#include <Eigen/Sparse> 

#include <igl/barycenter.h>
#include <igl/cotmatrix.h>
#include <igl/doublearea.h>
#include <igl/massmatrix.h>
#include <iostream>

void mcf(
    const Eigen::MatrixXd & V,
    const Eigen::MatrixXi & F, 
    Eigen::MatrixXd & U);

#endif