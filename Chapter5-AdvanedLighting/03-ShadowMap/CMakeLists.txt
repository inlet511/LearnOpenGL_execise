cmake_minimum_required(VERSION 3.10)
project(ShadowMapping VERSION 1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)


add_library(GLAD STATIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/glad.c")
target_include_directories(GLAD PUBLIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/include")

file(GLOB SHADERS ${CMAKE_SOURCE_DIR}/shaders/*)
file(GLOB_RECURSE  IAMGUI ${CMAKE_SOURCE_DIR}/../../ThirdParty/imgui/*.cpp)


# ShadowMapping
add_executable(ShadowMapping 
  ${SHADERS}
  ${IAMGUI}
  ${CMAKE_SOURCE_DIR}/src/ShadowMapping.cpp
  ${CMAKE_SOURCE_DIR}/src/Camera.h
  ${CMAKE_SOURCE_DIR}/src/Shader.h
  ${CMAKE_SOURCE_DIR}/src/stb_image.h)

set_property(TARGET  ShadowMapping
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            ${CMAKE_SOURCE_DIR})


target_include_directories(ShadowMapping PUBLIC
                                ${CMAKE_SOURCE_DIR}/src
                                ${OPENGL_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                ${GLFW3_INCLUDE_DIR}
								${CMAKE_SOURCE_DIR}/../../ThirdParty/imgui
								)
target_link_libraries(ShadowMapping PUBLIC
                                GLAD
                                ${GLFW3_LIBRARY}
                                ${OPENGL_LIBRARIES}
                                )