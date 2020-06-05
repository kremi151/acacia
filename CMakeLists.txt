cmake_minimum_required(VERSION 3.15)
project(acacia CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        source/registry/registry.cpp
        source/exceptions/assertion_exception.cpp
        source/report/report.cpp
        source/report/junit.cpp
        source/io/stream_capture.cpp
        source/io/teebuf.cpp
        source/io/teestream.cpp
        )

set(HEADERS
        source/acacia.h
        source/registry/registry.h
        source/exceptions/assertion_exception.h
        source/assertions/assertions.h
        source/assertions/equality_assertions.h
        source/assertions/compare_assertions.h
        source/report/report.h
        source/report/junit.h
        source/io/stream_capture.h
        source/io/teebuf.h
        source/io/teestream.h
        )

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DFB_DEBUG")

add_library(acacia STATIC ${SOURCES} ${HEADERS})
#add_executable(acacia ${SOURCES} ${HEADERS})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/source")