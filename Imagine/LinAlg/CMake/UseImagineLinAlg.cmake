# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

# Loading LinAlg
if(NOT ImagineLinAlg_FOUND)
set(ImagineLinAlg_FOUND true)

if(IMAGINE_FROM_SRC)
    file(TO_CMAKE_PATH "$ENV{IMAGINEPP_SRC}" c)
    set(d "${c}/Imagine/LinAlg/src")
    include_directories(BEFORE ${d})
else()
    file(TO_CMAKE_PATH "$ENV{Imagine_DIR}" c)
    set(d "${c}/include")
    include_directories(AFTER "${d}")
endif()
set(IMAGINE_LINALG_HEADERS
    "${d}/Imagine/LinAlg.h"
    "${d}/Imagine/LinAlg/Matrix.h"
    "${d}/Imagine/LinAlg/MyEigen.h"
    "${d}/Imagine/LinAlg/SymMatrix.h"
    "${d}/Imagine/LinAlg/Vector.h"
   )
file(TO_CMAKE_PATH "${IMAGINE_LINALG_HEADERS}" IMAGINE_LINALG_HEADERS)
endif()

# Using LinAlg
if(NOT ${LinAlg_Proj} STREQUAL "_PRELOAD_")
    if(IMAGINE_FROM_SRC)
        target_link_libraries(${LinAlg_Proj} ImagineLinAlg)
    else()
       file(TO_CMAKE_PATH "$ENV{Imagine_DIR}" d)
       ImagineAddLinkPath(${LinAlg_Proj} "${d}/lib")
       if(MSVC)
           target_link_libraries(${LinAlg_Proj} debug ImagineLinAlgd)
           target_link_libraries(${LinAlg_Proj} optimized ImagineLinAlg)
       else()
           target_link_libraries(${LinAlg_Proj} ImagineLinAlg)
       endif()
    endif()
    ImagineUseModules(${LinAlg_Proj} Common Eigen)
endif()
