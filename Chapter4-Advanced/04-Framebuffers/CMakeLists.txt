cmake_minimum_required(VERSION 3.10)

# 创建工程
project(Framebuffer VERSION 1.0.0
                DESCRIPTION "A very good program"
                LANGUAGES C CXX)

# 添加配置文件，设置根目录
# configure_file(${CMAKE_SOURCE_DIR}/src/helpers/RootDir.h.in ${CMAKE_SOURCE_DIR}/src/helpers/RootDir.h)                

# # 设置GLFW配置选项
# set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# add_subdirectory(${CMAKE_SOURCE_DIR}/ThirdParty/glfw-3.3/)


# 为GLAD创建target
add_library(GLAD STATIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/glad.c")
target_include_directories(GLAD PUBLIC "${CMAKE_SOURCE_DIR}/../../ThirdParty/glad/include")

aux_source_directory(${CMAKE_SOURCE_DIR}/src/ SOURCEFILES) 
 #添加可执行目标(主exe)
add_executable(${PROJECT_NAME} ${SOURCEFILES})

# Set working directory
set_property(TARGET ${PROJECT_NAME}
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
           "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
            )

#查找OpenGL
find_package(OpenGL REQUIRED)

# 查找cmake文件的位置
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
#查找Glfw
find_package(GLFW3 REQUIRED)

#给主exe文件增加include
target_include_directories(${PROJECT_NAME} PUBLIC 
                                    ${CMAKE_SOURCE_DIR}/src
                                    ${OPENGL_INCLUDE_DIRS}
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/include
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                    ${GLFW3_INCLUDE_DIR}
                                    )

#给主exe文件增加库文件
 target_link_libraries(${PROJECT_NAME} PUBLIC 
                                    GLAD
                                    ${GLFW3_LIBRARY} 
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/lib/assimp-vc141-mt.lib 
                                    ${OPENGL_LIBRARIES}
                                    )

# 复制图片、模型、shader等资源文件夹
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E copy_directory
                    "${PROJECT_SOURCE_DIR}/Res"
                    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Res"
                    )

# 复制Dll文件
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                        COMMAND ${CMAKE_COMMAND} -E copy_directory
                        "${PROJECT_SOURCE_DIR}/dlls"
                        $<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()



# Installation *****************************

set(CMAKE_INSTALL_PREFIX "D:/Test/")
install (TARGETS ${PROJECT_NAME} 
        RUNTIME
        CONFIGURATIONS Debug
        DESTINATION ${PROJECT_NAME}/Debug)
install (TARGETS  ${PROJECT_NAME} 
        RUNTIME 
        CONFIGURATIONS Release
        DESTINATION ${PROJECT_NAME}/Release)
        
set(DLLs ${CMAKE_SOURCE_DIR}/dlls/assimp-vc141-mt.dll)
install (PROGRAMS ${DLLs}
        CONFIGURATIONS Debug 
        DESTINATION ${PROJECT_NAME}/Debug
        ) 
install (PROGRAMS ${DLLs}
        CONFIGURATIONS Release
        DESTINATION ${PROJECT_NAME}/Release
        )
install (DIRECTORY Res
        CONFIGURATIONS Debug
        DESTINATION ${PROJECT_NAME}/Debug
        )
install (DIRECTORY Res
        CONFIGURATIONS Release
        DESTINATION ${PROJECT_NAME}/Release
        )