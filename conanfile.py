#!/usr/bin/env python
# -*- coding: utf-8 -*-

from conans import ConanFile, CMake, tools
import os


class WiseEnum(ConanFile):
    name = "wise_enum"
    version = "0.0.1"
    description = "A reflective enum implementation for C++"
    settings = "os", "compiler", "build_type", "arch", "cppstd"
    default_options = "boost:shared=True"
    generators = "cmake"
    requires = (
        'boost/1.68.0@conan/stable'
    )
    build_requires = "gtest/1.8.1@bincrafters/stable"
    exports_sources = "CMakeLists.txt", "*h", "test*"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        if tools.get_env("CONAN_RUN_TESTS", False):
            cmake.test()

    def package(self):
        self.copy("*.h", dst="include", src="")
