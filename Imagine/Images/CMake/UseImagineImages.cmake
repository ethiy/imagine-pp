# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

# Loading 
if(NOT ImagineImages_FOUND)
set(ImagineImages_FOUND true)

if(IMAGINE_FROM_SRC)
    file(TO_CMAKE_PATH "$ENV{IMAGINEPP_SRC}" c)
    set(d "${c}/Imagine/Images/src")
    include_directories(BEFORE "${d}")
else()
    file(TO_CMAKE_PATH "$ENV{Imagine_DIR}" c)
    set(d "${c}/include")
    include_directories(AFTER "${d}")
endif()
set(IMAGINE_IMAGES_HEADERS
    "${d}/Imagine/Images.h"
    "${d}/Imagine/Images/Image.h"
    "${d}/Imagine/Images/IO.h"
    "${d}/Imagine/Images/Algos.h"
    "${d}/Imagine/Images/Schemes.h"
   )
file(TO_CMAKE_PATH "${IMAGINE_IMAGES_HEADERS}" IMAGINE_IMAGES_HEADERS)
endif()

# Using Images
if(NOT ${Images_Proj} STREQUAL "_PRELOAD_")
    ImagineUseModules(${Images_Proj} Graphics)
endif()
