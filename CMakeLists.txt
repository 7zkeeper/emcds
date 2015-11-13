PROJECT(dataservice_rdd)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#ADD_DEFINITIONS(-std=c++11)

SET(ENV{Platform} x64)

SET(ENV{Configuration} Debug)

SET(CompilerSetting "g++")

SET(LIBRARY_OUTPUT_PATH lib/$ENV{Platform}/$ENV{Configuration})

SET(EXECUTABLE_OUTPUT_PATH $ENV{Configuration})

SET(LINK_LIBPATH lib/$ENV{Platform}/$ENV{Configuration})

ADD_SUBDIRECTORY(datatask)

ADD_SUBDIRECTORY(proxyserver)

#ADD_SUBDIRECTORY(mongotest)
