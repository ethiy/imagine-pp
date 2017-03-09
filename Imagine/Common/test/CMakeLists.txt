# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

project(ImagineCommonTest)

cmake_minimum_required(VERSION 2.6)
find_package(Imagine REQUIRED)

add_executable(ImagineCommonTest test.cpp)
ImagineUseModules(ImagineCommonTest Common)

if(IMAGINE_INSTALL)
    install(FILES CMakeLists.txt test.cpp DESTINATION  test/Common)
endif()
