#ifndef IMAGINE_GRAPHICS_GRAPHICSUTILITIES_H
#define IMAGINE_GRAPHICS_GRAPHICSUTILITIES_H

#include "Imagine/Graphics/ConfigGraphics.h"
#include "GraphicsApplication.h"
#include "PaintingWindow.h"

namespace Imagine {

inline GraphicsApplication *guiApp()
{ return qobject_cast<GraphicsApplication*>(qApp);  }

inline UserThread& userThread()
{ return guiApp()->userThread; }

inline PaintingWindow* activeWindow2D() {
     Window win = guiApp()->activeWindow;
     return (win? win->contents[win->activeWin]: 0);
 }
#ifdef IMAGINE_OPENGL
inline OpenGLWindow* activeWindow3D() {
    Window win = guiApp()->activeWindow;
    return (win? win->contents3D[win->activeWin]: 0);
}
#endif
inline QWidget* activeWindow() {
    QWidget* w = activeWindow2D();
#ifdef IMAGINE_OPENGL
    if(! w)  w = (QWidget*)activeWindow3D();
#endif
    return w;
}

#define oops2D() \
    if(! activeWindow2D()) { \
        std::cerr << "Graphics error: no active 2D window" << std::endl; \
        return; \
    }
#ifdef IMAGINE_OPENGL
#define oops3D() \
    if(! activeWindow3D()) { \
        std::cerr << "Graphics error: no active 3D window" << std::endl; \
        return; \
    }
#endif
#define oopsActive() \
    if(! activeWindow()) { \
        std::cerr << "Graphics error: no active window" << std::endl; \
        return; \
    }
} /* namespace Imagine */

#endif /* IMAGINE_GRAPHICS_GRAPHICSUTILITIES_H */
