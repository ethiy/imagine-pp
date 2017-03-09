# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

if(NOT Qt5Core_FOUND)
    file(READ CMake/UseImagineQt4.cmake.in str)
    file(WRITE CMake/UseImagineQt4.cmake ${str})
    if(IMAGINE_OPENGL)
        file(APPEND CMake/UseImagineQt4.cmake "if(NOT \${Qt4_Proj} STREQUAL \"_PRELOAD_\")\n")
        file(APPEND CMake/UseImagineQt4.cmake "    ImagineUseModules(\${Qt4_Proj} OpenGL)\n")
        file(APPEND CMake/UseImagineQt4.cmake "endif()\n")
    endif()
    install(FILES CMake/UseImagineQt4.cmake DESTINATION CMake
            RENAME UseImagineQt.cmake)
endif()
