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
from conans import ConanFile, CMake, tools
from conans.errors import ConanInvalidConfiguration
from conans.model.version import Version
from conan.tools.cmake import CMakeToolchain, CMakeDeps
from conans.tools import load
import re, os.path

required_conan_version = ">=1.33.0"

class Morpheus(ConanFile):
    name = "morpheus"
    homepage = "https://github.com/Twon/Morpheus"
    description = "Cross plafrom game engine build using C++20"
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
        "build_docs": True
    }
    exports_sources = ["CMakeLists.txt", "LICENSE", "version.txt", "cmake/*", "examples/*" "libraries/*"]
    generators = "cmake_find_package", "cmake_find_package_multi", "virtualenv"
    requires = (
        "boost/1.79.0",
        "catch2/3.1.0", 
        "fmt/8.1.1",
        "glbinding/3.1.0",
        "glew/2.2.0",
        "ms-gsl/4.0.0",
        "range-v3/0.12.0",
        "trompeloeil/42",
        "vulkan-headers/1.3.221"
    )

    def set_version(self):
        content = load(os.path.join(os.path.dirname(__file__), "version.txt"))
        version = re.search(r'(\d+\.\d+\.\d+)', content).group(1)
        self.version = version.strip()

    def build_requirements(self):
        # Ensure the package is build against a version of CMake from 3.23 onwards.
        if CMake.get_version() < Version("3.24.0"):
            self.build_requires("cmake/3.24.0")

    def requirements(self):
        if self.settings.os in ["Macos", "iOS", "tvOS"] and self.settings.compiler == "apple-clang":
            self.requires("moltenvk/1.1.6")

#    @property
#    def _source_subfolder(self):
#        return "source_subfolder"

    @property
    def _minimum_cpp_standard(self):
        return 20

    @property
    def _minimum_compilers_version(self):
        return {
            "Visual Studio": "16",
            "gcc": "11",
            "clang": "13",
            "apple-clang": "13"
        }

    def configure(self):
        if self.settings.compiler.get_safe("cppstd"):
            tools.check_min_cppstd(self, self._minimum_cpp_standard)
        min_version = self._minimum_compilers_version.get(
            str(self.settings.compiler))
        if not min_version:
            self.output.warn("{} recipe lacks information about the {} "
                             "compiler support.".format(
                                 self.name, self.settings.compiler))
        else:
            if tools.Version(self.settings.compiler.version) < min_version:
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
        self.copy("*LICENSE*", dst="licenses", keep_path=False)
        cmake = CMake(self)
        cmake.configure()
        cmake.install()

    def package_id(self):
        self.info.header_only()

    def package_info(self):
        pass
        #self.cpp_info.names["cmake_find_package"] = "wg21_linear_algebra"
        #self.cpp_info.names["cmake_find_package_multi"] = "wg21_linear_algebra"
        #self.cpp_info.components["_wg21_linear_algebra"].names["cmake_find_package"] = "wg21_linear_algebra"
        #self.cpp_info.components["_wg21_linear_algebra"].names["cmake_find_package_multi"] = "wg21_linear_algebra"
        #self.cpp_info.components["_wg21_linear_algebra"].requires = ["mdspan::mdspan"]
