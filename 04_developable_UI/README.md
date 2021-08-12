# Developable Surface Approximation

This demo turns an input shape into an approximate developable surface. One can control the number of developable patches by changing the `developability` value in the UI.

You can compile the code via
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j8
```
once it is compiled, you can run `./normalDriven_bin [input.obj]` such as 
```
./normalDriven_bin bunny.obj
```
