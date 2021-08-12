#ifndef DEVELOPABLE_NORMALS_H
#define DEVELOPABLE_NORMALS_H

#include <iostream>
#include <ctime>
#include <vector>
#include <Eigen/Core>

// include libigl functions
#include <igl/vertex_triangle_adjacency.h>
#include <igl/slice.h>
#include <igl/per_face_normals.h>
#include <igl/svd3x3.h>
#include <igl/doublearea.h>

// include cube flow functions
// #include <fit_rotations_normal.h>
// #include <fit_transformation.h>
#include <normal_driven_data.h>
// #include <cubic_normals.h>
// #include <snap_normals.h>

void developable_normals(
	const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & tarFN,
  normal_driven_data & data);
#endif