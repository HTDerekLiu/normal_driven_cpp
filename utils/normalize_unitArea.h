#ifndef NORMALIZE_UNITAREA_H
#define NORMALIZE_UNITAREA_H

#include <iostream>
#include <Eigen/Core>

#include <igl/doublearea.h>
#include <igl/barycenter.h>

// Inputs:
//   V        a matrix of vertex positions
// Outputs: 
//   V        a matrix of vertex positions (in a unit box)
void normalize_unitArea(
	const Eigen::MatrixXi & F,
	Eigen::MatrixXd & V);
#endif