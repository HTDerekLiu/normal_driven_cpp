#ifndef TRANSFER_GAUSS_NORMALS_H
#define TRANSFER_GAUSS_NORMALS_H

#include <iostream>
#include <Eigen/Core>

#include <igl/point_mesh_squared_distance.h>
#include <igl/point_simplex_squared_distance.h>

void transfer_gauss_normals(
	const Eigen::MatrixXd & gaussPos,
	const Eigen::MatrixXd & tarN,
	const Eigen::MatrixXd & N,
	Eigen::MatrixXd & N_snap);
#endif