# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

project(ImagineLinAlgTest)

cmake_minimum_required(VERSION 2.6)
find_package(Imagine REQUIRED)

add_executable(ImagineLinAlgTest test.cpp)
ImagineUseModules(ImagineLinAlgTest LinAlg)

if(IMAGINE_INSTALL)
    install(FILES CMakeLists.txt test.cpp DESTINATION test/LinAlg)
endif()
