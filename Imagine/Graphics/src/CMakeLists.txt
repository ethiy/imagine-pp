# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

project(ImagineGraphicsLib)

# Third-party libraries
set(GRAPHICS_OPENGL OFF)
if(NOT IMAGINE_FORCE_QT4)
    find_package(Qt5Core)
    if(Qt5Core_FOUND)
        find_package(Qt5OpenGL)
        if(Qt5OpenGL_FOUND)
           set(GRAPHICS_OPENGL ON)
        endif()
    else()
        set(GRAPHICS_OPENGL ON)
    endif()
endif()
if(IMAGINE_FORCE_QT4)
    unset(Qt5Core_FOUND)
endif()

# Imagine Qt classes having signals/slots
set(ImagineGraphicsQt_HEADERS
    GraphicsApplication.h
    PaintingWindow.h
    UserThread.h)
if(IMAGINE_OPENGL)
    set(ImagineGraphicsQt_HEADERS ${ImagineGraphicsQt_HEADERS} OpenGLWindow.h)
endif()

# Specify whether OpenGL is used
configure_file(Imagine/Graphics/ConfigGraphics.h.in
               ${CMAKE_CURRENT_SOURCE_DIR}/Imagine/Graphics/ConfigGraphics.h)

set(HEADER Imagine/Graphics.h)
set(SUBHEADERS
    Imagine/Graphics/ConfigGraphics.h
    Imagine/Graphics/Draw.h
    Imagine/Graphics/Events.h
    Imagine/Graphics/ImageIO.h
    Imagine/Graphics/Interface.h
    Imagine/Graphics/Mesh.h
    Imagine/Graphics/Types.h
    Imagine/Graphics/Window.h)

if(Qt5Core_FOUND)
    ImaginePreLoadModules(Qt5 Common)
    qt5_wrap_cpp(ImagineGraphics_MOC_SOURCES ${ImagineGraphicsQt_HEADERS})
    if(Qt5OpenGL_FOUND AND IMAGINE_OPENGL)
        ImaginePreLoadModules(OpenGL)
    endif()
    set_property(GLOBAL PROPERTY QtVersion "Qt5")
else()
    ImaginePreLoadModules(Qt4 Common)
    qt4_wrap_cpp(ImagineGraphics_MOC_SOURCES ${ImagineGraphicsQt_HEADERS})
    if(QT_USE_QTOPENGL AND IMAGINE_OPENGL)
        ImaginePreLoadModules(OpenGL)
    endif()
    set_property(GLOBAL PROPERTY QtVersion "Qt4")
endif()

add_library(ImagineGraphics STATIC
            Draw.cpp Events.cpp GraphicsApplication.cpp ImageIO.cpp 
            Interface.cpp
            Mesh.cpp OpenGLWindow.cpp PaintingWindow.cpp UserThread.cpp 
            Window.cpp 
            GraphicsApplication.h GraphicsUtilities.h OpenGLWindow.h
            PaintingWindow.h UserThread.h
            ${HEADER}
            ${SUBHEADERS}
            ${ImagineGraphics_MOC_SOURCES})
if(MSVC)
    ImagineAppendProperty(ImagineGraphics DEBUG_POSTFIX "d")
endif()
if(Qt5Core_FOUND)
    ImagineUseModules(ImagineGraphics Qt5 Common)
else()
    ImagineUseModules(ImagineGraphics Qt4 Common)
endif()

if(IMAGINE_INSTALL)
    install(FILES ${SUBHEADERS} DESTINATION include/Imagine/Graphics)
    install(FILES ${HEADER}     DESTINATION include/Imagine)
    install(TARGETS ImagineGraphics
            ARCHIVE DESTINATION lib
            LIBRARY DESTINATION lib)
    if(MSVC)
        set(d "${ImagineGraphicsLib_BINARY_DIR}/Debug/ImagineGraphicsd.lib")
        install(FILES "${d}" DESTINATION lib)
        set(d "${ImagineGraphicsLib_BINARY_DIR}/Debug/ImagineGraphicsd.pdb")
        if(EXISTS "${d}") # not genereated sometimes, for unknown reasons...
            install(FILES "${d}" DESTINATION lib)
        endif()
    endif()
endif()
