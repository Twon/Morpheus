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
from conan.tools.cmake import cmake_layout, CMake, CMakeDeps, CMakeToolchain
from conan.tools.env import VirtualBuildEnv
from conan.tools.files import copy
from conan.tools.scm import Version
from conan.tools.files import load
from conan.tools.system.package_manager import Apt
import re, os.path
import subprocess
import sys

required_conan_version = ">=2.1.0"


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
        "build_docs": [True, False],
        "fPIC": [True, False],
        "link_with_mold": [True, False],
        "shared": [True, False],
        "tools": [True, False],
        "with_rs_direct_x12": [True, False],
        "with_rs_metal": [True, False],
        "with_rs_opengl": [True, False],
        "with_rs_vulkan": [True, False]
    }
    default_options = {
        "build_docs": False,
        "fPIC": True,
        "link_with_mold": True,
        "shared": False,
        "tools": True,
        "with_rs_direct_x12": True,
        "with_rs_metal": True,
        "with_rs_opengl": True,
        "with_rs_vulkan": True
     }
    exports_sources = ["CMakeLists.txt", "LICENSE", "version.txt", "cmake/*", "examples/*" "libraries/*"]
    requires = (
        "boost/1.85.0",
        "ctre/3.8.1",
        "magic_enum/0.9.5",
        "ms-gsl/4.0.0",
        "rapidjson/cci.20230929",
        "range-v3/0.12.0",
        "scnlib/2.0.2",
        #"zlib/1.2.12" # xapian-core/1.4.19' requires 'zlib/1.2.12' while 'boost/1.81.0' requires 'zlib/1.2.13'. To fix this conflict you need to override the package 'zlib' in your root package.
    )

    build_requires = (
#        "ccache/4.6",
    )

    def set_version(self):
        content = load(self, os.path.join(os.path.dirname(__file__), "version.txt"))
        version = re.search(r'(\d+\.\d+\.\d+)', content).group(1)
        self.version = version.strip()

    def checkMoldIsSupported(self):
        """ Mold is only tested on Linux with gcc and clang. In future support for icc may be added. """
        return self.settings.os == "Linux" and (self.settings.compiler == "clang" or self.settings.compiler == "gcc")

    @property
    def useDate(self):
        """ Does the current compiler version lack support for Date and timezones via the STL. """
        compiler = self.settings.compiler
        version = Version(self.settings.compiler.version)
        std_support = (compiler == "msvc" and version >= 193) or (compiler == "gcc" and version >= Version("14"))
        return not std_support

    @property
    def useExpected(self):
        """ Does the current compiler version lack support for std::expected via the STL. """
        compiler = self.settings.compiler
        version = Version(self.settings.compiler.version)
        std_support = (compiler == "msvc" and version >= 193) or (compiler == "gcc" and version >= Version("12")) or \
                      (compiler == "clang" and version >= Version("16")) or (compiler == "apple-clang" and version >= Version("15"))
        return not std_support

    @property
    def useFMT(self):
        """ Does the current compiler version lack support for std::format or std::print via the STL. """
        compiler = self.settings.compiler
        version = Version(self.settings.compiler.version)
        std_support = (compiler == "msvc" and version >= 193) or (compiler == "gcc" and version >= Version("14")) or \
                      (compiler == "clang" and version >= Version("18"))
        return not std_support

    def config_options(self):
        if not self.checkMoldIsSupported():
            self.options.rm_safe("link_with_mold")

        if not (self.settings.os in ["Macos", "iOS", "tvOS"]):
            self.options.rm_safe("with_rs_metal")

        if not (self.settings.os in ["Windows"]):
            self.options.rm_safe("with_rs_direct_x12")

    def build_requirements(self):
        self.tool_requires("ninja/1.11.1")
        self.test_requires("catch2/3.5.3")
        self.test_requires("gtest/1.14.0")

        if get_cmake_version() < Version("3.28.1"):
            self.tool_requires("cmake/3.28.1")

        if self.options.build_docs:
            self.build_requires("doxygen/1.9.4") # doxygen/1.9.5 will update dependency on zlib/1.2.12 to zlib/1.2.13

        if self.options.get_safe("link_with_mold", False):
            self.build_requires("mold/2.4.0")
            self.build_requires("openssl/3.2.1", override=True)

    def requirements(self):
        if self.options.get_safe("with_rs_vulkan", False):
            self.requires("vulkan-headers/1.3.239.0")
        
            if (self.settings.os in ["Macos", "iOS", "tvOS"]):
                self.requires("moltenvk/1.2.2")

        if self.options.get_safe("with_rs_opengl", False):
            self.requires("glbinding/3.3.0")
            self.requires("glew/2.2.0")

        if self.settings.os in ["Windows"]:
            self.requires("wil/1.0.240122.1")

        if self.useDate:
            self.requires("date/3.0.1")

        if self.useExpected:
            self.requires("tl-expected/20190710")

        if self.useFMT:
            self.requires("fmt/10.2.1")

    def system_requirements(self):
        apt = Apt(self)
        apt.install(["libgl-dev", "libopengl-dev", "libglu1-mesa-dev"], update=True, check=True)

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

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables["BUILD_SHARED_LIBS"] = self.options.shared
        tc.variables["MORPHEUS_BUILD_DOCS"] = self.options.build_docs
        tc.variables["MORPHEUS_LINK_WITH_MOLD"] = self.options.get_safe("link_with_mold", False)
        tc.variables["MORPHEUS_RENDER_SYSTEM_DIRECT_X12"] = self.options.get_safe("with_rs_direct_x12", False)
        tc.variables["MORPHEUS_RENDER_SYSTEM_METAL"] = self.options.get_safe("with_rs_metal", False)
        tc.variables["MORPHEUS_RENDER_SYSTEM_OPENGL"] = self.options.get_safe("with_rs_opengl", False)
        tc.variables["MORPHEUS_RENDER_SYSTEM_VULKAN"] = self.options.get_safe("with_rs_vulkan", False)
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()
        ms = VirtualBuildEnv(self)
        ms.generate()

    def layout(self):
        cmake_layout(self)

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
