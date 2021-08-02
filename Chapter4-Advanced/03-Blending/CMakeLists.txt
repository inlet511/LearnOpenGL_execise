cmake_minimum_required(VERSION 3.10)
project(Blending VERSION 1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(Assimp SHARED IMPORTED)
set_property(TARGET Assimp PROPERTY IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/bin/assimp-vc142-mtd.dll)
set_property(TARGET Assimp PROPERTY IMPORTED_IMPLIB ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/bin/assimp-vc142-mtd.lib)

# add GLAD
add_library(GLAD STATIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/glad.c")
target_include_directories(GLAD PUBLIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/include")

# add Shader files to project
file(GLOB SHADERS ${CMAKE_SOURCE_DIR}/shaders/*)

# add imgui cpp files to project
file(GLOB_RECURSE  IAMGUI ${CMAKE_SOURCE_DIR}/../../ThirdParty/imgui/*.cpp)



# AlphaClipping
add_executable(AlphaClipping 
  ${SHADERS}
  ${IAMGUI}
  ${CMAKE_SOURCE_DIR}/src/AlphaClipping.cpp
  ${CMAKE_SOURCE_DIR}/src/Camera.h
  ${CMAKE_SOURCE_DIR}/src/Mesh.h
  ${CMAKE_SOURCE_DIR}/src/Model.h
  ${CMAKE_SOURCE_DIR}/src/Shader.h
  ${CMAKE_SOURCE_DIR}/src/stb_loader.cpp
  )

set_property(TARGET  AlphaClipping
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            ${CMAKE_SOURCE_DIR})


target_include_directories(AlphaClipping PUBLIC
                                ${CMAKE_SOURCE_DIR}/src
                                ${OPENGL_INCLUDE_DIRS}
								${GLFW3_INCLUDE_DIR}
                                ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm                                
								${CMAKE_SOURCE_DIR}/../../ThirdParty/imgui
								${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/include
								)

target_link_libraries(AlphaClipping PUBLIC
                                GLAD
                                ${GLFW3_LIBRARY}
                                ${OPENGL_LIBRARIES}
								Assimp
                                )
								
# Transparent
add_executable(Transparent 
  ${SHADERS}
  ${IAMGUI}
  ${CMAKE_SOURCE_DIR}/src/Transparent.cpp
  ${CMAKE_SOURCE_DIR}/src/Camera.h
  ${CMAKE_SOURCE_DIR}/src/Mesh.h
  ${CMAKE_SOURCE_DIR}/src/Model.h
  ${CMAKE_SOURCE_DIR}/src/Shader.h
  ${CMAKE_SOURCE_DIR}/src/stb_loader.cpp
  )

set_property(TARGET  Transparent
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            ${CMAKE_SOURCE_DIR})


target_include_directories(Transparent PUBLIC
                                ${CMAKE_SOURCE_DIR}/src
                                ${OPENGL_INCLUDE_DIRS}
								${GLFW3_INCLUDE_DIR}
                                ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm                                
								${CMAKE_SOURCE_DIR}/../../ThirdParty/imgui
								${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/include
								)

target_link_libraries(Transparent PUBLIC
                                GLAD
                                ${GLFW3_LIBRARY}
                                ${OPENGL_LIBRARIES}
								Assimp
                                )								