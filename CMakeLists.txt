cmake_minimum_required(VERSION 3.15)

#set project name
project(gldemo)

include_directories(
	include
)

set(SOURCES 
	source/main.cpp 
	source/Shader.h 
	source/glad.c
)


link_directories(lib)

add_executable(gldemo ${SOURCES})

target_link_libraries(${PROJECT_NAME} glfw3)


