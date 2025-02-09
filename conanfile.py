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
from conan.tools.files import copy, rm
from conan.tools.scm import Git, Version
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
        "with_rs_vulkan": True,
     }
    requires = (
        "boost/1.86.0",
        "ctre/3.8.1",
        "magic_enum/0.9.5",
        "ms-gsl/4.0.0",
        "rapidjson/cci.20230929",
        "scnlib/4.0.1",
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
                      (compiler == "clang" and version >= Version("19"))
        return not std_support
    
    @property
    def useRanges(self):
        """ Does the current compiler version lack support for std::ranges via the STL. """
        compiler = self.settings.compiler
        version = Version(self.settings.compiler.version)
        std_support = (compiler == "msvc" and version >= 193) or (compiler == "gcc" and version >= Version("10")) or \
                      (compiler == "clang" and version >= Version("16"))
        return not std_support

    def config_options(self):
        if not self.checkMoldIsSupported():
            self.options.rm_safe("link_with_mold")

        if not (self.settings.os in ["Macos", "iOS", "tvOS"]):
            self.options.rm_safe("with_rs_metal")

        if not (self.settings.os in ["Windows"]):
            self.options.rm_safe("with_rs_direct_x12")

    def build_requirements(self):
        self.tool_requires("ninja/1.12.1")
        self.test_requires("catch2/3.7.0")
        self.test_requires("gtest/1.15.0")

        if get_cmake_version() < Version("3.30.1"):
            self.tool_requires("cmake/3.30.1")

        if self.options.build_docs:
            self.build_requires("doxygen/1.13.2")

        if self.options.get_safe("link_with_mold", False):
            self.build_requires("mold/2.33.0")
            self.build_requires("openssl/3.2.1", override=True)

    def requirements(self):
        if self.options.get_safe("with_rs_vulkan", False):
            self.requires("vulkan-headers/1.3.239.0", transitive_headers=True)

            if (self.settings.os in ["Macos", "iOS", "tvOS"]):
                self.requires("moltenvk/1.2.2", transitive_headers=True)

        if self.options.get_safe("with_rs_opengl", False):
            self.requires("glbinding/3.3.0", transitive_headers=True)
            self.requires("glew/2.2.0", transitive_headers=True)

        if self.settings.os in ["Windows"]:
            self.requires("wil/1.0.240803.1", transitive_headers=True)

        if self.useDate:
            self.requires("date/3.0.3", transitive_headers=True)

        if self.useExpected:
            self.requires("tl-expected/20190710", transitive_headers=True)

        if self.useFMT:
            self.requires("fmt/11.0.2", transitive_headers=True)

        if self.useRanges:
            self.requires("range-v3/cci.20240905", transitive_headers=True)

    def system_requirements(self):
        if self.options.get_safe("with_rs_opengl", False):
            apt = Apt(self)
            apt.install(["libgl-dev", "libopengl-dev", "libglu1-mesa-dev"], update=True, check=True)

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

    def export_sources(self):
        copy(self, "CMakeLists.txt", src=self.recipe_folder, dst=self.export_sources_folder)
        copy(self, "LICENSE", src=self.recipe_folder, dst=self.export_sources_folder)
        copy(self, "version.txt", src=self.recipe_folder, dst=self.export_sources_folder)
        copy(self, "cmake/*", src=self.recipe_folder, dst=self.export_sources_folder)
        copy(self, "examples/*", src=self.recipe_folder, dst=self.export_sources_folder)
        copy(self, "libraries/*", src=self.recipe_folder, dst=self.export_sources_folder)

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, pattern="LICENSE", src=self.source_folder, dst=os.path.join(self.package_folder, "licenses"))
        cmake = CMake(self)
        cmake.configure()
        cmake.install()
        rm(self, "*export-set*.cmake", os.path.join(self.package_folder, "lib", "cmake", "morpheus"))

    def package_info(self):
        self.cpp_info.components["core"].set_property("cmake_file_name", "MorpheusCore")
        self.cpp_info.components["core"].set_property("cmake_target_name", "morpheus::core")
        self.cpp_info.components["core"].defines = ["BOOST_USE_WINAPI_VERSION=BOOST_WINAPI_NTDDI_WIN10"]
        self.cpp_info.components["core"].requires = ["boost::headers", "boost::log", "ctre::ctre", "magic_enum::magic_enum", "ms-gsl::ms-gsl", "range-v3::range-v3", "rapidjson::rapidjson", "scnlib::scnlib"]
        self.cpp_info.components["core"].builddirs.append(os.path.join("lib", "cmake", "morpheus"))

        if self.useDate:
            self.cpp_info.components["core"].requires.append("date::date")
            self.cpp_info.components["core"].requires.append("date::date-tz")

        if self.useExpected:
            self.cpp_info.components["core"].requires.append("tl-expected::expected")

        if self.useFMT:
            self.cpp_info.components["core"].requires.append("fmt::fmt")

        if self.options.get_safe("with_rs_direct_x12", False):
            self.cpp_info.components["directx12"].set_property("cmake_file_name", "MorpheusGfxDirectX12")
            self.cpp_info.components["directx12"].set_property("cmake_target_name", "morpheus::gfx::directx12")

        if self.options.get_safe("with_rs_metal", False):
            self.cpp_info.components["metal"].set_property("cmake_file_name", "MorpheusGfxMetal")
            self.cpp_info.components["metal"].set_property("cmake_target_name", "morpheus::gfx::metal")

        if self.options.get_safe("with_rs_opengl", False):
            self.cpp_info.components["opengl"].set_property("cmake_file_name", "MorpheusGfxVulkan")
            self.cpp_info.components["opengl"].set_property("cmake_target_name", "morpheus::gfx::vulkan")
            self.cpp_info.components["opengl"].requires.append("glbinding::glbinding")
            self.cpp_info.components["opengl"].requires.append("glew::glew")

        if self.options.get_safe("with_rs_vulkan", False):
            self.cpp_info.components["vulkan"].set_property("cmake_file_name", "MorpheusGfxVulkan")
            self.cpp_info.components["vulkan"].set_property("cmake_target_name", "morpheus::gfx::vulkan")
            self.cpp_info.components["vulkan"].requires.append("vulkan-headers::vulkan-headers")

            if (self.settings.os in ["Macos", "iOS", "tvOS"]):
                self.cpp_info.components["vulkan"].requires.append("moltenvk::moltenvk")
