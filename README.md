# Morpheus

 [![Build](https://github.com/Twon/Morpheus/actions/workflows/cmake.yml/badge.svg)](https://github.com/Twon/Morpheus/actions)
 [![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/twon/morpheus/master/LICENSE.MIT)
 [![GitHub Issues](https://img.shields.io/github/issues/twon/morpheus.svg)](http://github.com/twon/morpheus/issues)
 [![codecov](https://codecov.io/gh/twon/morpheus/branch/master/graph/badge.svg)](https://codecov.io/gh/twon/morpheus)


=======

## Build Instructions


```bash
cd <project root>
mkdir build
cd build

conan install ../

cmake -G <generator> <configuration options> ../
```

Or if using a multi configuration environment like Visual Studio or XCode (which contain debug and release builds in a single CMake generated build file) then
generate multi configuration CMake settings

```bash
cd <project root>
mkdir build
cd build

conan install ../ -g cmake_multi -s build_type=Release
conan install ../ -g cmake_multi -s build_type=Debug

cmake -G <generator> <configuration options> ../ 
```
