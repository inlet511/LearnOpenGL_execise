cmake_minimum_required(VERSION 3.10)
project(HelloShaders VERSION 1.0
                      DESCRIPTION "Hello Shaders")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)


add_library(GLAD STATIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/glad.c")
target_include_directories(GLAD PUBLIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/include")


# basic code

file(GLOB SHADERS ${CMAKE_SOURCE_DIR}/shaders/*)

add_executable(${PROJECT_NAME} ${SHADERS} ${CMAKE_SOURCE_DIR}/src/HelloShaders.cpp ${CMAKE_SOURCE_DIR}/src/Shader.h)

set_property(TARGET ${PROGRAM_NAME}
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>")


target_include_directories(${PROJECT_NAME} PUBLIC
                                ${CMAKE_SOURCE_DIR}/src
                                ${OPENGL_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                ${GLFW3_INCLUDE_DIR}
																)
target_link_libraries(${PROJECT_NAME} PUBLIC
                                GLAD
                                ${GLFW3_LIBRARY}
                                ${OPENGL_LIBRARIES}
                                )

