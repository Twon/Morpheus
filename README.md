# Morpheus

 [![Build](https://github.com/Twon/Morpheus/actions/workflows/cmake.yml/badge.svg)](https://github.com/Twon/Morpheus/actions)
 [![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/twon/morpheus/master/LICENSE.MIT)
 [![GitHub Issues](https://img.shields.io/github/issues/twon/morpheus.svg)](http://github.com/twon/morpheus/issues)
 [![codecov](https://codecov.io/gh/Twon/Morpheus/branch/main/graph/badge.svg?token=1JmtZA8soP)](https://codecov.io/gh/Twon/Morpheus)

![Coverage](https://codecov.io/gh/Twon/Morpheus/branch/main/graphs/sunburst.svg?token=1JmtZA8soP)

## Build Instructions

The build use CMake for build system generation and Conan 2 for dependency management.  Prerequisites for building are:
 - A supported C++ compiler
   * GCC, 11.x and later
   * Clang, 14.x and later
   * MSCV, 2022 and later
 - Python
 - Git

In general you can use your own [Conan profile](https://docs.conan.io/2/reference/commands/profile.html) but the project ships with profiles for all supported configurations. I you use your own profile then ensure that if you are building again libstdc++ with GCC or Clang that you build on the C++11 and onwards version.  To do so insert the following into your Conan profile under the `[settings]` section:

```
compiler.libcxx=libstdc++11
```

However, preferably use one of the pre-installed configurations in `<project root>/.conan/profiles` (which are installed via the `conan config install ./conan` command to the local conan configuration folder ./.conan2 as specified in the ./.conanrc file) as these are tested and known to work.

### Cloning the Repo

To clone the repo use git to clone the repository to your local machine:

```bash
git clone https://github.com/Twon/Morpheus.git
```

### Configuring Conan

To set up Conan for the repository create a repository local virtual environment for Python and [activate the environment (note this step differs for different shells)](https://docs.python.org/3/library/venv.html#how-venvs-work)

```bash
cd <project root>
python3 -m venv .venv               # Create a Python virtual env
source ./.venv/bin/activate         # Activate the virtual env for bash by source.
pip install -r ./requirements.txt   # Install all Python dependencies
conan profile detect --force        # Generate a default configuration with the local machine settings
conan config install ./.conan       # Install supported build profiles from ./.conan to ./conan2
```

### Standard build

Now with the repository cloned and Conan configured building the repository required installing the Conan dependencies and configuring CMake.  Note that since CMake 3.19 there is a new mechanism for sharing common configurations with users of your project called [`presets`](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html), this is now the recommended mechanism for Conan 2, which will generate default presets during the installation stage:

```bash
cd <project root>
```
To enable Mold linker usage for gcc and clang with Linux:
```bash
conan install ./ -pr:h .conan2/profiles/gcc/12/x64-libstdc++11-debug -pr:b .conan2/profiles/gcc/12/x64-libstdc++11-debug --build missing
source build/Debug/generators/conanbuild.sh # Access the environment variables needed to use the Mold linker with gcc and clang
```
To disable Mold linker usage for gcc and clang with Linux:
```bash
conan install ./ -pr:h .conan2/profiles/gcc/12/x64-libstdc++11-debug -pr:b .conan2/profiles/gcc/12/x64-libstdc++11-debug --build missing -o link_with_mold=False
```
Use the preset generated by Conan
```bash
cmake --preset conan-debug
```

Now build via CMake using the build preset generated by Conan. As a debug profile was used during the Conan install step this will create a `Debug` build with full symbolic information.
```bash
cmake --build --preset conan-debug
```

### Multi-Config Build

Multi-config builds allow you to create a build folder containing sub-folders for different build configurations and build them side-by-side. Once again starting with the repository clone and Conan configured run the install stage, but this time we specity the Conan cmake tools use Ninja multi-config to generate `Release, Debug, RelWithDebInfo` configurations.  To generate all 3 configuration we run the `conan-default` preset which configures CMake for these configurations.
```bash
conan install ./ -pr:h .conan2/profiles/msvc/193/x64-release -pr:b .conan2/profiles/msvc/193/x64-release --build missing -c tools.cmake.cmaketoolchain:generator="Ninja Multi-Config"
source build/generators/conanbuild.sh # Access the environment variables needed to use the Mold linker with gcc and clang
cmake --preset conan-default  # The configure stage for multi-config builds is conan-default
```

Now with CMake configured we select the preset conresponding to the configuration we want to build, in this case the `Release` configuration.
```bash
cmake --build --preset conan-release # The build stage for multi-config builds is the conan-<configuration>
```

### Build Documentation

To build documentation we once again ensure we have cloned the repository and have configured Conan.  This time when installing Conan dependencies we specify `-o build_docs=True` so that Conan installs the tools required to build documentation (including Doxygen).
```bash
conan install ./ -pr:h .conan2/profiles/clang/15/x64-libc++-release -pr:b .conan2/profiles/clang/15//x64-libc++-release --build missing -o build_docs=True
cmake --preset conan-release -DMORPHEUS_BUILD_DOCUMENTATION:BOOL=ON # Build with documentation enabled
```

```bash
cmake --build --preset conan-release --target Documentation # Build the Documentation target
```

### Run Code Coverage

To build with code coverage we once again ensure we have cloned the repository and have configured Conan. We can install as a regular build.
```bash
conan install ./ -pr:h .conan2/profiles/gcc/12/x64-libstdc++-debug -pr:b .conan2/profiles/gcc/12/x64-libstdc++-debug
cmake --preset conan-debug -DENABLE_CODE_COVERAGE=1 # Build with code coverage enabled
```

The build is now configured to send code-coverage flags to the compiler when building, so no build the project with coverage collection enabled, run the tests to collect coverage information and then run the coverage targets to generate the required code-coverage reports.
```bash
cmake --build --preset conan-debug                             # Build the project
ctest --preset conan-debug                                     # Run all tests to collect coverage information.
cmake --build --preset conan-debug --target coverage           # Build the coverage stats
cmake --build --preset conan-debug --target coverage-lcov      # Build a html report from the coverage information
cmake --build --preset conan-debug --target coverage-corbetura # Build a Corbertura XML coverage report
```
