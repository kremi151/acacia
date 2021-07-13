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

    set(ACACIA_TEST_SOURCES "")
    set(ACACIA_META_FILES "")
    foreach(INPUT_FILE ${ARGV})
        list(APPEND ACACIA_TEST_SOURCES ${INPUT_FILE})

        set(ACACIA_TMP_META_FILE ${ACACIA_GENERATED_DIR}/meta/${INPUT_FILE}.meta)

        string(UUID ACACIA_TMP_UUID NAMESPACE "464bd450-52a4-4f01-aef8-3889917ab97a" NAME "${ACACIA_TMP_META_FILE}" TYPE SHA1)

        get_filename_component(ACACIA_TMP_META_PARENT_DIR "${ACACIA_TMP_META_FILE}" DIRECTORY)

        set(ACACIA_TMP_DEPENDENCIES_LIST
                acacia-gen
                ${INPUT_FILE}
                )

        if (Filesystem_FOUND)
        else()
            add_custom_target("acacia_meta_${ACACIA_TMP_UUID}" ALL
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${ACACIA_TMP_META_PARENT_DIR})

            list(APPEND ACACIA_TMP_DEPENDENCIES_LIST "acacia_meta_${ACACIA_TMP_UUID}")
        endif()

        add_custom_command(
                OUTPUT ${ACACIA_GENERATED_DIR}/meta/${INPUT_FILE}.meta
                COMMAND acacia-gen meta ${CMAKE_CURRENT_SOURCE_DIR} ${ACACIA_GENERATED_DIR}/meta ${INPUT_FILE}
                DEPENDS ${ACACIA_TMP_DEPENDENCIES_LIST}
        )

        list(APPEND ACACIA_META_FILES ${ACACIA_TMP_META_FILE})

        unset(ACACIA_TMP_DEPENDENCIES_LIST)
        unset(ACACIA_TMP_META_FILE)
        unset(ACACIA_TMP_META_PARENT_DIR)
        unset(ACACIA_TMP_UUID)
    endforeach()

    add_custom_command(
            OUTPUT ${ACACIA_GENERATED_DIR}/suites.h ${ACACIA_GENERATED_DIR}/test_suites.cpp
            COMMAND acacia-gen generate ${ACACIA_GENERATED_DIR} ${ACACIA_META_FILES}
            DEPENDS acacia-gen ${ACACIA_META_FILES}
    )

    set(ACACIA_TEST_HEADERS ${ACACIA_TEST_HEADERS} "${ACACIA_GENERATED_DIR}/suites.h")
    set(ACACIA_TEST_SOURCES ${ACACIA_TEST_SOURCES} "${ACACIA_GENERATED_DIR}/test_suites.cpp")
endmacro()