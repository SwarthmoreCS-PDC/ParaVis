# QtVis

## A library for visualization of parallel programs

This repo provides a library for visualizing and animating a two dimensional grid of colors through the [DataVis](include/dataVis.h) class. The primary purpose of this library is to provide an easy to use interface to explore parallel computing through data visualization. The `DataVis` class makes it easy to create small derived classes that use various parallel frameworks to update the color grid. The library uses Qt and OpenGL 4.x to animate and visualize the grid as the user updates it, but users do not need to be experts in either Qt or OpenGL to use this library. Currently, the following parallel frameworks are supported:

 * [OpenMP](https://www.openmp.org/resources/tutorials-articles/)
 * [pthreads](https://computing.llnl.gov/tutorials/pthreads/)
 * [CUDA](https://developer.nvidia.com/cuda-zone)

Users can also write single threaded applications for comparison or initial testing.

The installer will attempt to autodetect available libraries, so it is possible to use this library if e.g., you only have pthreads and OpenMP available on your system. While the library will attempt to compile support for as many frameworks as possible, users can focus on a single parallel framework when designing their application, and do not need to understand all of the above parallel frameworks to use this library.

This repo includes some small sample demos, and you can use this repo to extend and write your own demos. However, this code also supports being installed as a library. Under this configuration, a single user could configure, build, and install the library on a network and multiple users can develop parallel applications that use this library using a much more simplified code base. Examples of demos that use and link against this library are available in a separate [qt-demos](https://github.swarthmore.edu/adanner1/qtogl-demos) repo.

# Quick Build Directions

To quickly try out the code samples, try the standard CMake out of source build directions.

```
mkdir build
cd build
cmake ..
make -j8
./cpuDemo
./openMPDemo
./threadDemo
./cudaDemo
```

Not all demos may be available if, for example, CUDA or OpenMP are not supported on your system.

# CUDA Troubleshooting

If you have CUDA installed, but CMake is not finding it, you may want to try specifying the full path to the CUDA compiler when running `cmake`, e.g.,

```
cmake -DCMAKE_CUDA_COMPILER=/usr/local/cuda-9.0/bin/nvcc ../
```

It may also be necessary to install or point cmake to an older version of gcc if CUDA complains your compiler is too new. For example, on Ubuntu 18.04, CUDA 9.0 does not like the default gcc 7.3.0 version, but is OK with gcc 6.4.0, so my full configuration flags for CUDA 9.0 on Ubuntu 18.04 as of August 2018 were

```
cmake -DCMAKE_CUDA_HOST_COMPILER=/usr/bin/gcc-6 -DCMAKE_CUDA_COMPILER=/usr/local/cuda-9.0/bin/nvcc ..
```

# Installing the library system wide

CMake will configure a `make install` target for you during the initial configuration. By default on linux, the install prefix is `/usr/local`, but you can set an alternate prefix. For custom installs, I regularly use [GNU stow](https://www.gnu.org/software/stow/manual/stow.html) for managing the installation/uninstall. You may need root access to perform some of these steps.

```
cmake -DCMAKE_INSTALL_PREFIX=/usr/local/stow/qtvis/ ..
make -j8
make install
cd /usr/local/stow/
sudo stow qtvis
```

# Links

 * [Web Documentation](https://www.cs.swarthmore.edu/~adanner/qtvis/)
 * [Extra Demos](https://github.swarthmore.edu/adanner1/qtogl-demos)
 * [License](License.md)

# References

 * [EduPar18 Materials](https://www.cs.swarthmore.edu/edupar18/)
