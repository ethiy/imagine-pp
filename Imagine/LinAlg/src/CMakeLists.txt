# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

project(ImagineLinAlgLib)

add_library(ImagineLinAlg STATIC
            MyEigen1.cpp
            MyEigen2.cpp
            MyEigen3.cpp
            MyEigen4.cpp
            MyEigen5.cpp)
if(MSVC)
    ImagineAppendProperty(ImagineLinAlg DEBUG_POSTFIX "d")
endif()
ImagineUseModules(ImagineLinAlg Eigen)

if(IMAGINE_INSTALL)
    install(FILES Imagine/LinAlg.h DESTINATION include/Imagine)
    install(FILES
            Imagine/LinAlg/Matrix.h
            Imagine/LinAlg/MyEigen.h
            Imagine/LinAlg/SymMatrix.h
            Imagine/LinAlg/Vector.h
            DESTINATION include/Imagine/LinAlg)
    install(TARGETS ImagineLinAlg
            ARCHIVE DESTINATION lib
            LIBRARY DESTINATION lib)
    if(MSVC)
        set(d "${ImagineLinAlgLib_BINARY_DIR}/Debug/ImagineLinAlgd.lib")
        install(FILES "${d}" DESTINATION lib)
        set(d "${ImagineLinAlgLib_BINARY_DIR}/Debug/ImagineLinAlgd.pdb")
        if(EXISTS "${d}") # not genereated sometimes, for unknown reasons...
            install(FILES "${d}" DESTINATION lib)
        endif()
    endif()
endif()
