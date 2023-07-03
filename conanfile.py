# The MIT License (MIT)
#
# Copyright (c) 2021 Antony Peacock
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
from conan import ConanFile
from conan.errors import ConanException, ConanInvalidConfiguration
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMake
from conan.tools.files import copy
from conan.tools.scm import Version
from conan.tools.files import load
import re, os.path
import subprocess
import sys

required_conan_version = ">=1.59.0"


def get_cmake_version():
    try:
        out, _ = subprocess.Popen(["cmake", "--version"], stdout=subprocess.PIPE, shell=False).communicate()
        out = out.decode(sys.stdout.encoding)
        version_line = out.split('\n', 1)[0]
        version_str = version_line.rsplit(' ', 1)[-1]
        return Version(version_str)
    except Exception as e:
        raise ConanException("Error retrieving CMake version: '{}'".format(e))

class Morpheus(ConanFile):
    name = "morpheus"
    homepage = "https://github.com/Twon/Morpheus"
    description = "Cross plafrom game engine build using C++23"
    topics = ("game-engine", "rendering-engine")
    license = "MIT"
    url = "https://github.com/Twon/Morpheus"
    settings = "os", "compiler", "build_type", "arch"
    no_copy_source = True
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "tools": [True, False],
        "build_docs": [True, False]
    }
    default_options = {
        "shared": False,
        "fPIC": True,
        "tools": True,
        "build_docs": False
    }
    exports_sources = ["CMakeLists.txt", "LICENSE", "version.txt", "cmake/*", "examples/*" "libraries/*"]
    generators = "cmake_find_package", "cmake_find_package_multi", "virtualenv"
    requires = (
        "boost/1.82.0",
        "catch2/3.1.0", 
        "fmt/10.0.0",
        "glbinding/3.1.0",
        "glew/2.2.0",
        "gtest/1.13.0",
        "magic_enum/0.8.2",
        "ms-gsl/4.0.0",
        "rapidjson/cci.20220822",
        "range-v3/0.12.0",
        "tl-expected/20190710",
        "trompeloeil/42",
        "vulkan-headers/1.3.239"#,
        #"zlib/1.2.12" # xapian-core/1.4.19' requires 'zlib/1.2.12' while 'boost/1.81.0' requires 'zlib/1.2.13'. To fix this conflict you need to override the package 'zlib' in your root package.
    )

    build_requires = (
#        "ccache/4.6",
    )

    def set_version(self):
        content = load(self, os.path.join(os.path.dirname(__file__), "version.txt"))
        version = re.search(r'(\d+\.\d+\.\d+)', content).group(1)
        self.version = version.strip()

    def build_requirements(self):
        # Ensure the package is build against a version of CMake from 3.25 onwards.
        if get_cmake_version() < Version("3.25.0"):
            self.build_requires("cmake/3.25.0")

        if self.options.build_docs:
            self.build_requires("doxygen/1.9.4") # doxygen/1.9.5 will update dependency on zlib/1.2.12 to zlib/1.2.13

    def requirements(self):
        if self.settings.os in ["Macos", "iOS", "tvOS"] and self.settings.compiler == "apple-clang":
            self.requires("moltenvk/1.21.6")

        if self.settings.os in ["Windows"]:
            self.requires("wil/1.0.230411.1")

        if self.settings.compiler != "msvc":
            self.requires("date/3.0.1")

#    @property
#    def _source_subfolder(self):
#        return "source_subfolder"

    @property
    def _minimum_cpp_standard(self):
        return 20

    @property
    def _minimum_compilers_version(self):
        return {
#            "intel-cc": "??"
            "msvc": "16",
            "gcc": "11",
            "clang": "13",
            "apple-clang": "13"
        }

    def configure(self):
        if self.settings.compiler.get_safe("cppstd"):
            check_min_cppstd(self, self._minimum_cpp_standard)
        min_version = self._minimum_compilers_version.get(
            str(self.settings.compiler))
        if not min_version:
            self.output.warn("{} recipe lacks information about the {} "
                             "compiler support.".format(
                                 self.name, self.settings.compiler))
        else:
            if Version(self.settings.compiler.version) < min_version:
                raise ConanInvalidConfiguration(
                    "{} requires C++{} support. "
                    "The current compiler {} {} does not support it.".format(
                        self.name, self._minimum_cpp_standard,
                        self.settings.compiler,
                        self.settings.compiler.version))

#    def generate(self):
#        tc = CMakeToolchain(self, generator=os.getenv("CONAN_CMAKE_GENERATOR"))
#        tc.variables["MORPHEUS_BUILD_DOCS"] = self.options.build_docs
#        tc.generate()
#        deps = CMakeDeps(self)
        #import pdb; pdb.pm()
#        breakpoint()
#        deps.generate()

#    def source(self):
#        tools.get(**self.conan_data["sources"][self.version],
#                  strip_root=True, destination=self._source_subfolder)

    def package(self):
        copy(self, "*LICENSE*", dst="licenses", keep_path=False)
        cmake = CMake(self)
        cmake.configure()
        cmake.install()

#    def package_id(self):
#        self.info.header_only()

    def package_info(self):
        pass
        #self.cpp_info.names["cmake_find_package"] = "wg21_linear_algebra"
        #self.cpp_info.names["cmake_find_package_multi"] = "wg21_linear_algebra"
        #self.cpp_info.components["_wg21_linear_algebra"].names["cmake_find_package"] = "wg21_linear_algebra"
        #self.cpp_info.components["_wg21_linear_algebra"].names["cmake_find_package_multi"] = "wg21_linear_algebra"
        #self.cpp_info.components["_wg21_linear_algebra"].requires = ["mdspan::mdspan"]


