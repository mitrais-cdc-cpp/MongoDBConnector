cmake_minimum_required(VERSION 3.1)
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
add_executable(MongoDaoTest TestSuiteMongo.cpp)

# just for example add some compiler flags
#target_compile_options(MongoDaoTest PUBLIC -Wall)

set_property(TARGET MongoDaoTest PROPERTY CXX_STANDARD 11)


###############################################################################
## dependencies ###############################################################
###############################################################################

# set the MongoDao Lib paths and libs
set(MONGODAOLIB_PREFIX      "/usr/local")
set(MONGODAOLIB_INCLUDE_DIR 	"${MONGODAOLIB_PREFIX}/include")
set(MONGODAOLIB_LIB_DIR     	"${MONGODAOLIB_PREFIX}/lib")
set(MONGODAOLIB_LIBS        	"${MONGODAOLIB_LIB_DIR}/libMongoDaoLib.so")

# set the POCO paths and libs
set(POCO_PREFIX      "/usr/local")
set(POCO_INCLUDE_DIR "${POCO_PREFIX}/include")
set(POCO_LIB_DIR     "${POCO_PREFIX}/lib")
set(POCO_LIBS        "${POCO_LIB_DIR}/libPocoNetd.so"
                     "${POCO_LIB_DIR}/libPocoUtild.so"
                     "${POCO_LIB_DIR}/libPocoMongoDBd.so")

# set the include path for the app
target_include_directories(MongoDaoTest PRIVATE 
						"${POCO_INCLUDE_DIR}" 
						"${MONGODAOLIB_INCLUDE_DIR}")

# link the app against POCO
target_link_libraries(MongoDaoTest PRIVATE 
						"${POCO_LIBS}" 
						"${MONGODAOLIB_LIBS}")


###############################################################################
## install ####################################################################
###############################################################################



###############################################################################
## Outputs ####################################################################
###############################################################################

message(STATUS "\n------------ PATHS: ------------")
message(STATUS ">> MONGODAOLIB inc: ${MONGODAOLIB_INCLUDE_DIR}")
message(STATUS ">> MONGODAOLIB lib: ${MONGODAOLIB_LIB_DIR}")
message(STATUS ">> Poco inc: ${POCO_INCLUDE_DIR}")
message(STATUS ">> Poco lib: ${POCO_LIB_DIR}")
message(STATUS "\n")


