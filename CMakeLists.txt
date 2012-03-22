cmake_minimum_required(VERSION 2.6)
project(Deathliar)

set(INC_PATH ${PROJECT_SOURCE_DIR}/Include)
set(SRC_PATH ${PROJECT_SOURCE_DIR}/Source)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/CMake/")

if (CMAKE_BUILD_TYPE STREQUAL "")
	#Overload default option, to prevent none CMAKE_BUILD_TYPE
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build, options are: Debug or Release" FORCE)
endif ()

find_package(SFML REQUIRED SYSTEM GRAPHICS WINDOW)

include_directories(${SFML_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/Include)

set(LIBS ${LIBS} ${SFML_LIBRARIES})

set(HDRS 
	${INC_PATH}/Entity.h
	${INC_PATH}/MathUtil.h
	${INC_PATH}/ResourceMgr.h
	${INC_PATH}/Vec2D.h
	${INC_PATH}/World.h
)
set(SRCS 
	${SRC_PATH}/Entity.cpp
	${SRC_PATH}/Main.cpp
	${SRC_PATH}/ResourceMgr.cpp
	${SRC_PATH}/World.cpp)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/Bin/")

add_executable(Bridge ${HDRS} ${SRCS})
target_link_libraries(Bridge ${LIBS})