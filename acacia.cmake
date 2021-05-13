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
    file(MAKE_DIRECTORY ${ACACIA_GENERATED_DIR})

    set(ACACIA_TEST_SOURCES ${ACACIA_TEST_SOURCES} ${ARGV})

    add_custom_command(
            OUTPUT ${ACACIA_GENERATED_DIR}/suites.h ${ACACIA_GENERATED_DIR}/test_suites.cpp
            COMMAND acacia-gen ${CMAKE_CURRENT_SOURCE_DIR} ${ACACIA_GENERATED_DIR} ${ARGV}
            DEPENDS acacia-gen
            MAIN_DEPENDENCY ${ARGV} ""
    )

    set(ACACIA_TEST_HEADERS ${ACACIA_TEST_HEADERS} "${ACACIA_GENERATED_DIR}/suites.h")
    set(ACACIA_TEST_SOURCES ${ACACIA_TEST_SOURCES} "${ACACIA_GENERATED_DIR}/test_suites.cpp")
endmacro()