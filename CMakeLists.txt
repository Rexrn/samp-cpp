# CMake settings
cmake_minimum_required(VERSION 3.1)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.12)
endif()

# Project
project(SAMPEDGENGINE LANGUAGES C CXX)

# Add subproject targets.
add_subdirectory(Engine)
add_subdirectory(ServerCore)
add_subdirectory(Examples)
