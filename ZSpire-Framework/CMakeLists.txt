cmake_minimum_required(VERSION 3.10)
project(ZSpireFramework)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "./cmake")
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(OpenAL REQUIRED)
find_package(ALUT REQUIRED)
find_package(Qt5Widgets REQUIRED)

include_directories(
	${SDL2_INCLUDE_DIR}
	${OPENGL_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}
	${ASSIMP_INCLUDE_DIRS}
	${OPENAL_INCLUDE_DIR}
	${ALUT_INCLUDE_DIR}
	include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fpermissive -c")
add_library(ZSpireFramework STATIC
	src/zs-app.cpp
	src/zs-audio-manager.cpp
	src/zs-audio-source.cpp
	src/zs-camera.cpp
	src/zs-deffered-render.cpp
	src/zs-errors-checker.cpp
	src/zs-forward-render.cpp
	src/zs-game-object.cpp
	src/zs-input.cpp
	src/zs-light.cpp
	src/zs-math.cpp
	src/zs-mesh.cpp
	src/zs-mesh-loader.cpp
	src/zs-scene.cpp
	src/zs-shader.cpp
	src/zs-text-renderer.cpp
	src/zs-texture.cpp
	src/zs-transform.cpp)

qt5_use_modules(ZSpireFramework Widgets Core)

target_link_libraries(
	ZSpireFramework
	${SDL2_LIBRARY}
	${OPENGL_LIBRARY}
	${GLEW_LIBRARIES}
	${ASSIMP_LIBRARIES}
	${OPENAL_LIBRARY}
	${ALUT_LIBRARIES})
