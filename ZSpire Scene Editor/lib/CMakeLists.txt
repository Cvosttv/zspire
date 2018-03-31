CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(ZSpireEditorLib)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "./cmake")

FIND_PACKAGE(SDL2 REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)
FIND_PACKAGE(ASSIMP REQUIRED)

INCLUDE_DIRECTORIES(
	${SDL2_INCLUDE_DIR}
	${OPENGL_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}
	${ASSIMP_INCLUDE_DIRS}
	includes)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fpermissive -c")

ADD_LIBRARY(ZSpireEditorLib STATIC
	IMGUI/imgui.cpp
	IMGUI/imgui_demo.cpp
	IMGUI/imgui_draw.cpp
	src/file_window.cpp
	src/GameObject.cpp
	src/imgui_impl_sdl_gl3.cpp
	src/Light.cpp
	src/objects_window.cpp
	src/property_inspector.cpp
	src/Renderer.cpp
	src/Resources.cpp
	src/resources_window.cpp
	src/scene_loader.cpp
	src/startup_window.cpp
	src/zs-camera.cpp
	src/zs-math.cpp
	src/zs-mesh.cpp
	src/zs-mesh-loader.cpp
	src/zs-shader.cpp
	src/zs-texture.cpp
	src/zs-transform.cpp)

TARGET_LINK_LIBRARIES(
	ZSpireEditorLib
	${SDL2_LIBRARY}
	${OPENGL_LIBRARY}
	${GLEW_LIBRARIES}
	${ASSIMP_LIBRARIES})