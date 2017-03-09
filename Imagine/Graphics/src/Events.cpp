#include "GraphicsUtilities.h"
#include "Imagine/Graphics/Events.h"
#include "Imagine/Graphics/Window.h"

namespace Imagine {

    // ====================================================================== //
    //! Temporizing functions
    void milliSleep(int msec)
    {
        userThread().milliSleep(msec);
    }

    void microSleep(int usec)
    {
        userThread().microSleep(usec);
    }

    // ====================================================================== //
    //! I/O control functions
    int getMouse(int& x, int& y)
    {
        Window w; int sw;
        return userThread().getMouse(x,y,w,sw,true);
    }

    int click()
    {
        int x, y;
        return getMouse(x, y);
    }

    int anyGetMouse(int &x, int&y, Window &win, int &subWin)
    {
        return userThread().getMouse(x,y,win,subWin,false);
    }

    int anyClick()
    {
        int x,y,sw; Window w;
        return anyGetMouse(x,y,w,sw);
    }

    int anyClick(Window& win, int& subWin)
    {
        int x,y;
        return anyGetMouse(x,y,win,subWin);
    }

    static bool isModifier(int k)
    {
        return (k==KEY_SHIFT || k==KEY_CONTROL || k==KEY_ALT || k==KEY_CMD);
    }

    int getKey(bool ignoreModifier)
    {
        Window w; int sw;
        while(true) {
            int k = userThread().getKey(w,sw,true);
            if(! (ignoreModifier && isModifier(k)))
                return k;
        }
    }

    int anyGetKey(Window& win, int& subWin, bool ignoreModifier)
    {
        while(true) {
            int k = userThread().getKey(win,subWin,false);
            if(! (ignoreModifier && isModifier(k)))
                return k;
        }
    }

    void getEvent(int ms, Event &ev)
    {
        userThread().getEvent(ms, ev);
    }

    void flushEvents()
    {
        userThread().flushEvents();
    }

    void unGetEvent(const Event &ev)
    {
        userThread().unGetEvent(ev);
    }

} /* namespace Imagine */
