# Normal-Driven Stylization

This demo stylizes an input shape according to a style shape. Different from the example of `02_primStyle_UI` which simply snaps to the closest face normals, this method will first deform the style shape to a sphere, and then use this sphere as the mean to transfer normals to the input shape. To make sure the deformation is good, we recommend one to use style shapes that are genus 0, have higher poly counts, and are nicely triangulated. 

You can compile the code via
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j8
```
once it is compiled, you can run `./normalDriven_bin [input.obj] [style.obj]` such as 
```
./normalDriven_bin spot.obj oloid.obj
```
