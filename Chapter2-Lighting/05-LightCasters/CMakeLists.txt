cmake_minimum_required(VERSION 3.10)
project(LightCasters VERSION 1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)


add_library(GLAD STATIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/glad.c")
target_include_directories(GLAD PUBLIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/include")

file(GLOB SHADERS ${CMAKE_SOURCE_DIR}/shaders/*)
file(GLOB_RECURSE  IAMGUI ${CMAKE_SOURCE_DIR}/../../ThirdParty/imgui/*.cpp)


# DirectionalLight
add_executable(DirectionalLight 
  ${SHADERS}
  ${IAMGUI}
  ${CMAKE_SOURCE_DIR}/src/DirectionalLight.cpp
  ${CMAKE_SOURCE_DIR}/src/Camera.h
  ${CMAKE_SOURCE_DIR}/src/Shader.h
  ${CMAKE_SOURCE_DIR}/src/stb_image.h)

set_property(TARGET  DirectionalLight
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            ${CMAKE_SOURCE_DIR})


target_include_directories(DirectionalLight PUBLIC
                                ${CMAKE_SOURCE_DIR}/src
                                ${OPENGL_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                ${GLFW3_INCLUDE_DIR}
								${CMAKE_SOURCE_DIR}/../../ThirdParty/imgui
								)
target_link_libraries(DirectionalLight PUBLIC
                                GLAD
                                ${GLFW3_LIBRARY}
                                ${OPENGL_LIBRARIES}
                                )

# PointLight
add_executable(PointLight 
  ${SHADERS}
  ${IAMGUI}
  ${CMAKE_SOURCE_DIR}/src/PointLight.cpp
  ${CMAKE_SOURCE_DIR}/src/Camera.h
  ${CMAKE_SOURCE_DIR}/src/Shader.h
  ${CMAKE_SOURCE_DIR}/src/stb_image.h)

set_property(TARGET  PointLight
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            ${CMAKE_SOURCE_DIR})


target_include_directories(PointLight PUBLIC
                                ${CMAKE_SOURCE_DIR}/src
                                ${OPENGL_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                ${GLFW3_INCLUDE_DIR}
								${CMAKE_SOURCE_DIR}/../../ThirdParty/imgui
								)
target_link_libraries(PointLight PUBLIC
                                GLAD
                                ${GLFW3_LIBRARY}
                                ${OPENGL_LIBRARIES}
                                )

# SpotLight
add_executable(SpotLight 
  ${SHADERS}
  ${IAMGUI}
  ${CMAKE_SOURCE_DIR}/src/SpotLight.cpp
  ${CMAKE_SOURCE_DIR}/src/Camera.h
  ${CMAKE_SOURCE_DIR}/src/Shader.h
  ${CMAKE_SOURCE_DIR}/src/stb_image.h)

set_property(TARGET  SpotLight
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            ${CMAKE_SOURCE_DIR})


target_include_directories(SpotLight PUBLIC
                                ${CMAKE_SOURCE_DIR}/src
                                ${OPENGL_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                ${GLFW3_INCLUDE_DIR}
								${CMAKE_SOURCE_DIR}/../../ThirdParty/imgui
								)
target_link_libraries(SpotLight PUBLIC
                                GLAD
                                ${GLFW3_LIBRARY}
                                ${OPENGL_LIBRARIES}
                                )
								
#SoftEdge_SpotLight

add_executable(SoftEdge_SpotLight 
  ${SHADERS}
  ${IAMGUI}
  ${CMAKE_SOURCE_DIR}/src/SoftEdge_SpotLight.cpp
  ${CMAKE_SOURCE_DIR}/src/Camera.h
  ${CMAKE_SOURCE_DIR}/src/Shader.h
  ${CMAKE_SOURCE_DIR}/src/stb_image.h)

set_property(TARGET  SoftEdge_SpotLight
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            ${CMAKE_SOURCE_DIR})


target_include_directories(SoftEdge_SpotLight PUBLIC
                                ${CMAKE_SOURCE_DIR}/src
                                ${OPENGL_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                ${GLFW3_INCLUDE_DIR}
								${CMAKE_SOURCE_DIR}/../../ThirdParty/imgui
								)
target_link_libraries(SoftEdge_SpotLight PUBLIC
                                GLAD
                                ${GLFW3_LIBRARY}
                                ${OPENGL_LIBRARIES}
                                )