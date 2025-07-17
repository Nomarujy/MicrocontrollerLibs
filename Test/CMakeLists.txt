cmake_minimum_required(VERSION 4.0)

project(ComponentTests)

enable_testing()

add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/googleTest"
    "googleTest"
)

file(GLOB_RECURSE TEST_FILES "./testLib/*.cpp")

foreach(TEST_FILE ${TEST_FILES})
    
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

    add_executable(${TEST_NAME} ${TEST_FILE})

    target_include_directories(
    ${TEST_NAME} PRIVATE
    "../Components"
    )

    target_include_directories(
    ${TEST_NAME} PRIVATE
    "../Microcontroller"
    )

    target_link_libraries(
    ${TEST_NAME} PRIVATE
    gtest gtest_main
    )

    add_test(${TEST_NAME} ${TEST_NAME})

endforeach(TEST_FILE ${TEST_FILES})