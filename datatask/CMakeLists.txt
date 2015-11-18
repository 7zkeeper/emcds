SET(ProjectName datatask)

PROJECT(${ProjectName})

INCLUDE_DIRECTORIES(../include)

AUX_SOURCE_DIRECTORY(. DIR_SRCS)

AUX_SOURCE_DIRECTORY(../include/inifile DIR_SRCS)

AUX_SOURCE_DIRECTORY(../include/redis DIR_SRCS)

AUX_SOURCE_DIRECTORY(../include/mongodb DIR_SRCS)

AUX_SOURCE_DIRECTORY(../include/zookeeper DIR_SRCS)

AUX_SOURCE_DIRECTORY(../include/utility DIR_SRCS)

SET(CMAKE_CXX_COMPILER ${CompilerSetting})

IF ($ENV{Configuration} STREQUAL Debug)
	SET(CMAKE_BUILD_TYPE Debug)
ELSE()
	SET(CMAKE_BUILD_TYPE Release)
ENDIF()

#LINK_DIRECTORIES(${LINK_LIBPATH})

IF ($ENV{Configuration} STREQUAL Debug)
	SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -g -O0 -Wall -fPIC -fpermissive ")
ELSE()
	SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -g -O3 -Wall -fPIC -fpemissive ")
ENDIF()

ADD_EXECUTABLE(${ProjectName} ${DIR_SRCS})
TARGET_LINK_LIBRARIES (${ProjectName} log4cxx zookeeper_mt z boost_thread jansson protobuf
						boost_filesystem boost_program_options boost_system 
						boost_regex mongoclient)






