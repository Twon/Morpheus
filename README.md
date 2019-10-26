# Morpheus

[![Build status](https://ci.appveyor.com/api/projects/status/c4fd0kxw0u0wm0t5/branch/master?svg=true)](https://ci.appveyor.com/project/Twon/morpheus/branch/master)
![MIT](https://img.shields.io/badge/license-MIT-blue.svg)

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