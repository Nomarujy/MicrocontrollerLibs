cmake_minimum_required(VERSION 4.0)

project("TestingLibrary")

enable_testing()

add_subdirectory(
    "Test/googleTest"
    "googleTest"
)

include_directories("src")

#List of all Libs
set(LibsPathDirectories
"Components/TEMP/BMP280"
)

foreach(path IN LISTS LibsPathDirectories)

    #create library
    file(GLOB LibFiles "src/${path}/*.cpp")
    if(NOT LibFiles)
        message(WARNING "Source files not found at directory: ${path}")
        continue()
    endif()

    get_filename_component(LibName ${path} NAME)
    add_library("${LibName}" ${LibFiles})

    #create tests 
    file(GLOB TestFiles "Test/${path}/*.cpp")
    if(NOT TestFiles)
        message(WARNING "Test files not found at directory: Test/${path}")
        continue()
    endif()

    add_executable("${LibName}Tester" ${TestFiles})
    target_link_libraries("${LibName}Tester" gtest gtest_main ${LibName})
    target_compile_definitions("${LibName}Tester" PUBLIC DEBUG)
    add_test("${LibName}_Tests" "${LibName}Tester")

endforeach(path)
