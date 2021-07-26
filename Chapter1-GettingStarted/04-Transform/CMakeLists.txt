cmake_minimum_required(VERSION 3.10)
project(Transform VERSION 1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)


add_library(GLAD STATIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/glad.c")
target_include_directories(GLAD PUBLIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/include")


# basic code

file(GLOB SHADERS ${CMAKE_SOURCE_DIR}/shaders/*)

add_executable(${PROJECT_NAME} ${SHADERS} ${CMAKE_SOURCE_DIR}/src/Textures.cpp ${CMAKE_SOURCE_DIR}/src/Shader.h ${CMAKE_SOURCE_DIR}/src/stb_image.h)

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


# exercise2


# add_executable(exercise2 ${SHADERS} ${CMAKE_SOURCE_DIR}/src/Textures_exercise2.cpp ${CMAKE_SOURCE_DIR}/src/Shader.h ${CMAKE_SOURCE_DIR}/src/stb_image.h)

# set_property(TARGET exercise2
#             PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
#             ${CMAKE_SOURCE_DIR})


# target_include_directories(exercise2 PUBLIC
#                                 ${CMAKE_SOURCE_DIR}/src
#                                 ${OPENGL_INCLUDE_DIRS}
#                                 ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
#                                 ${GLFW3_INCLUDE_DIR}
# 																)
# target_link_libraries(exercise2 PUBLIC
#                                 GLAD
#                                 ${GLFW3_LIBRARY}
#                                 ${OPENGL_LIBRARIES}
#                                 )


# # exercise3


# add_executable(exercise3 ${SHADERS} ${CMAKE_SOURCE_DIR}/src/Textures_exercise3.cpp ${CMAKE_SOURCE_DIR}/src/Shader.h ${CMAKE_SOURCE_DIR}/src/stb_image.h)

# set_property(TARGET exercise3
#             PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
#             ${CMAKE_SOURCE_DIR})


# target_include_directories(exercise3 PUBLIC
#                                 ${CMAKE_SOURCE_DIR}/src
#                                 ${OPENGL_INCLUDE_DIRS}
#                                 ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
#                                 ${GLFW3_INCLUDE_DIR}
# 																)
# target_link_libraries(exercise3 PUBLIC
#                                 GLAD
#                                 ${GLFW3_LIBRARY}
#                                 ${OPENGL_LIBRARIES}
#                                 )
								

# # exercise4


# add_executable(exercise4 ${SHADERS} ${CMAKE_SOURCE_DIR}/src/Textures_exercise4.cpp ${CMAKE_SOURCE_DIR}/src/Shader.h ${CMAKE_SOURCE_DIR}/src/stb_image.h)

# set_property(TARGET exercise4
#             PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
#             ${CMAKE_SOURCE_DIR})


# target_include_directories(exercise4 PUBLIC
#                                 ${CMAKE_SOURCE_DIR}/src
#                                 ${OPENGL_INCLUDE_DIRS}
#                                 ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
#                                 ${GLFW3_INCLUDE_DIR}
# 																)
# target_link_libraries(exercise4 PUBLIC
#                                 GLAD
#                                 ${GLFW3_LIBRARY}
#                                 ${OPENGL_LIBRARIES}
#                                 )