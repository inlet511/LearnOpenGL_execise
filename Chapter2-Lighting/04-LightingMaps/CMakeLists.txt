cmake_minimum_required(VERSION 3.10)
project(LightingMaps VERSION 1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)


add_library(GLAD STATIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/glad.c")
target_include_directories(GLAD PUBLIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/include")

file(GLOB SHADERS ${CMAKE_SOURCE_DIR}/shaders/*)
file(GLOB_RECURSE  IAMGUI ${CMAKE_SOURCE_DIR}/../../ThirdParty/imgui/*.cpp)


# LightingMaps
add_executable(LightingMaps 
  ${SHADERS}
  ${IAMGUI}
  ${CMAKE_SOURCE_DIR}/src/LightingMaps.cpp
  ${CMAKE_SOURCE_DIR}/src/Camera.h
  ${CMAKE_SOURCE_DIR}/src/Shader.h
  ${CMAKE_SOURCE_DIR}/src/stb_image.h)

set_property(TARGET  LightingMaps
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            ${CMAKE_SOURCE_DIR})


target_include_directories(LightingMaps PUBLIC
                                ${CMAKE_SOURCE_DIR}/src
                                ${OPENGL_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                ${GLFW3_INCLUDE_DIR}
								${CMAKE_SOURCE_DIR}/../../ThirdParty/imgui
								)
target_link_libraries(LightingMaps PUBLIC
                                GLAD
                                ${GLFW3_LIBRARY}
                                ${OPENGL_LIBRARIES}
                                )

# Exercise4
add_executable(Exercise4 
  ${SHADERS}
  ${IAMGUI}
  ${CMAKE_SOURCE_DIR}/src/Exercise4.cpp
  ${CMAKE_SOURCE_DIR}/src/Camera.h
  ${CMAKE_SOURCE_DIR}/src/Shader.h
  ${CMAKE_SOURCE_DIR}/src/stb_image.h)

set_property(TARGET  Exercise4
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            ${CMAKE_SOURCE_DIR})


target_include_directories(Exercise4 PUBLIC
                                ${CMAKE_SOURCE_DIR}/src
                                ${OPENGL_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                ${GLFW3_INCLUDE_DIR}
								${CMAKE_SOURCE_DIR}/../../ThirdParty/imgui
								)
target_link_libraries(Exercise4 PUBLIC
                                GLAD
                                ${GLFW3_LIBRARY}
                                ${OPENGL_LIBRARIES}
                                )