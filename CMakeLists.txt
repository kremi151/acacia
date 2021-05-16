cmake_minimum_required(VERSION 3.13)
project(acacia CXX)

set(CMAKE_CXX_STANDARD 17)

set(ACACIA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake-modules)

# Filesystem support is optional
# If not supported, generated source folders will be created by CMake
find_package(Filesystem)

include(acacia.cmake)

set(GENERATOR_SOURCES
        generator-source/main.cpp
        generator-source/scan_file.cpp
        generator-source/scan_suite.cpp
        generator-source/utils.cpp
        generator-source/cmd_meta.cpp
        generator-source/cmd_generate.cpp
        )

set(GENERATOR_HEADERS
        generator-source/scan_file.h
        generator-source/scan_suite.h
        generator-source/utils.h
        generator-source/logging.h
        generator-source/platform.h
        generator-source/cmd_meta.h
        generator-source/cmd_generate.h
        generator-source/fs.h
        generator-source/typedefs.h
        )

add_executable(acacia-gen ${GENERATOR_SOURCES} ${GENERATOR_HEADERS})
if (Filesystem_FOUND)
    target_link_libraries(acacia-gen CXX::Filesystem)
    target_compile_definitions(acacia-gen PRIVATE ACACIA_HAS_FS)
endif()

set(SOURCES
        source/acacia.cpp
        source/registry/registry.cpp
        source/exceptions/assertion_exception.cpp
        source/assertions/manual_assertions.cpp
        source/assertions/output_assertions.cpp
        source/assertions/boolean_assertions.cpp
        source/report/report.cpp
        source/report/acacia_report.cpp
        source/report/junit.cpp
        source/io/stream_capture.cpp
        source/io/teebuf.cpp
        source/io/teestream.cpp
        source/util/json_serialization.cpp
        )

set(HEADERS
        source/acacia.h
        source/registry/registry.h
        source/exceptions/assertion_exception.h
        source/assertions/assertions.h
        source/assertions/equality_assertions.h
        source/assertions/compare_assertions.h
        source/assertions/manual_assertions.h
        source/assertions/output_assertions.h
        source/assertions/boolean_assertions.h
        source/report/report.h
        source/report/acacia_report.h
        source/report/junit.h
        source/io/stream_capture.h
        source/io/teebuf.h
        source/io/teestream.h
        source/util/json_serialization.h
        source/util/test_suites.h
        )

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DFB_DEBUG")

add_library(acacia STATIC ${SOURCES} ${HEADERS})
#add_executable(acacia ${SOURCES} ${HEADERS})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/source")
