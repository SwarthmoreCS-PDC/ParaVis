# Quick Build Directions

```
mkdir build
cd build
cmake ..
make -j8
./cudaDemos
```

# Adding a new CUDA Animation

 1. Read directions in `main.cpp`
 2. Perhaps use `UserBufferKernel.*` to model new Animation
 3. Add new source to `CMakeLists.txt` (around line 77)
 4. Include new header in `cudaDemos.cpp`
 5. Create new `Animator` instance
