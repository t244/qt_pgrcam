# qt_pgrcam
Qt GUI tool for Point Grey Research cameras.

## How to build
1. Clone this project on your computer.
2. Make a build directory in the projecto directory.
```
cd qt_pgrcam
mkdir build
```
3. Run cmake. (I've tried on Visual Studio 2015 64bit only)
```
cd build
cmake -G "Visual Studio 14 2015 Win64" ../
```
4. Open the generated VS solution and then build it.
