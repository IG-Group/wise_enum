#!/bin/bash
set -e

if [[ -z ${CONAN_FULL_PACKAGE_NAME} ]]; then
  echo "CONAN_FULL_PACKAGE_NAME is not set"
  return 1
fi

#gcc4.9_std14
(
source /opt/rh/devtoolset-3/enable
SHARED_SETTINGS='-s compiler=gcc -s compiler.version=4.9 -s compiler.libcxx=libstdc++ -s cppstd=14'
conan create . ${CONAN_FULL_PACKAGE_NAME} ${SHARED_SETTINGS} -s build_type=Debug
conan create . ${CONAN_FULL_PACKAGE_NAME} ${SHARED_SETTINGS} -s build_type=Release
)

#gcc8_std14
(
source /opt/rh/devtoolset-8/enable
SHARED_SETTINGS='-s compiler=gcc -s compiler.version=8 -s compiler.libcxx=libstdc++11 -s cppstd=14'
conan create . ${CONAN_FULL_PACKAGE_NAME} ${SHARED_SETTINGS} -s build_type=Debug
conan create . ${CONAN_FULL_PACKAGE_NAME} ${SHARED_SETTINGS} -s build_type=Release
)
#gcc8_std17
(
source /opt/rh/devtoolset-8/enable
SHARED_SETTINGS='-s compiler=gcc -s compiler.version=8 -s compiler.libcxx=libstdc++11 -s cppstd=17'
conan create . ${CONAN_FULL_PACKAGE_NAME} ${SHARED_SETTINGS} -s build_type=Debug
conan create . ${CONAN_FULL_PACKAGE_NAME} ${SHARED_SETTINGS} -s build_type=Release
)
