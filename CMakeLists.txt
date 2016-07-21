cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(MongoDao VERSION 0.1 LANGUAGES CXX)

set(_ECLIPSE_VERSION "4.5")

###############################################################################
## file globbing ##############################################################
###############################################################################

file(GLOB SOURCES src/Connector.cpp)

include_directories(inc)  
 	

###############################################################################
## target definitions #########################################################
###############################################################################

#Generate the shared library from the sources
add_library(MongoDao SHARED ${SOURCES})

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

####################
##  Installation  ##
####################

# Set installation destination folder for .so and .h files.
# Change the destination folder
###############################
set(INSTALLATION_DIR "/home/developer/workspace/SpiderBite/env/mongodao/lib")
set(HEADER_DIR "/home/developer/workspace/SpiderBite/env/mongodao/inc")

# Set header location that will be copied
file(GLOB HEADERS inc/*)

# Install .so file
#install(TARGETS MongoDao DESTINATION ${INSTALLATION_DIR}
#	PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ WORLD_WRITE)

INSTALL( FILES "${CMAKE_CURRENT_SOURCE_DIR}/libMongoDao.so"
	DESTINATION ${INSTALLATION_DIR}
	PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ WORLD_WRITE)

# Install .h files
foreach(ITEM ${HEADERS})
   IF( IS_DIRECTORY "${ITEM}" )
      LIST( APPEND DIRS_TO_DEPLOY "${ITEM}" )
   ELSE()
      LIST( APPEND FILES_TO_DEPLOY "${ITEM}" )
   ENDIF()
endforeach()

INSTALL( FILES ${FILES_TO_DEPLOY} DESTINATION ${HEADER_DIR} 
	PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ WORLD_WRITE)

INSTALL( DIRECTORY ${DIRS_TO_DEPLOY} DESTINATION ${HEADER_DIR} )
	



