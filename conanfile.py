#!/usr/bin/env python
# -*- coding: utf-8 -*-
from conans import ConanFile, CMake

class MetricsConan(ConanFile):
    name = "sds_metrics"
    version = "0.3.2"

    license = "Proprietary"
    url = "https://github.corp.ebay.com/SDS/metrics"
    description = "Metrics collection project for eBay SDS"

    settings = "compiler"
    options = {"coverage": ['True', 'False'],
               "sanitize": ['True', 'False']}
    default_options = 'coverage=False', 'sanitize=False'

    requires = (("sds_logging/3.0.1@sds/stable"),
                ("boost_dynamic_bitset/1.66.0@bincrafters/stable"),
                ("evhtp/1.2.16@oss/stable"),
                ("jsonformoderncpp/3.1.2@vthiery/stable"),
                ("prometheus-cpp/0.1.2@oss/stable"),
                ("userspace-rcu/0.10.1@oss/stable"))

    generators = "cmake"
    exports_sources = "CMakeLists.txt", "cmake/*", "src/*"

    def configure(self):
        if not self.settings.compiler == "gcc":
            del self.options.coverage

    def build(self):
        cmake = CMake(self)

        definitions = {'CONAN_BUILD_COVERAGE': 'OFF',
                       'MEMORY_SANITIZER_ON': 'OFF'}
        test_target = None

        if self.options.coverage == 'True':
            definitions['CONAN_BUILD_COVERAGE'] = 'ON'
            test_target = 'coverage'

        if self.options.sanitize == 'True':
            definitions['MEMORY_SANITIZER_ON'] = 'ON'

        cmake.configure(defs=definitions)
        cmake.build()
        cmake.test(target=test_target)

    def package(self):
        self.copy("*.hpp", src="src/include", dst="include", keep_path=False)
        self.copy("*.a", dst="lib/", keep_path=False)
        self.copy("*.lib", dst="lib/", keep_path=False)
        self.copy("*.so", dst="lib/", keep_path=False)
        self.copy("*.dll", dst="lib/", keep_path=False)
        self.copy("*.dylib", dst="lib/", keep_path=False)

    def package_info(self):
        if self.options.coverage == 'True':
            self.cpp_info.libs.append('gcov')
