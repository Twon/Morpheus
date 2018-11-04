# Morpheus

[![Build status](https://ci.appveyor.com/api/projects/status/c4fd0kxw0u0wm0t5/branch/master?svg=true)](https://ci.appveyor.com/project/Twon/morpheus/branch/master)

## Build Instructions

```bash
cd <project root>
mkdir build
cd build

conan install ../

cmake -G <generator> <configuration options> ../ 
```