cmake_minimum_required(VERSION 3.0)
project(MongoDaoTest)

###############################################################################
## version ####################################################################
###############################################################################

#set (MongoDaoTest_VERSION_MAJOR 1)
#set (MongoDaoTest_VERSION_MINOR 0)
 
 
###############################################################################
## file globbing ##############################################################
###############################################################################


###############################################################################
## target definitions #########################################################
###############################################################################

#Generate the executable
add_executable(MongoDaoTest TestSuiteMongo.h)

#Help the compiler to decide which language we use
set_target_properties(MongoDaoTest PROPERTIES LINKER_LANGUAGE CXX)

# just for example add some compiler flags
#target_compile_options(MongoDaoTest PUBLIC -std=c++1y -Wall -Wfloat-conversion)


###############################################################################
## dependencies ###############################################################
###############################################################################

# set the MongoDao Lib paths and libs
set(MONGODAOLIB_PREFIX      "/usr/local")
set(MONGODAOLIB_INCLUDE_DIR 	"${MONGODAOLIB_PREFIX}/include")
set(MONGODAOLIB_LIB_DIR     	"${MONGODAOLIB_PREFIX}/lib")
set(MONGODAOLIB_LIBS        	"${MONGODAOLIB_LIB_DIR}/libMongoDaoLib.so")

# set the include path for the app
target_include_directories(MongoDaoTest PRIVATE "${MONGODAOLIB_INCLUDE_DIR}")

# link the app against MongoDBLib
target_link_libraries(MongoDaoTest "${MONGODAOLIB_LIBS}")


###############################################################################
## install ####################################################################
###############################################################################



###############################################################################
## Outputs ####################################################################
###############################################################################

message(STATUS "\n------------ PATHS: ------------")
message(STATUS ">> MONGODAOLIB inc: ${MONGODAOLIB_INCLUDE_DIR}")
message(STATUS ">> MONGODAOLIB lib: ${MONGODAOLIB_LIB_DIR}")
message(STATUS "\n")


