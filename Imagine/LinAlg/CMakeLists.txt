# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

if(IMAGINE_INSTALL)
    install(FILES CMake/UseImagineLinAlg.cmake DESTINATION CMake)
endif()
add_subdirectory(src)
add_subdirectory(test)
