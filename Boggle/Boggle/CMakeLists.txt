cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(Boggle VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_SOURCE_DIR}/../run)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

# add the executable
add_executable(Boggle Boggle.cpp)
add_subdirectory(BoggleBoard)
add_subdirectory(Tries)
target_link_libraries(Boggle PUBLIC BoggleBoard Tries)
