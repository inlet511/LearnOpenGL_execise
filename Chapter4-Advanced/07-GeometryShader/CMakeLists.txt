cmake_minimum_required(VERSION 3.10)
project(GeometryShader VERSION 1.0.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(OpenGL REQUIRED)

# 为GLAD创建target
add_library(GLAD STATIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/glad.c")
target_include_directories(GLAD PUBLIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/include")



file(GLOB SHADERS ${CMAKE_SOURCE_DIR}/Res/shaders/*)

###############################################################################################################	

add_executable(GeoShader
				${CMAKE_SOURCE_DIR}/src/GeoShader.cpp
				${CMAKE_SOURCE_DIR}/src/Camera.h
				${CMAKE_SOURCE_DIR}/src/Mesh.h
				${CMAKE_SOURCE_DIR}/src/Model.h
				${CMAKE_SOURCE_DIR}/src/Shader.h
				${CMAKE_SOURCE_DIR}/src/stb_loader.cpp
				${CMAKE_SOURCE_DIR}/Res/shaders/vert.vert
				${CMAKE_SOURCE_DIR}/Res/shaders/geo.geom
				${CMAKE_SOURCE_DIR}/Res/shaders/frag.frag
				)

# Set working directory
set_property(TARGET GeoShader
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
			${CMAKE_SOURCE_DIR}
            )

#给主exe文件增加include
target_include_directories(GeoShader PUBLIC 
                                    ${CMAKE_SOURCE_DIR}/src
                                    ${OPENGL_INCLUDE_DIRS}
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/include
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                    ${GLFW3_INCLUDE_DIR}
                                    )

#给主exe文件增加库文件
 target_link_libraries(GeoShader PUBLIC 
                                    GLAD
                                    ${GLFW3_LIBRARY} 
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/lib/assimp-vc142-mtd.lib 
                                    ${OPENGL_LIBRARIES}
                                    )
									
###############################################################################################################	

add_executable(DrawHouse
				${CMAKE_SOURCE_DIR}/src/DrawHouse.cpp
				${CMAKE_SOURCE_DIR}/src/Camera.h
				${CMAKE_SOURCE_DIR}/src/Mesh.h
				${CMAKE_SOURCE_DIR}/src/Model.h
				${CMAKE_SOURCE_DIR}/src/Shader.h
				${CMAKE_SOURCE_DIR}/src/stb_loader.cpp
				${CMAKE_SOURCE_DIR}/Res/shaders/house.vert
				${CMAKE_SOURCE_DIR}/Res/shaders/house.geom
				${CMAKE_SOURCE_DIR}/Res/shaders/house.frag
				)

# Set working directory
set_property(TARGET DrawHouse
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
			${CMAKE_SOURCE_DIR}
            )

#给主exe文件增加include
target_include_directories(DrawHouse PUBLIC 
                                    ${CMAKE_SOURCE_DIR}/src
                                    ${OPENGL_INCLUDE_DIRS}
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/include
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                    ${GLFW3_INCLUDE_DIR}
                                    )

#给主exe文件增加库文件
 target_link_libraries(DrawHouse PUBLIC 
                                    GLAD
                                    ${GLFW3_LIBRARY} 
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/lib/assimp-vc142-mtd.lib 
                                    ${OPENGL_LIBRARIES}
                                    )
###############################################################################################################	

add_executable(ExplodeMesh
				${CMAKE_SOURCE_DIR}/src/ExplodeMesh.cpp
				${CMAKE_SOURCE_DIR}/src/Camera.h
				${CMAKE_SOURCE_DIR}/src/Mesh.h
				${CMAKE_SOURCE_DIR}/src/Model.h
				${CMAKE_SOURCE_DIR}/src/Shader.h
				${CMAKE_SOURCE_DIR}/src/stb_loader.cpp
				${CMAKE_SOURCE_DIR}/Res/shaders/explode.vert
				${CMAKE_SOURCE_DIR}/Res/shaders/explode.geom
				${CMAKE_SOURCE_DIR}/Res/shaders/explode.frag
				)

# Set working directory
set_property(TARGET ExplodeMesh
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
			${CMAKE_SOURCE_DIR}
            )

#给主exe文件增加include
target_include_directories(ExplodeMesh PUBLIC 
                                    ${CMAKE_SOURCE_DIR}/src
                                    ${OPENGL_INCLUDE_DIRS}
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/include
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                    ${GLFW3_INCLUDE_DIR}
                                    )

#给主exe文件增加库文件
 target_link_libraries(ExplodeMesh PUBLIC 
                                    GLAD
                                    ${GLFW3_LIBRARY} 
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/lib/assimp-vc142-mtd.lib 
                                    ${OPENGL_LIBRARIES}
                                    )

###############################################################################################################	

add_executable(VisualizeNormal
				${CMAKE_SOURCE_DIR}/src/VisualizeNormal.cpp
				${CMAKE_SOURCE_DIR}/src/Camera.h
				${CMAKE_SOURCE_DIR}/src/Mesh.h
				${CMAKE_SOURCE_DIR}/src/Model.h
				${CMAKE_SOURCE_DIR}/src/Shader.h
				${CMAKE_SOURCE_DIR}/src/stb_loader.cpp
				${CMAKE_SOURCE_DIR}/Res/shaders/shownormal.vert
				${CMAKE_SOURCE_DIR}/Res/shaders/shownormal.geom
				${CMAKE_SOURCE_DIR}/Res/shaders/shownormal.frag
				${CMAKE_SOURCE_DIR}/Res/shaders/model.vert
				${CMAKE_SOURCE_DIR}/Res/shaders/model.frag
				)

# Set working directory
set_property(TARGET VisualizeNormal
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
			${CMAKE_SOURCE_DIR}
            )

#给主exe文件增加include
target_include_directories(VisualizeNormal PUBLIC 
                                    ${CMAKE_SOURCE_DIR}/src
                                    ${OPENGL_INCLUDE_DIRS}
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/include
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                    ${GLFW3_INCLUDE_DIR}
                                    )

#给主exe文件增加库文件
 target_link_libraries(VisualizeNormal PUBLIC 
                                    GLAD
                                    ${GLFW3_LIBRARY} 
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/lib/assimp-vc142-mtd.lib 
                                    ${OPENGL_LIBRARIES}
                                    )

set_property(DIRECTORY ${CMAKE_SOURCE_DIR} 
			PROPERTY VS_STARTUP_PROJECT 
			VisualizeNormal)

