cmake_minimum_required(VERSION 3.10)
project(HelloTriangle VERSION 1.0
                      DESCRIPTION "The Very first OpenGL program")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)


add_library(GLAD STATIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/glad.c")
target_include_directories(GLAD PUBLIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/include")


# basic code

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/HelloTriangle.cpp)

set_property(TARGET ${PROGRAM_NAME}
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>")


target_include_directories(${PROJECT_NAME} PUBLIC
                                ${CMAKE_SOURCE_DIR}/src
                                ${OPENGL_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                ${GLFW3_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC
                                GLAD
                                ${GLFW3_LIBRARY}
                                ${OPENGL_LIBRARIES}
                                )

# execise 1 -------------------------------------
add_executable(execise1  ${CMAKE_SOURCE_DIR}/src/HelloTriangle-execise1.cpp)
set_property(TARGET execise1
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            "$<TARGET_FILE_DIR:execise1>")


target_include_directories(execise1 PUBLIC
                                ${CMAKE_SOURCE_DIR}/src
                                ${OPENGL_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                ${GLFW3_INCLUDE_DIR})
target_link_libraries(execise1 PUBLIC
                                GLAD
                                ${GLFW3_LIBRARY}
                                ${OPENGL_LIBRARIES}
                                )
								
# execise 2 -------------------------------------
add_executable(execise2  ${CMAKE_SOURCE_DIR}/src/HelloTriangle-execise2.cpp)
set_property(TARGET execise2
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            "$<TARGET_FILE_DIR:execise2>")

target_include_directories(execise2 PUBLIC
                                ${CMAKE_SOURCE_DIR}/src
                                ${OPENGL_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                ${GLFW3_INCLUDE_DIR})
target_link_libraries(execise2 PUBLIC
                                GLAD
                                ${GLFW3_LIBRARY}
                                ${OPENGL_LIBRARIES}
                                )
								
								
# execise 3	-------------------------------------		
add_executable(execise3  ${CMAKE_SOURCE_DIR}/src/HelloTriangle-execise3.cpp)
set_property(TARGET execise3
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
            "$<TARGET_FILE_DIR:execise3>")


target_include_directories(execise3 PUBLIC
                                ${CMAKE_SOURCE_DIR}/src
                                ${OPENGL_INCLUDE_DIRS}
                                ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                ${GLFW3_INCLUDE_DIR})
target_link_libraries(execise3 PUBLIC
                                GLAD
                                ${GLFW3_LIBRARY}
                                ${OPENGL_LIBRARIES}
                                )