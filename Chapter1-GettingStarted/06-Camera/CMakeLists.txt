cmake_minimum_required(VERSION 3.10)
project(Camera VERSION 1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)


add_library(GLAD STATIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/glad.c")
target_include_directories(GLAD PUBLIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/include")



# OrbitCamera

add_executable(OrbitCamera ${SHADERS} ${CMAKE_SOURCE_DIR}/src/OrbitCamera.cpp ${CMAKE_SOURCE_DIR}/src/Shader.h ${CMAKE_SOURCE_DIR}/src/stb_image.h)

set_property(TARGET OrbitCamera
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            ${CMAKE_SOURCE_DIR})


target_include_directories(OrbitCamera PUBLIC
                                ${CMAKE_SOURCE_DIR}/src
                                ${OPENGL_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                ${GLFW3_INCLUDE_DIR}
																)
target_link_libraries(OrbitCamera PUBLIC
                                GLAD
                                ${GLFW3_LIBRARY}
                                ${OPENGL_LIBRARIES}
                                )
								

# FreeCamera

add_executable(FreeCamera ${SHADERS} ${CMAKE_SOURCE_DIR}/src/FreeCamera.cpp ${CMAKE_SOURCE_DIR}/src/Shader.h ${CMAKE_SOURCE_DIR}/src/stb_image.h)

set_property(TARGET FreeCamera
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            ${CMAKE_SOURCE_DIR})


target_include_directories(FreeCamera PUBLIC
                                ${CMAKE_SOURCE_DIR}/src
                                ${OPENGL_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                ${GLFW3_INCLUDE_DIR}
																)
target_link_libraries(FreeCamera PUBLIC
                                GLAD
                                ${GLFW3_LIBRARY}
                                ${OPENGL_LIBRARIES}
                                )