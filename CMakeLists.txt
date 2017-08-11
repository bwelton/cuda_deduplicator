cmake_minimum_required (VERSION 2.8.11)
SET(CMAKE_CXX_STANDARD 11)
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

project(cuda_deduplicator)

find_package(Boost COMPONENTS system thread REQUIRED)
find_package(PythonLibs REQUIRED)
find_package(PythonInterp REQUIRED)

if (PYTHON_VERSION_STRING VERSION_GREATER 3.0 OR PYTHON_VERSION_STRING VERSION_LESS 2.7)
	message(WARNING "This package is not tested with python versions < 2.7 or > 3.0 ")
endif(PYTHON_VERSION_STRING VERSION_GREATER 3.0 OR PYTHON_VERSION_STRING VERSION_LESS 2.7)

## Get dyninst library info
include(${CMAKE_SOURCE_DIR}/DyninstInstall.cmake)

