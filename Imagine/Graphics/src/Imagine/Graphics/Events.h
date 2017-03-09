// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

#ifndef IMAGINE_GRAPHICS_EVENTS_H
#define IMAGINE_GRAPHICS_EVENTS_H

#include "Types.h"

namespace Imagine {
    /// \addtogroup Graphics
    /// @{

    /// \brief Keyboard codes.
    enum KeyCode {
        KEY_BACK=16777219, KEY_TAB=16777217,
        KEY_RETURN=16777220, KEY_NUMPAD_ENTER=16777221,
        KEY_ESCAPE=16777216,
        KEY_INSERT=16777222, KEY_DELETE=16777223,
        KEY_HOME=16777232, KEY_END=16777233,
        KEY_PAGEUP=16777238, KEY_PAGEDOWN,
        KEY_LEFT=16777234, KEY_UP, KEY_RIGHT, KEY_DOWN,
        KEY_SHIFT=16777248, KEY_CONTROL=16777249,
        KEY_CMD=16777299, KEY_ALT=16777251,
        KEY_PRINT=16777225, KEY_SCROLL=16777254,
        KEY_PAUSE=16777224, KEY_MENU=16777301,
        KEY_F1=16777264, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6,
        KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12,
        KEY_NUMLOCK=16777253
    };

    // =============== Events ==========================
    /// %Event type.
    /// What triggered the event:
    /// - EVT_NONE    : No event (thus, a timeout)
    /// - EVT_BUT_ON  : A mouse button has been pressed
    /// - EVT_BUT_OFF : A mouse button has been released
    /// - EVT_MOTION  : The mouse has moved
    /// - EVT_KEY_ON  : A key has been pressed
    /// - EVT_KEY_OFF : A key has been released
    enum EventType {
        EVT_NONE = 0,
        EVT_BUT_ON = 2,
        EVT_BUT_OFF = 3,
        EVT_MOTION = 5,
        EVT_KEY_ON,
        EVT_KEY_OFF
    };
    /// %Event State.
    /// Keyboard and mouse state while the event occured (independently on what
    /// caused the event).
    /// These are binary masks (e.g. if (state&EVS_SHIFT) {} ...)
    /// - EVS_NONE    : None
    /// - EVS_SHIFT   : Shift was down
    /// - EVS_CONTROL : Control was down
    /// - EVS_ALT     : Alt was down
    enum EventState {
        EVS_NONE   =0,
        EVS_SHIFT  =(1<<0),
        EVS_CONTROL=(1<<1),
        EVS_ALT    =(1<<2)
    };
    /// \headerfile Imagine/Graphics.h "Imagine/Graphics.h"
    /// %Event info.
    /// All the info about an event...
    /// See this page for usage: \ref getEventPage "Handling events"
    struct Event {
        /// Event type.
        EventType type;
        /// Mouse position (only for EVT_BUT_ON, EVT_BUT_OFF and EVT_MOTION).
        IntPoint2 pix;
        /// Pressed mouse button (1,2,3) if any.
        int button;
        /// Pressed key code if any (only for EVT_KEY_ON and EVT_KEY_OFF).
        int key;
        /// Keyboard and mouse state (bitfield) just before event occured.
        EventState state;
        /// Window.
        Window win;
        /// SubWindow.
        int subWin;
    };
    /// ...
    /// Sleep.
    /// Waits for (approximately!) msec milliseconds, then return.
    /// \param msec number of milliseconds
    ///
    /// \dontinclude Graphics/test/test.cpp \skip events()
    /// \skipline sleep
    /// \until ...
    void milliSleep(int msec);

    // I/O control functions

