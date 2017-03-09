# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
if(NOT ${OpenGL_Proj} STREQUAL "_PRELOAD_")
    target_link_libraries(${OpenGL_Proj} ${OPENGL_LIBRARIES})
endif()
