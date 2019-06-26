#!/usr/bin/env python
# -*- coding: utf-8 -*-

from conans import ConanFile, CMake, tools
import os


class WiseEnum(ConanFile):
    name = "wise_enum"
    version = "0.0.1"
    description = "A reflective enum implementation for C++"
    settings = "os", "compiler", "build_type", "arch", "cppstd"
    #because it does not seem possible to conditionally set boost:shared in default_options we are always setting it.
    default_options = "boost:shared=True"
    generators = "cmake"
    build_requires = "gtest/1.8.1@bincrafters/stable"
    exports_sources = "CMakeLists.txt", "*h", "test*"

    def is_cpp_11_or_14(self):
        return  "11" in self.settings.cppstd or "14" in self.settings.cppstd

    def configure(self):
        if self.is_cpp_11_or_14():
            self.requires("boost/1.68.0@conan/stable")

    def build(self):
        cmake = CMake(self)
        if self.is_cpp_11_or_14():
            cmake.definitions["WISE_ENUM_USE_BOOST"] = "ON"
        cmake.configure()
        cmake.build()
        if tools.get_env("CONAN_RUN_TESTS", False):
            cmake.test()

    def package(self):
        self.copy("*.h", dst="include/wise_enum", src="")
