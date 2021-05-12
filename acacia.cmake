macro(set_acacia_paths_internal)
    set(ACACIA_GENERATED_DIR "${CMAKE_BINARY_DIR}/acacia-generated")
    set(ACACIA_TEST_INCLUDE_DIRS "${ACACIA_GENERATED_DIR}/include")
endmacro()

macro(set_acacia_use_default_main)
    set_acacia_paths_internal()
    configure_file("${ACACIA_SOURCE_DIR}/source/dynamic/acacia_default_main.cpp.in" "${ACACIA_GENERATED_DIR}/default_main.cpp" @ONLY)
    set(ACACIA_TEST_SOURCES ${ACACIA_TEST_SOURCES} "${ACACIA_GENERATED_DIR}/default_main.cpp")
endmacro()

macro(set_acacia_test_sources)
    set_acacia_paths_internal()
    set(ACACIA_TEST_SOURCES ${ACACIA_TEST_SOURCES} ${ARGV})
    set(ACACIA_SUITE_IMPORTS "")
    set(ACACIA_REPORT_EXECUTION_CODE "")
    foreach(ACACIA_TEST_SOURCE ${ARGV})
        message(STATUS "Test source: ${ACACIA_TEST_SOURCE}")

        file(READ ${ACACIA_TEST_SOURCE} ACACIA_TEST_SOURCE_CONTENT)
        string(REGEX MATCH "TEST_SUITE\\s*\\(([^)]+)\\)" _ ${ACACIA_TEST_SOURCE_CONTENT})

        set(ACACIA_TEST_SUITE_NAME ${CMAKE_MATCH_1})

        if(NOT "${ACACIA_TEST_SUITE_NAME}" STREQUAL "")
            message(STATUS "Found test suite '${ACACIA_TEST_SUITE_NAME}'")

            configure_file("${ACACIA_SOURCE_DIR}/source/dynamic/test_suite_header.h.in" "${ACACIA_GENERATED_DIR}/suite_${ACACIA_TEST_SUITE_NAME}.h" @ONLY)
            set(ACACIA_TEST_HEADERS ${ACACIA_TEST_HEADERS} "${ACACIA_GENERATED_DIR}/suite_${ACACIA_TEST_SUITE_NAME}.h")

            set(ACACIA_SUITE_IMPORTS "${ACACIA_SUITE_IMPORTS}\n\
#include \"suite_${ACACIA_TEST_SUITE_NAME}.h\"")
            set(ACACIA_SUITE_MAP_CODE "${ACACIA_SUITE_MAP_CODE}\n\
suites[\"${ACACIA_TEST_SUITE_NAME}\"] = __Acacia__TestSuite_${ACACIA_TEST_SUITE_NAME}::runSuite;")
        endif()
    endforeach()

    configure_file("${ACACIA_SOURCE_DIR}/source/dynamic/test_suites.cpp.in" "${ACACIA_GENERATED_DIR}/test_suites.cpp" @ONLY)
    set(ACACIA_TEST_SOURCES ${ACACIA_TEST_SOURCES} "${ACACIA_GENERATED_DIR}/test_suites.cpp")

    set(ACACIA_TEST_SOURCE_CONTENT "")
endmacro()