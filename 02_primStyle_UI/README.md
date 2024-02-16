# Primitive Stylization

This demo stylizes an input shape according to the style of a simple primitive shape. We recommend users to use convex shape with only few distinct face normals (e.g., cube). 

You can compile the code via
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j8
```
once it is compiled, you can run `./normalDriven_bin [input.obj] [style.obj]` such as 
```
./normalDriven_bin spot.obj cube.obj
```
to play with the stylization in the UI.