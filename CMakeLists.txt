cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(MongoDao VERSION 0.1 LANGUAGES CXX)

set(_ECLIPSE_VERSION "4.5")

###############################################################################
## file globbing ##############################################################
###############################################################################

file(GLOB SOURCES
 	src/Connector.cpp)

message("Following sources found:")
foreach(a ${SOURCES})
  message("${a}")
endforeach()

###############################################################################
## target definitions #########################################################
###############################################################################

#Generate the shared library from the sources
add_library(MongoDao ${SOURCES})

#Set Debug or Release
set(CMAKE_BUILD_TYPE Debug)

# just for example add some compiler flags
#target_compile_options(MongoDao PUBLIC -Wextra)

###############################################################################
## compiler definitions########################################################
###############################################################################

#enable c++11 and set it required
set_property(TARGET MongoDao PROPERTY CXX_STANDARD 11)
set_property(TARGET MongoDao PROPERTY CXX_STANDARD_REQUIRED ON)

###############################################################################
## dependencies ###############################################################
###############################################################################

# POCO
# set the POCO paths and libs
set(POCO_PREFIX "/usr/local") # the directory containing "include" and "lib"
set(POCO_INCLUDE_DIR"${POCO_PREFIX}/include")
set(POCO_LIB_DIR "${POCO_PREFIX}/lib")
set(POCO_LIBS
        "${POCO_LIB_DIR}/libPocoNet.so"
        "${POCO_LIB_DIR}/libPocoUtil.so"
        "${POCO_LIB_DIR}/libPocoFoundation.so"
        "${POCO_LIB_DIR}/libPocoJSON.so"
        "${POCO_LIB_DIR}/libPocoMongoDB.so")

#set(Poco_USE_STATIC_LIBS OFF) 
#set(Poco_USE_MULTITHREADED ON)  
#set(Poco_USE_STATIC_RUNTIME OFF) 
#find_package(Poco 1.7.3 EXACT COMPONENTS PocoNet PocoUtil PocoFoundation PocoJSON PocoMongoDB regex date_time log log_setup REQUIRED)

# THREADS
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(${POCO_INCLUDE})
link_directories(${POCO_LIB_DIR})
target_link_libraries(MongoDao ${POCO_LIBS} Threads::Threads)