function(week_executable)
    set(options)
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCES INCLUDE_DIRECTORIES LIBRARIES)
    cmake_parse_arguments(WEEK_EXE "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_executable("${PROJECT_NAME}_${WEEK_EXE_NAME}" ${WEEK_EXE_SOURCES})
    target_link_libraries("${PROJECT_NAME}_${WEEK_EXE_NAME}" PRIVATE ${WEEK_EXE_LIBRARIES} ${Boost_LIBRARIES})
    target_include_directories("${PROJECT_NAME}_${WEEK_EXE_NAME}" PRIVATE ${WEEK_EXE_INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIR})
endfunction()

function(week_library)
    set(options)
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCES INCLUDE_DIRECTORIES LIBRARIES)
    cmake_parse_arguments(WEEK_LIB "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_library("${PROJECT_NAME}_${WEEK_LIB_NAME}" STATIC ${WEEK_LIB_SOURCES})
    target_link_libraries("${PROJECT_NAME}_${WEEK_LIB_NAME}" PUBLIC ${WEEK_LIB_LIBRARIES} ${Boost_LIBRARIES})
    target_include_directories("${PROJECT_NAME}_${WEEK_LIB_NAME}" PUBLIC ${WEEK_LIB_INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIR})
endfunction()

function(week_shared_library)
    set(options)
    set(oneValueArgs NAME OUTPUT_NAME)
    set(multiValueArgs SOURCES INCLUDE_DIRECTORIES LIBRARIES)
    cmake_parse_arguments(WEEK_LIB "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    add_library("${PROJECT_NAME}_${WEEK_LIB_NAME}" SHARED ${WEEK_LIB_SOURCES})
    target_link_libraries("${PROJECT_NAME}_${WEEK_LIB_NAME}" PUBLIC ${WEEK_LIB_LIBRARIES} ${Boost_LIBRARIES})
    target_include_directories("${PROJECT_NAME}_${WEEK_LIB_NAME}" PUBLIC ${WEEK_LIB_INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIR})
    if(WEEK_LIB_OUTPUT_NAME)
      set_target_properties("${PROJECT_NAME}_${WEEK_LIB_NAME}" PROPERTIES
        OUTPUT_NAME ${WEEK_LIB_OUTPUT_NAME}
      )
    endif()
endfunction()

function(week_test)
    set(options)
    set(oneValueArgs NAME)
    set(multiValueArgs SOURCES INCLUDE_DIRECTORIES LIBRARIES)
    cmake_parse_arguments(WEEK_TEST "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    week_executable(NAME ${WEEK_TEST_NAME}
        SOURCES ${WEEK_TEST_SOURCES}
        INCLUDE_DIRECTORIES ${WEEK_TEST_INCLUDE_DIRECTORIES}
        LIBRARIES ${WEEK_TEST_LIBRARIES}
    )

    add_test(NAME "${PROJECT_NAME}_${WEEK_TEST_NAME}" COMMAND "${PROJECT_NAME}_${WEEK_TEST_NAME}")
endfunction()
