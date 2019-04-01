cmake_minimum_required(VERSION 3.4)
project(wise_enum)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(warning_list
        -Wall
        -Wextra
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Wcast-align
        -Wunused
        -Woverloaded-virtual
        -Wpedantic
        -Wconversion
        -Wsign-conversion
        -Wlogical-op
        -Wuseless-cast
        -Wdouble-promotion
        -Wformat=2
        -Wno-missing-field-initializers)

add_library(${PROJECT_NAME} INTERFACE)

#todo add if around this:
target_link_libraries(${PROJECT_NAME} INTERFACE
        CONAN_PKG::boost
        )
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()
file(GLOB_RECURSE ut-sources ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp)
add_executable(utest-${PROJECT_NAME} ${ut-sources})
target_sources(utest-${PROJECT_NAME} PRIVATE test)
target_link_libraries(utest-${PROJECT_NAME}  PRIVATE ${PROJECT_NAME} CONAN_PKG::gtest)
add_test(NAME utest-${PROJECT_NAME} COMMAND utest-${PROJECT_NAME} --gtest_output=xml:utest.xml)
