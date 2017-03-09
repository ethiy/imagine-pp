# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

project(ImagineGraphicsTests)

cmake_minimum_required(VERSION 2.6)
find_package(Imagine REQUIRED)

add_executable(ImagineGraphicsExample example.cpp)
ImagineUseModules(ImagineGraphicsExample Graphics)

add_executable(ImagineGraphicsTest test.cpp)
ImagineUseModules(ImagineGraphicsTest Graphics)

add_executable(ImagineGraphicsParticles particles.cpp)
ImagineUseModules(ImagineGraphicsParticles Graphics)

if(IMAGINE_INSTALL)
    install(FILES CMakeLists.txt example.cpp test.cpp particles.cpp
                  ksmall.jpg sup.png test.jpg ryu.gif index.jpg forty-licks.png
                  bunny.obj
            DESTINATION test/Graphics)
endif()
