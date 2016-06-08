cmake_minimum_required(VERSION 3.0)
project(MongoDaoLib)


#http://stackoverflow.com/questions/21163188/most-simple-but-complete-cmake-example

###############################################################################
## file globbing ##############################################################
###############################################################################

# these instructions search the directory tree when cmake is
# invoked and put all files that match the pattern in the variables 
# `sources` and `data`
file(GLOB_RECURSE SOURCES src/*.cpp inc/*.h)


###############################################################################
## target definitions #########################################################
###############################################################################

#Generate the shared library from the sources
add_library(MongoDaoLib SHARED ${SOURCES})

#Help the compiler to decide which language we use
set_target_properties(MongoDaoLib PROPERTIES LINKER_LANGUAGE CXX)

# just for example add some compiler flags
#target_compile_options(MongoDaoLib PUBLIC -std=c++1y -Wall -Wfloat-conversion)


###############################################################################
## dependencies ###############################################################
###############################################################################

# set the POCO paths and libs
set(POCO_PREFIX      "/usr/local/")
set(POCO_INCLUDE_DIR "${POCO_PREFIX}/include")
set(POCO_LIB_DIR     "${POCO_PREFIX}/lib")
set(POCO_LIBS        "${POCO_LIB_DIR}/libPocoNetd.so"
                     "${POCO_LIB_DIR}/libPocoUtild.so"
                     "${POCO_LIB_DIR}/libPocoMongoDBd.so")

# set the include path for the app
target_include_directories(MongoDaoLib PRIVATE "${POCO_INCLUDE_DIR}")

# link the app against POCO
target_link_libraries(MongoDaoLib "${POCO_LIBS}")

if(Poco_FOUND)    
    message(STATUS "\n------------ linked libary paths ------------")
    message(STATUS ">> Poco libs: ${POCO_LIBS}")
    message(STATUS "\n")                                                                                                                                                                                                                       
endif() 