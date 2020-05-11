cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Burrows-Wheeler VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_SOURCE_DIR}/../run)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

# add the executable
add_executable(BWCompression Burrows-Wheeler.cpp)
add_subdirectory(BWT)
add_subdirectory(MoF)
add_subdirectory(Hff_alg)
#link the library to the executable
target_link_libraries(BWCompression PUBLIC BWT MoF Hff_alg)
