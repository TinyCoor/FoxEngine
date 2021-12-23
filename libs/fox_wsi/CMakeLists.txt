cmake_minimum_required(VERSION 3.13)
project(fox_wsi)

add_library(fox_wsi STATIC)

add_subdirectory(src)

target_include_directories(fox_wsi PUBLIC include)
target_link_libraries(fox_wsi public glfw)
target_code_coverage(fox_wsi)