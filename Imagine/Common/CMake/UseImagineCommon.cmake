# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

# Loading Common
if(NOT ImagineCommon_FOUND)
set(ImagineCommon_FOUND true)

if(IMAGINE_FROM_SRC)
    file(TO_CMAKE_PATH "$ENV{IMAGINEPP_SRC}" c)
    set(d "${c}/Imagine/Common/src")
    include_directories(BEFORE "${d}")
else()
    file(TO_CMAKE_PATH "$ENV{Imagine_DIR}" c)
    set(d "${c}/include")
    include_directories(AFTER "${d}")
endif()
endif()

# Using ImagineCommon
if(NOT ${Common_Proj} STREQUAL "_PRELOAD_")
    get_target_property(f ${Common_Proj} COMPILE_FLAGS)
    if (${f} MATCHES "-DSRCDIR")
    else()
        ImagineAppendProperty(${Common_Proj} COMPILE_FLAGS
                              -DSRCDIR=\"${CMAKE_CURRENT_SOURCE_DIR}\")
    endif()
endif()
