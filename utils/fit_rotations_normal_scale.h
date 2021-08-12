#ifndef FIT_ROTATIONS_NORMAL_SCALE_H
#define FIT_ROTATIONS_NORMAL_SCALE_H

#include <iostream>
#include <Eigen/Core>
#include <Eigen/Sparse>
#include <normal_driven_data.h>
#include <igl/slice.h>
#include <igl/parallel_for.h>
#include <igl/fit_rotations.h>
#include <math.h> 

void fit_rotations_normal_scale(
	const Eigen::MatrixXi & F,
	Eigen::MatrixXd & U,
	Eigen::MatrixXd & RAll,
	normal_driven_data & data);
#endif