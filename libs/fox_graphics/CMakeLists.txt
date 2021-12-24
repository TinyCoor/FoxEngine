cmake_minimum_required(VERSION 3.13)
project(fox_graphics)

find_package(Vulkan REQUIRED)

#Decl
add_library(fox_graphics)

#generate_export_header(fox_graphics EXPORT_FILE_NAME  EXPORT_MACRO_NAME
#                        ${CMAKE_CURRENT_BINARY_DIR}/exports/fox/graphics_export.h)
target_include_directories(fox_graphics PUBLIC include)
target_link_libraries(fox_graphics PUBLIC Vulkan::Vulkan)
target_code_coverage(fox_graphics)
# Source

add_subdirectory(src)