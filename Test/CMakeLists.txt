# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

cmake_minimum_required(VERSION 2.6)

project(ImagineTest)

file(GLOB tests RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} * )
file(GLOB TPtests RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ThirdParty/*)

foreach (dir ${tests} ${TPtests})
	if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/CMakeLists.txt)
		ADD_SUBDIRECTORY(${dir})
	endif()
endforeach()
