# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

if(IMAGINE_FORCE_QT4)
    return()
endif(IMAGINE_FORCE_QT4)

if(POLICY CMP0020)
    cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0011)
    cmake_policy(SET CMP0011 NEW)
endif()

find_package(Qt5Core REQUIRED)
if(Qt5Core_FOUND)
    find_package(Qt5Widgets REQUIRED)
    find_package(Qt5Gui REQUIRED)
    find_package(Qt5OpenGL)
endif()

include_directories(${Qt5Core_INCLUDE_DIRS}
                    ${Qt5Widgets_INCLUDE_DIRS}
                    ${Qt5Gui_INCLUDE_DIRS}
                    ${Qt5OpenGL_INCLUDE_DIRS})

if(Qt_Proj)
    set(Qt5_Proj ${Qt_Proj})
endif()

if(NOT ${Qt5_Proj} STREQUAL "_PRELOAD_")
  target_link_libraries(${Qt5_Proj}
                        ${Qt5Core_LIBRARIES}
                        ${Qt5Widgets_LIBRARIES}
                        ${Qt5Gui_LIBRARIES}
                        ${Qt5OpenGL_LIBRARIES})
endif()
