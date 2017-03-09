# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

if(NOT IMAGINE_FORCE_QT4)
    find_package(Qt5Core)
endif()

if(Qt5Core_FOUND)
    file(READ CMake/UseImagineQt5.cmake.in str)
    file(WRITE CMake/UseImagineQt5.cmake ${str})
    if(IMAGINE_OPENGL)
        file(APPEND CMake/UseImagineQt5.cmake "if(NOT \${Qt5_Proj} STREQUAL \"_PRELOAD_\")\n")
        file(APPEND CMake/UseImagineQt5.cmake "    ImagineUseModules(\${Qt5_Proj} OpenGL)\n")
        file(APPEND CMake/UseImagineQt5.cmake "endif()\n")
    endif()
    install(FILES CMake/UseImagineQt5.cmake DESTINATION CMake
            RENAME UseImagineQt.cmake)
endif()
