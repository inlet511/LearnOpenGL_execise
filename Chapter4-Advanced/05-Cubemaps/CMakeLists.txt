cmake_minimum_required(VERSION 3.10)
project(CubeMapsSolution VERSION 1.0.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenGL REQUIRED)

# 为GLAD创建target
add_library(GLAD STATIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/glad.c")
target_include_directories(GLAD PUBLIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/include")



file(GLOB SHADERS ${CMAKE_SOURCE_DIR}/Res/shaders/*)

###############################################################################################################	
 #添加可执行目标(主exe)
add_executable(CubeMaps ${SHADERS}
				${CMAKE_SOURCE_DIR}/src/Cubemaps.cpp
				${CMAKE_SOURCE_DIR}/src/Camera.h
				${CMAKE_SOURCE_DIR}/src/Mesh.h
				${CMAKE_SOURCE_DIR}/src/Model.h
				${CMAKE_SOURCE_DIR}/src/Shader.h
				)

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

###############################################################################################################	
 # Reflection
add_executable(Reflection  ${SHADERS}
				${CMAKE_SOURCE_DIR}/src/Reflection.cpp
				${CMAKE_SOURCE_DIR}/src/Camera.h
				${CMAKE_SOURCE_DIR}/src/Mesh.h
				${CMAKE_SOURCE_DIR}/src/Model.h
				${CMAKE_SOURCE_DIR}/src/Shader.h
)

# Set working directory
set_property(TARGET Reflection
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
			${CMAKE_SOURCE_DIR}
            )

#给主exe文件增加include
target_include_directories(Reflection PUBLIC 
                                    ${CMAKE_SOURCE_DIR}/src
                                    ${OPENGL_INCLUDE_DIRS}
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/include
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                    ${GLFW3_INCLUDE_DIR}
                                    )

#给主exe文件增加库文件
 target_link_libraries(Reflection PUBLIC 
                                    GLAD
                                    ${GLFW3_LIBRARY} 
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/lib/assimp-vc142-mtd.lib 
                                    ${OPENGL_LIBRARIES}
                                    )
									
###############################################################################################################				
 # Refraction
add_executable(Refraction  ${SHADERS}
				${CMAKE_SOURCE_DIR}/src/Refraction.cpp
				${CMAKE_SOURCE_DIR}/src/Camera.h
				${CMAKE_SOURCE_DIR}/src/Mesh.h
				${CMAKE_SOURCE_DIR}/src/Model.h
				${CMAKE_SOURCE_DIR}/src/Shader.h
)

# Set working directory
set_property(TARGET Refraction
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
			${CMAKE_SOURCE_DIR}
            )

#给主exe文件增加include
target_include_directories(Refraction PUBLIC 
                                    ${CMAKE_SOURCE_DIR}/src
                                    ${OPENGL_INCLUDE_DIRS}
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/include
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                    ${GLFW3_INCLUDE_DIR}
                                    )

#给主exe文件增加库文件
 target_link_libraries(Refraction PUBLIC 
                                    GLAD
                                    ${GLFW3_LIBRARY} 
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/lib/assimp-vc142-mtd.lib 
                                    ${OPENGL_LIBRARIES}
                                    )
###############################################################################################################					
# Exercise1
add_executable(Exercise1  ${SHADERS}
				${CMAKE_SOURCE_DIR}/src/Exercise1.cpp
				${CMAKE_SOURCE_DIR}/src/Camera.h
				${CMAKE_SOURCE_DIR}/src/Mesh.h
				${CMAKE_SOURCE_DIR}/src/Model.h
				${CMAKE_SOURCE_DIR}/src/Shader.h
)

# Set working directory
set_property(TARGET Exercise1
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
			${CMAKE_SOURCE_DIR}
            )

#给主exe文件增加include
target_include_directories(Exercise1 PUBLIC 
                                    ${CMAKE_SOURCE_DIR}/src
                                    ${OPENGL_INCLUDE_DIRS}
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/include
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                    ${GLFW3_INCLUDE_DIR}
                                    )

#给主exe文件增加库文件
 target_link_libraries(Exercise1 PUBLIC 
                                    GLAD
                                    ${GLFW3_LIBRARY} 
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/lib/assimp-vc142-mtd.lib 
                                    ${OPENGL_LIBRARIES}
                                    )
###############################################################################################################										
set_property(DIRECTORY ${CMAKE_SOURCE_DIR} 
			PROPERTY VS_STARTUP_PROJECT 
			Exercise1)

