cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Baseball_Elimination VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_SOURCE_DIR}/../run)
set(CMAKE_BUILD_TYPE RelWithDebInfo)
# add the executable
add_executable(Baseball_Elimination Baseball_elimination.cpp)
add_subdirectory(Maxflow)
target_link_libraries(Baseball_Elimination PUBLIC Maxflow)
