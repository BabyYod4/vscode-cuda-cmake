cmake_minimum_required( VERSION 3.5.1 )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )

file( GLOB_RECURSE CPU_SOURCES *.cc *.hh *.cpp *.hpp *.c *.h)
file( GLOB_RECURSE GPU_SOURCES cuda/*.cu )

### Disable Warnings 
set( CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++11 -L/usr/local/libs -I/opt/cuda/include" ) 

### Compiler settings
set( CMAKE_CXX_FLAGS_DEBUG "-g -O0" )
set( CMAKE_CXX_FLAGS_RELEASE "-O3" )
set( CMAKE_CXX_STANDARD_REQUIRED ON ) #...is required...
set( CMAKE_CXX_EXTENSIONS ON ) #...with compiler extensions like gnu++11

set( CMAKE_VERBOSE_MAKEFILE ON )
set( CMAKE_CXX_COMPILER_LAUNCHER "ccache" )
set( CMAKE_CUDA_COMPILER_LAUNCHER "ccache" )

set( CMAKE_CUDA_COMPILER "/opt/cuda/bin/nvcc" )

## Source file containing the "main" function
set( MAIN_SOURCE main.cpp )
## Specify a name for the generated executable file
set( MAIN_EXE_NAME ${PROJECT_NAME_}.exe )
set( MAIN_GPU_EXE_NAME ${PROJECT_NAME_}.gpu )

option(USE_OLD_CUDA "Use Old CUDA" OFF)

if( ("${CMAKE_VERSION}" VERSION_EQUAL 3.8) OR ("${CMAKE_VERSION}" VERSION_GREATER 3.8) )
    # Modern CMake
    enable_language("CUDA")
    add_executable( ${MAIN_EXE_NAME} ${MAIN_SOURCE} ${CPU_SOURCES} ${GPU_SOURCES} )
else()
    # Old CMake
    add_executable( ${MAIN_EXE_NAME} ${MAIN_SOURCE} ${CPU_SOURCES} )
    find_package(CUDA 8.0)
    if(NOT CUDA_FOUND)
        message(FATAL_ERROR "CUDA not found")
    else()
        CUDA_ADD_LIBRARY(${MAIN_GPU_EXE_NAME} ${GPU_SOURCES})
        set(USE_OLD_CUDA ON)
        target_link_libraries(diana diana_gpu)
    endif()

endif()


## Link
# target_link_libraries(${MAIN_EXE_NAME} <<Libraryname>> )
if(USE_OLD_CUDA)
    target_link_libraries( ${MAIN_EXE_NAME} ${MAIN_GPU_EXE_NAME} )
else()
    target_link_libraries( ${MAIN_EXE_NAME} )
endif()

add_definitions(-DUSE_CUDA)

## Install
install( TARGETS ${MAIN_EXE_NAME} RUNTIME DESTINATION bin )