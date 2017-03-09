# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

# Loading ImagineGraphics
if(NOT ImagineGraphics_FOUND)
set(ImagineGraphics_FOUND true)

if(IMAGINE_FROM_SRC)
    file(TO_CMAKE_PATH "$ENV{IMAGINEPP_SRC}" c)
    set(d "${c}/Imagine/Graphics/src")
    include_directories(BEFORE "${d}")
else()
    file(TO_CMAKE_PATH "$ENV{Imagine_DIR}" c)
    set(d "${c}/include")
    include_directories(AFTER "${d}")
endif()
endif()

# Using Graphics
if(NOT ${Graphics_Proj} STREQUAL "_PRELOAD_")
    if(IMAGINE_FROM_SRC)
        # Refers to project name
        target_link_libraries(${Graphics_Proj} ImagineGraphics)
    else()
        # Refers to .lib names 
        file(TO_CMAKE_PATH "$ENV{Imagine_DIR}" d)
        ImagineAddLinkPath(${Graphics_Proj} "${d}/lib")
        if(MSVC)
            target_link_libraries(${Graphics_Proj} debug ImagineGraphicsd)
            target_link_libraries(${Graphics_Proj} optimized ImagineGraphics)
        else()
            target_link_libraries(${Graphics_Proj} ImagineGraphics)
        endif()
    endif()
    set(Qt Qt)
    if(IMAGINE_FROM_SRC) # Building Imagine++, use found Qt version (4 or 5)
        get_property(Qt GLOBAL PROPERTY QtVersion) # In Graphics/CMakeLists.txt
    endif()
    ImagineUseModules(${Graphics_Proj} ${Qt} Common)
endif()
