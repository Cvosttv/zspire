cmake_minimum_required(VERSION 3.10)
project(ZSpireDemo)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "../ZSpire-Framework/cmake")
set(ZSPIRE_INCLUDE_DIR ../ZSpire-Framework/includes)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(OpenAL REQUIRED)
find_package(ALUT REQUIRED)

include_directories(
	${SDL2_INCLUDE_DIR}
	${OPENGL_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}
	${ASSIMP_INCLUDE_DIRS}
	${OPENAL_INCLUDE_DIR}
	${ALUT_INCLUDE_DIR}
	${ZSPIRE_INCLUDE_DIR}
	)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fpermissive")

add_executable(main
	src/demo.cpp
	)
add_library(framework STATIC IMPORTED)
set_target_properties(framework PROPERTIES
	IMPORTED_LOCATION ../ZSpire-Framework/libZSpireFramework.a)

target_link_libraries(
	main framework
	${SDL2_LIBRARY}
	${OPENGL_LIBRARY}
	${GLEW_LIBRARIES}
	${ASSIMP_LIBRARIES}
	${OPENAL_LIBRARY}
	${ALUT_LIBRARIES})
