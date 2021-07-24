cmake_minimum_required(VERSION 3.10)

# 创建工程
project(Blending VERSION 1.0.0
                DESCRIPTION "A very good program")


#添加可执行目标(主exe)
add_executable(${PROJECT_NAME} 
                ${CMAKE_SOURCE_DIR}/src/blending.cpp
                ${CMAKE_SOURCE_DIR}/src/Camera.h
                ${CMAKE_SOURCE_DIR}/src/Mesh.h
                ${CMAKE_SOURCE_DIR}/src/Model.h
                ${CMAKE_SOURCE_DIR}/src/Shader.h
                ${CMAKE_SOURCE_DIR}/src/Shader.cpp
                ${CMAKE_SOURCE_DIR}/src/stb_image.h
		${CMAKE_SOURCE_DIR}/src/glad.c
                )

# 查找cmake文件的位置
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#查找OpenGL
find_package(OpenGL REQUIRED)

#查找Glfw
find_package(GLFW3 REQUIRED)


#查找assimp
find_package(ASSIMP REQUIRED)

#给主exe文件增加include
target_include_directories(${PROJECT_NAME} PUBLIC 
                                    ${CMAKE_SOURCE_DIR}/src
                                    ${OPENGL_INCLUDE_DIRS}
                                    ${GLFW3_INCLUDE_DIR}
				    ${ASSIMP_INCLUDE_DIR}
                                    )

#给主exe文件增加库文件
 target_link_libraries(${PROJECT_NAME} PUBLIC 
                                    ${GLFW3_LIBRARY} 
				    ${OPENGL_LIBRARY}
				    ${ASSIMP_LIBRARY}
				    dl GL m Xrandr Xi X11 Xxf86vm pthread Xinerama Xcursor
                                    )

# 复制图片、模型、shader等资源文件夹
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    "${PROJECT_SOURCE_DIR}/Res"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Res"
                    )



# Installation *****************************

install (TARGETS ${PROJECT_NAME} 
        RUNTIME
        CONFIGURATIONS Debug
        DESTINATION ${PROJECT_NAME}/Debug)
install (TARGETS  ${PROJECT_NAME} 
        RUNTIME 
        CONFIGURATIONS Release
        DESTINATION ${PROJECT_NAME}/Release)
        
install (DIRECTORY Res
        CONFIGURATIONS Debug
        DESTINATION ${PROJECT_NAME}/Debug
        )
install (DIRECTORY Res
        CONFIGURATIONS Release
        DESTINATION ${PROJECT_NAME}/Release
        )
