cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(DAO_Test VERSION 0.1 LANGUAGES CXX)

set(_ECLIPSE_VERSION "4.5")

###############################################################################
## file globbing ##############################################################
###############################################################################

file(GLOB SOURCES
 *.h
 *.cpp)

###############################################################################
## target definitions #########################################################
###############################################################################

#Generate the shared library from the sources
add_executable(DAO_Test ${SOURCES})

#Set Debug or Release
set(CMAKE_BUILD_TYPE Debug)

# just for example add some compiler flags
#target_compile_options(DAO_Test PUBLIC -Wextra)

###############################################################################
## compiler definitions########################################################
###############################################################################

#enable c++11 and set it required
set_property(TARGET DAO_Test PROPERTY CXX_STANDARD 11)
set_property(TARGET DAO_Test PROPERTY CXX_STANDARD_REQUIRED ON)

###############################################################################
## dependencies ###############################################################
###############################################################################

# POCO
# set the POCO paths and libs
set(DAO_PREFIX "../build") # the directory containing "include" and "lib"
set(DAO_INCLUDE_DIR"../inc")
set(DAO_LIB_DIR "${DAO_PREFIX}")
set(DAO_LIBS
        "${DAO_LIB_DIR}/libDAO.a")

include_directories(${DAO_INCLUDE})
link_directories(${DAO_LIB_DIR})
target_link_libraries(DAO_Test ${DAO_LIBS})