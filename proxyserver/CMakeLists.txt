SET(ProjectName proxyserver)

PROJECT(${ProjectName})

INCLUDE_DIRECTORIES(../include)

AUX_SOURCE_DIRECTORY(. DIR_SRCS)

AUX_SOURCE_DIRECTORY(../include/inifile DIR_SRCS)

AUX_SOURCE_DIRECTORY(../include/redis DIR_SRCS)

AUX_SOURCE_DIRECTORY(../include/protobuf DIR_SRCS)

AUX_SOURCE_DIRECTORY(../include/zookeeper DIR_SRCS)

AUX_SOURCE_DIRECTORY(../include/utility DIR_SRCS)

AUX_SOURCE_DIRECTORY(../include/zookeeper DIR_SRCS)

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
	SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -g -O3 -Wall -fPIC -fpermissive ")
ENDIF()

ADD_EXECUTABLE(${ProjectName} ${DIR_SRCS})

TARGET_LINK_LIBRARIES (${ProjectName} muduo_net muduo_base log4cxx hiredis z rt pthread protobuf
				boost_system boost_thread zookeeper_mt)



