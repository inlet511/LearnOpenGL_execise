cmake_minimum_required(VERSION 3.10)
project(Framebuffers VERSION 1.0.0)

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
add_executable(Framebuffer ${SOURCEFILES} ${SHADERS})

# Set working directory
set_property(TARGET Framebuffer
            PROPERTY VS_DEBUGGER_WORKING_DIRECTORY
			${CMAKE_SOURCE_DIR}
            )

#给主exe文件增加include
target_include_directories(Framebuffer PUBLIC 
                                    ${CMAKE_SOURCE_DIR}/src
                                    ${OPENGL_INCLUDE_DIRS}
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/include
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/glm
                                    ${GLFW3_INCLUDE_DIR}
                                    )

#给主exe文件增加库文件
 target_link_libraries(Framebuffer PUBLIC 
                                    GLAD
                                    ${GLFW3_LIBRARY} 
                                    ${CMAKE_SOURCE_DIR}/../../ThirdParty/assimp/lib/assimp-vc142-mtd.lib 
                                    ${OPENGL_LIBRARIES}
                                    )


set_property(DIRECTORY ${CMAKE_SOURCE_DIR} 
			PROPERTY VS_STARTUP_PROJECT 
			Framebuffer)

# 复制图片、模型、shader等资源文件夹
# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                    # COMMAND ${CMAKE_COMMAND} -E copy_directory
                    # "${PROJECT_SOURCE_DIR}/Res"
                    # "$<TARGET_FILE_DIR:${PROJECT_NAME}>/Res"
                    # )

# 复制Dll文件
#if(WIN32)
    #add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                        #COMMAND ${CMAKE_COMMAND} -E copy_directory
                        #"${PROJECT_SOURCE_DIR}/dlls"
                        #$<TARGET_FILE_DIR:${PROJECT_NAME}>)
#endif()

<<<<<<< HEAD
set(CMAKE_INSTALL_PREFIX "D:/Test/")
install (TARGETS ${PROJECT_NAME} 
        RUNTIME
        CONFIGURATIONS Debug
        DESTINATION ${PROJECT_NAME}/Debug)
install (TARGETS  ${PROJECT_NAME} 
        RUNTIME 
        CONFIGURATIONS Release
        DESTINATION ${PROJECT_NAME}/Release)
        
set(DLLs ${CMAKE_SOURCE_DIR}/dlls/assimp-vc142-mtd.dll)
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
=======
>>>>>>> 92a39112e79189229a3f3b8e64c9053d348eae73
