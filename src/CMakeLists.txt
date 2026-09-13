# This file was automatically generated for projects
# without default 'CMakeLists.txt' file.

FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/src/*.*)

idf_component_register(SRCS ${app_sources})


target_include_directories(your_test_executable_name PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/mocks
)