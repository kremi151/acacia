cmake_minimum_required(VERSION 3.15)
project(acacia)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        source/acacia.cpp
        source/registry/registry.cpp
        source/registry/registrator.cpp
        source/exceptions/assertion_exception.cpp
#        source/debug_Test.cpp
        )

set(HEADERS
        source/acacia.h
        source/registry/registry.h
        source/registry/registrator.h
        source/exceptions/assertion_exception.h
        source/assertions/assertions.h
        source/assertions/equality_assertions.h
        )

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DFB_DEBUG")

add_library(acacia SHARED ${SOURCES} ${HEADERS})
#add_executable(acacia ${SOURCES} ${HEADERS})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/source")