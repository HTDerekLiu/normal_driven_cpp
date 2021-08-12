#include <igl/read_triangle_mesh.h>
#include <igl/writeOBJ.h>

#include <normal_driven_data.h>
#include <normal_driven_precomputation.h>
#include <normal_driven_prim_single_iteration.h>

#include <ctime>
#include <vector>
#include <iostream>
#include <fstream>

#ifndef MESH_PATH
#define MESH_PATH "../../meshes/"
#endif

// to run the code, type ./normalDriven_bin spot.obj cone.obj 2e-4
int main(int argc, char *argv[])
{
	using namespace Eigen;
	using namespace std;

    // load mesh
	MatrixXd V, desiredNormals;
	MatrixXi F;
    double stopReldV;  // stopping criteria for relative displacement
    string meshName, styleMeshName;
	{   
        meshName = argv[1];
        styleMeshName = argv[2];
        stopReldV = stod(argv[3]);
        string meshPath = MESH_PATH + meshName;
		string styleMeshPath = MESH_PATH + styleMeshName;

        // get desired normals (surface normals of the input style shape)
        MatrixXd sV,sN;
        MatrixXi sF,useless1,useless2; 
        igl::read_triangle_mesh(styleMeshPath, sV, sF);
        igl::per_face_normals(sV,sF,sN);
        igl::unique_rows(sN, desiredNormals, useless1, useless2);
        assert(desiredNormals.rows() > 0);

        // read mesh files
		igl::read_triangle_mesh(meshPath, V, F);
        assert(V.rows() > 0);
	}

    // prepare data for stylization
    normal_driven_data data;
    data.useScale = false;
    data.lambda = 1; // weighting for normal term
    data.desiredN = desiredNormals;

    // pin down at least one vertex
    {
        data.bc.resize(1,3);
        data.bc << V.row(F(0,0));

        data.b.resize(1);
        data.b << F(0,0);
    }

    // precomputation 
    int type = 0; // 0: vertex, 1: face
    normal_driven_precomputation(V,F,type,data);

    // primtitive stylization 
    MatrixXd U = V;
    int maxIter = 350;
    for (int iter=0; iter<maxIter; iter++)
    {
        normal_driven_prim_single_iteration(V,F,U,data);
        cout << "iteration: " << iter << ", reldV: " << data.reldV << endl;
        if (data.reldV < stopReldV) break;
    }
    
    // write output mesh
    igl::writeOBJ("../output.obj", U, F);

    return 0;
}