cmake_minimum_required(VERSION 3.10)
project(CubeMapsSolution VERSION 1.0.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenGL REQUIRED)

# 为GLAD创建target
add_library(GLAD STATIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/glad.c")
target_include_directories(GLAD PUBLIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/include")


aux_source_directory(${CMAKE_SOURCE_DIR}/src/ SOURCEFILES) 
file(GLOB SHADERS ${CMAKE_SOURCE_DIR}/Res/shaders/*)


 #添加可执行目标(主exe)
add_executable(CubeMaps ${SOURCEFILES} ${SHADERS})

# Set working directory
set_property(TARGET CubeMaps
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
			${CMAKE_SOURCE_DIR}
            )

#给主exe文件增加include
target_include_directories(CubeMaps PUBLIC 
                                    ${CMAKE_SOURCE_DIR}/src
                                    ${OPENGL_INCLUDE_DIRS}
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/include
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                    ${GLFW3_INCLUDE_DIR}
                                    )

#给主exe文件增加库文件
 target_link_libraries(CubeMaps PUBLIC 
                                    GLAD
                                    ${GLFW3_LIBRARY} 
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/lib/assimp-vc142-mtd.lib 
                                    ${OPENGL_LIBRARIES}
                                    )


set_property(DIRECTORY ${CMAKE_SOURCE_DIR} 
			PROPERTY VS_STARTUP_PROJECT 
			CubeMaps)