    /// Mouse click in active window (returning position).
    /// Waits for a mouse click in active window (see \ref setActiveWindow()).
    /// \param x,y Coordinates of the cliked point
    /// \return mouse button (1=left, 2=middle, 3=right)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip events()
    /// \skipline get mouse
    int getMouse(int& x, int& y);
    /// Mouse click in active window (returning IntPoint2 position).
    /// Waits for a mouse click in active window (see \ref setActiveWindow()).
    /// \param p The cliked point
    /// \return mouse button (1=left, 2=middle, 3=right)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip events()
    /// \skipline get mouse (IntPoint2)
    inline int getMouse(IntPoint2& p) { return getMouse(p.x(), p.y()); }
    /// Key press in active window.
    /// Waits for a key pressed <b>in active window</b>
    /// (see also \ref anyGetKey()).
    /// \param ignoreModifier whether to ignore modifier keys (shift, ctrl, alt)
    /// \return ASCII code or \ref KeyCode
    ///
    /// \dontinclude Graphics/test/test.cpp \skip events()
    /// \skipline get key
    /// \until ...
    /// <b>Warning</b>: Imagine++ up to version 4.2.0 used to return uppercase
    /// letters even when the SHIFT key was not pressed. This is no longer the
    /// case, so that if only a letter key is pressed, the lowercase ASCII code
    /// is returned, such as <tt>'a'</tt> instead of <tt>'A'</tt>.
    int getKey(bool ignoreModifier=true);
    /// Mouse click in active window.
    /// Waits for a mouse click <b>in active window</b>
    /// (see also \ref anyClick()).
    /// \return mouse button (1=left, 2=middle, 3=right)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip events()
    /// \skipline click
    int click();
    /// Mouse click in any window.
    /// Waits for a mouse click <b>in any window</b> (see also \ref click()).
    /// \return mouse button (1=left, 2=middle, 3=right)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip events()
    /// \skipline click any
    int anyClick();
    /// Mouse click in any window (returning window).
    /// Waits for a mouse click <b>in any window</b> (see also \ref click()).
    /// \param win the Window that is clicked
    /// \param subWin subwindow index (if any)
    /// \return mouse button (1=left, 2=middle, 3=right)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip events()
    /// \skipline click any (returning window)
    int anyClick(Window &win, int &subWin);
    /// Key press in any window.
    /// Waits for a key pressed <b>in any window</b> (see also \ref getKey()).
    /// \param win the Window that is clicked
    /// \param subWin subwindow index (if any)
    /// \param ignoreModifier whether to ignore modifier keys (shift, ctrl, alt)
    /// \return Returns ASCII code (uppercase) or KeyCode
    ///
    /// \dontinclude Graphics/test/test.cpp \skip events()
    /// \skipline get key (any window)
    /// <b>Warning</b>: Imagine++ up to version 4.2.0 used to return uppercase
    /// letters even when the SHIFT key was not pressed. This is no longer the
    /// case, so that if only a letter key is pressed, the lowercase ASCII code
    /// is returned, such as <tt>'a'</tt> instead of <tt>'A'</tt>.
int anyGetKey(Window &win, int &subWin, bool ignoreModifier=true);
    /// Mouse click in any window (returning window and position).
    /// Waits for a mouse click <b>in any window</b> (see also \ref getMouse()).
    /// \param x,y Coordinates of the cliked point
    /// \param win the Window that is clicked
    /// \param subWin subwindow index (if any)
    /// \return mouse button (1=left, 2=middle, 3=right)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip events()
    /// \skipline get mouse (any window)
    int anyGetMouse(int &x, int&y, Window &win, int &subWin);
    /// Mouse click in any window (returning window and position).
    /// Waits for a mouse click <b>in any window</b> (see also \ref getMouse()).
    /// \param p Coordinates of the cliked point
    /// \param win the Window that is clicked
    /// \param subWin subwindow index (if any)
    /// \return mouse button (1=left, 2=middle, 3=right)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip events()
    /// \skipline get mouse (any window, IntPoint2)
    inline int anyGetMouse(IntPoint2 &p, Window &win, int &subWin) { return anyGetMouse(p.x(), p.y(), win, subWin); }
    /// Get event.
    /// Gets next event in the queue. Wait for (approx) ms milliseconds before timeout.
    /// \param ms Number of milliseconds before timeout. If ms==-1, waits until an event.
    /// \param ev The event. If timeout, ev.type is EVT_NONE.
    ///
    /// See this page for usage: \ref getEventPage "Handling events"
    ///
    /// \dontinclude Graphics/test/test.cpp \skip events()
    /// \skipline manually process events
    /// \until ...
    /// <b>Warning</b>: Imagine++ up to version 4.2.0 used to return uppercase
    /// letters for key press even when the SHIFT key was not pressed.
    /// This is no longer the case, so that if only a letter key is pressed,
    /// the lowercase ASCII code is returned in <tt>ev.key</tt>,
    /// such as <tt>'a'</tt> instead of <tt>'A'</tt>.
    void getEvent(int ms, Event &ev);
    /// Flush events.
    /// Flush the event queue.
    ///
    /// See this page for usage: \ref getEventPage "Handling events"
    ///
    /// \dontinclude Graphics/test/test.cpp \skip events()
    /// \skipline flush events
    void flushEvents();
    /// Unget event.
    /// Push back event at end of queue.
    /// \param ev The event.
    ///
    /// See this page for usage: \ref getEventPage "Handling events"
    ///
    /// \dontinclude Graphics/test/test.cpp \skip events()
    /// \skipline unget event
    void unGetEvent(const Event &ev);

    /// @}
}  /* namespace Imagine */

#endif /* IMAGINE_GRAPHICS_EVENTS_H */
