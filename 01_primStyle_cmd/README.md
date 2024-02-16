# Primitive Stylization (command line)

This demo stylizes an input shape according to the style of a simple primitive shape. We recommend users to use convex shape with only few distinct face normals (e.g., cube). 

You can compile the code via
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j8
```
once it is compiled, you can run `./normalDriven_bin [input.obj] [style.obj] [stopping criteria]` such as 
```
./normalDriven_bin ../../meshes/spot.obj ../../meshes/cube.obj 2e-4
```
and then you will obtain a stylized `output.obj`.