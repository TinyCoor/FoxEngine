cmake_minimum_required(VERSION 3.13)
project(FoxEngine CXX)


#c++ 20
include(cmake/c++-standards.cmake)
cxx_20()

#code coverage
include(cmake/code-coverage.cmake)
add_code_coverage_all_targets()


# formatting commands
include(cmake/formatting.cmake)
file(GLOB_RECURSE CL_FILES *.[hc]pp *.[hc])
list(FILTER CL_FILES EXCLUDE REGEX ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(FILTER CL_FILES EXCLUDE REGEX ${CMAKE_CURRENT_SOURCE_DIR}/build)
clang_format(format ${CL_FILES})

file(GLOB_RECURSE CM_FILES CMakeLists.txt *.cmake)
list(FILTER CM_FILES EXCLUDE REGEX ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
cmake_format(cmake-format ${CM_FILES})


#Dependency Graph
include(cmake/dependency-graph.cmake)
gen_dep_graph(png ADD_TO_DEP_GRAPH)

#clang-tidy
include(cmake/tools.cmake)
option(CLANG_TIDY_FIX "" OFF)
if(CLANG_TIDY_FIX)
    clang_tidy(-headerfilter='${CMAKE_SOURCE_DIR}/*' -fix)
else()
    clang_tidy(-headerfilter='${CMAKE_SOURCE_DIR}/*')
endif()


#Misc CMake
include(cmake/compiler-options.cmake)
include(cmake/sanitizers.cmake)

#Engine EntryPoint
add_executable(fox_engine)
target_code_coverage(fox_engine AUTO ALL EXTERNAL)

#Sources
add_subdirectory(src)