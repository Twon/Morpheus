# Morpheus

 [![Build](https://github.com/Twon/Morpheus/actions/workflows/cmake.yml/badge.svg)](https://github.com/Twon/Morpheus/actions)
 [![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/twon/morpheus/master/LICENSE.MIT)
 [![GitHub Issues](https://img.shields.io/github/issues/twon/morpheus.svg)](http://github.com/twon/morpheus/issues)
 [![codecov](https://codecov.io/gh/Twon/Morpheus/branch/main/graph/badge.svg?token=1JmtZA8soP)](https://codecov.io/gh/Twon/Morpheus)

https://codecov.io/gh/Twon/Morpheus/branch/main/graphs/sunburst.svg?token=1JmtZA8soP

## Build Instructions

Linux or MacOS.  See [here](https://github.com/profitviews/heisenberg/blob/main/windows.md) for Windows.

1. Clone project
   ```
   git clone https://github.com/Twon/Morpheus.git
   cd morpheus 
   ```

2. Install Conan
   ```
   python3 -m venv .venv         # Create a Python virtual env
   source ./.venv/bin/activate   # Activate the virtual env
   pip install conan==1.60       # Install conan 1.60 (untill conan 2.0 is stable)
   ```

3. Install Conan Package & Configure CMake 
   ```
   mkdir build
   cd build

   # Possibly create/modify a profile file in ~/.conan/profiles. See https://docs.conan.io/1/reference/profiles.html
   conan install ../ --build missing
   cmake -DCMAKE_BUILD_TYPE=Debug ..
   ```
   
4. Build
   ```bash
   cmake --build .
   ```

This will create (with debugging symbols):



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
