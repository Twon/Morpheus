# Developer Guide

Welcome to the developers guide for the Morpheus Framework.  This guide will detail how you, the developer can build and use the framework to extend existing functionality and use the framework to develop your own applications.

# Overview

The Morpheus Framework is written largely in C++, but does also support other language in places.  For instance some of the other languages used are:
- CMake for build scripts
- Python for Conan
- Objective C/C++ for MacOs component such as the Metal rendering system.

Morpheus has many libraries that it depends upon.  Largely these dependencies are fetched via the Conan 2 package manager. In a few case where libraries are not packaged for Conan then a dependency may be fetched as a Git repo via CMake's FetchContent method.
