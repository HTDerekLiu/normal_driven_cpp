# Normal Driven Spherical Shape Analogies (C++)

This is a simple demo code for Normal-Driven Spherical Shape Analogies presented at [SGP 2021](https://sgp2021.github.io) by [Hsueh-Ti Derek Liu](https://www.dgp.toronto.edu/~hsuehtil/) and [Alec Jacobson](https://www.cs.toronto.edu/~jacobson/).

```
@article{Liu21Normal,
  author    = {Hsueh{-}Ti Derek Liu and
               Alec Jacobson},
  title     = {Normal-Driven Spherical Shape Analogies},
  journal   = {Comput. Graph. Forum},
  volume    = {40},
  number    = {5},
  year      = {2021},
}
```

## Installation
To get started, clone this repository recursively
```
git clone --recursive https://github.com/HTDerekLiu/normal_driven_cpp.git
```
If you haven't, please install [cmake](https://cmake.org) and a modern C++ compiler in order to compile the code.

## Layout
Each subfolder contains a stand-alone example that demonstrates some use cases of our code. If you want to compile an example, e.g. `02_primStyle_UI`, you can simply do
```
cd 02_primStyle_UI
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j8
```
If all goes well, you should be able to find and run the executable `./normalDriven_bin` with some input arguments explained in the README file in each subfolder. 

## Contacts
If any issues or questions, please do not hesitate to contact hsuehtil@cs.toronto.edu. 