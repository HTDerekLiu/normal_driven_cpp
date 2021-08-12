#ifndef NORMAL_DRIVEN_PRIM_SINGLE_ITERATION_H
#define NORMAL_DRIVEN_PRIM_SINGLE_ITERATION_H

#include <iostream>
#include <ctime>
#include <vector>
#include <Eigen/Core>

// include libigl functions
#include <igl/columnize.h>
#include <igl/slice.h>
#include <igl/per_face_normals.h>
#include <igl/per_vertex_normals.h>
#include <igl/min_quad_with_fixed.h>

// include cube flow functions
#include <fit_rotations_normal.h>
#include <fit_rotations_normal_scale.h>
#include <normal_driven_data.h>
#include <snap_normals.h>

#include <profc.h>

void normal_driven_prim_single_iteration(
    const Eigen::MatrixXd & V,
    const Eigen::MatrixXi & F,
    Eigen::MatrixXd & U,
    normal_driven_data & data);

void normal_driven_prim_single_iteration(
    const Eigen::MatrixXi & F,
    Eigen::MatrixXd & U,
    normal_driven_data & data);
#endif