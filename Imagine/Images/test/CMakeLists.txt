# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

project(ImagineImagesTest)

cmake_minimum_required(VERSION 2.6)
find_package(Imagine REQUIRED)

add_executable(ImagineImagesTest test.cpp)
ImagineUseModules(ImagineImagesTest Images)

if(IMAGINE_INSTALL)
    install(FILES CMakeLists.txt test.cpp ryu.gif sup.png test.jpg DESTINATION test/Images)
endif()
