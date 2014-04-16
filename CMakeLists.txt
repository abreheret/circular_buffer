project(CircularBuffer)
cmake_minimum_required(VERSION 2.8)

## configuration global de tous les projets
if(WIN32)
	add_definitions(-D_CRT_SECURE_NO_DEPRECATE)	
endif(WIN32)

add_subdirectory(src)
