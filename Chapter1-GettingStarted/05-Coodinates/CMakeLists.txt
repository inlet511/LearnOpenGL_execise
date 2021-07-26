cmake_minimum_required(VERSION 3.10)
project(Coordinates VERSION 1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)


add_library(GLAD STATIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/glad.c")
target_include_directories(GLAD PUBLIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/include")


# basic code

file(GLOB SHADERS ${CMAKE_SOURCE_DIR}/shaders/*)

add_executable(${PROJECT_NAME} ${SHADERS} ${CMAKE_SOURCE_DIR}/src/Coordinates.cpp ${CMAKE_SOURCE_DIR}/src/Shader.h ${CMAKE_SOURCE_DIR}/src/stb_image.h)

set_property(TARGET ${PROGRAM_NAME}
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            ${CMAKE_SOURCE_DIR})


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


# morecubes


add_executable(morecubes ${SHADERS} ${CMAKE_SOURCE_DIR}/src/MoreCubes.cpp ${CMAKE_SOURCE_DIR}/src/Shader.h ${CMAKE_SOURCE_DIR}/src/stb_image.h)

set_property(TARGET morecubes
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            ${CMAKE_SOURCE_DIR})


target_include_directories(morecubes PUBLIC
                                ${CMAKE_SOURCE_DIR}/src
                                ${OPENGL_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                ${GLFW3_INCLUDE_DIR}
																)
target_link_libraries(morecubes PUBLIC
                                GLAD
                                ${GLFW3_LIBRARY}
                                ${OPENGL_LIBRARIES}
                                )

# exercise01


add_executable(exercise01 ${SHADERS} ${CMAKE_SOURCE_DIR}/src/Exercise01.cpp ${CMAKE_SOURCE_DIR}/src/Shader.h ${CMAKE_SOURCE_DIR}/src/stb_image.h)

set_property(TARGET exercise01
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            ${CMAKE_SOURCE_DIR})


target_include_directories(exercise01 PUBLIC
                                ${CMAKE_SOURCE_DIR}/src
                                ${OPENGL_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                ${GLFW3_INCLUDE_DIR}
																)
target_link_libraries(exercise01 PUBLIC
                                GLAD
                                ${GLFW3_LIBRARY}
                                ${OPENGL_LIBRARIES}
                                )

# exercise02

add_executable(exercise02 ${SHADERS} ${CMAKE_SOURCE_DIR}/src/Exercise02.cpp ${CMAKE_SOURCE_DIR}/src/Shader.h ${CMAKE_SOURCE_DIR}/src/stb_image.h)

set_property(TARGET exercise02
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            ${CMAKE_SOURCE_DIR})


target_include_directories(exercise02 PUBLIC
                                ${CMAKE_SOURCE_DIR}/src
                                ${OPENGL_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                ${GLFW3_INCLUDE_DIR}
																)
target_link_libraries(exercise02 PUBLIC
                                GLAD
                                ${GLFW3_LIBRARY}
                                ${OPENGL_LIBRARIES}
                                )

# exercise03

add_executable(exercise03 ${SHADERS} ${CMAKE_SOURCE_DIR}/src/Exercise03.cpp ${CMAKE_SOURCE_DIR}/src/Shader.h ${CMAKE_SOURCE_DIR}/src/stb_image.h)

set_property(TARGET exercise03
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            ${CMAKE_SOURCE_DIR})


target_include_directories(exercise03 PUBLIC
                                ${CMAKE_SOURCE_DIR}/src
                                ${OPENGL_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                ${GLFW3_INCLUDE_DIR}
																)
target_link_libraries(exercise03 PUBLIC
                                GLAD
                                ${GLFW3_LIBRARY}
                                ${OPENGL_LIBRARIES}
                                )