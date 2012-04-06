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
	${INC_PATH}/PathFinding.h
	${INC_PATH}/LevelEditor.h
	${INC_PATH}/Wall.h
	${INC_PATH}/Pistol.h
	${INC_PATH}/GameMaster.h
	${INC_PATH}/Camera.h
	${INC_PATH}/ParamFile.h
	${INC_PATH}/Level.h
	${INC_PATH}/Player.h
	${INC_PATH}/Enemy.h
	${INC_PATH}/Entity.h
	${INC_PATH}/MathUtil.h
	${INC_PATH}/ResourceMgr.h
	${INC_PATH}/Vec2D.h
	${INC_PATH}/World.h
	${INC_PATH}/Weapon.h
	${INC_PATH}/Axe.h
	${INC_PATH}/LevelEditor.h)

set(SRCS 
	${SRC_PATH}/PathFinding.h
	${SRC_PATH}/LevelEditor.cpp
	${SRC_PATH}/Wall.cpp
	${SRC_PATH}/Pistol.cpp
	${SRC_PATH}/GameMaster.cpp
	${SRC_PATH}/Camera.cpp
	${SRC_PATH}/ParamFile.cpp
	${SRC_PATH}/Level.cpp
	${SRC_PATH}/Entity.cpp
	${SRC_PATH}/Enemy.cpp
	${SRC_PATH}/Main.cpp
	${SRC_PATH}/ResourceMgr.cpp
	${SRC_PATH}/World.cpp
	${SRC_PATH}/Player.cpp
	${SRC_PATH}/Weapon.cpp
	${SRC_PATH}/Axe.cpp
	${SRC_PATH}/LevelEditor.cpp)

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/Bin/")

add_executable(Deathliar ${HDRS} ${SRCS})

if (MSVC_IDE)
    # hack to get around the "Debug" and "Release" directories cmake tries to add on Windows
    set_target_properties (Deathliar PROPERTIES PREFIX "../")
endif()

target_link_libraries(Deathliar ${LIBS})