// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

#ifndef IMAGINE_GRAPHICS_TYPES_H
#define IMAGINE_GRAPHICS_TYPES_H

#include <Imagine/Common.h>

namespace Imagine {
    /// \addtogroup Graphics
    /// @{

    /// Plane point with integral coordinates.
    typedef Coords<2> IntPoint2;
    /// Double space point.
    typedef FVector<double,3> DoublePoint3;
    /// Double space vector.
    typedef DoublePoint3 DoubleVector3;
    /// Float space point.
    typedef FVector<float,3> FloatPoint3;
    /// Float space vector.
    typedef FloatPoint3 FloatVector3;
    /// Triangle to insert in a mesh, built from three space point indices.
    typedef FArray<int,3> Triangle;
    /// Quadrilateral to insert in a mesh, built from four space point indices.
    typedef FArray<int,4> Quad;

    /// Type of Window.
    /// Type of Window
    /// - WINDOW_2D: 2D display
    /// - WINDOW_3D: 3D display (meshes using OpenGL), with navigation:
    ///     - SHIFT+Button 1:   rotate
    ///     - SHIFT+Button 3:   translate
    ///     - Mouse wheel:      zoom
    ///     - SHIFT+a:          zoom in
    ///     - SHIFT+z:          zoom out
    ///     - SHIFT+r:          recenter camera
    ///     - SHIFT+m:          toggle solid/wire/points mode
    enum WindowType { WINDOW_2D, WINDOW_3D };

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    class WindowInternal; // Private
#endif
    /// Handle to a display window.
    typedef WindowInternal* Window;

    /// \enum KeyCode
    /// \details Codes assigned to most non alpha-numeric keys
    /// (alpha-numeric keys are represented by their ASCII code: 'A', '0'...)
    ///
    /// Functions \ref getKey() and \ref anyGetKey() may return one of those.
    /// The field \ref Event::key stores such a value.
    /// \dontinclude Graphics/test/test.cpp \skip events()
    /// \skipline get key
    /// \until ...
    /// The possible codes are:
    /// \dontinclude Graphics/src/Imagine/Graphics/Events.h \skip namespace
    /// \skipline enum KeyCode
    /// \until };
    /// Use the names defined above, not their numerical values: your code will
    /// be clearer and more portable.
    ///
    /// The direction arrow keys are <tt>KEY_UP</tt>, <tt>KEY_DOWN</tt>,
    /// <tt>KEY_LEFT</tt>, <tt>KEY_RIGHT</tt>.
    ///
    /// Modifier keys are <tt>KEY_SHIFT</tt>, <tt>KEY_ALT</tt>,
    /// <tt>KEY_CONTROL</tt>,
    /// <tt>KEY_CMD</tt> (Command key under MacOS, Windows key otherwise).

    /// @}
} /* namespace Imagine */

#endif /* IMAGINE_GRAPHICS_TYPES_H */
