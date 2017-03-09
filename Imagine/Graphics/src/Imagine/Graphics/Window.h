// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

#ifndef WINDOWCONTROL_H
#define WINDOWCONTROL_H

namespace Imagine {
    /// \addtogroup Graphics
    /// @{

    // Basic window control

    /// New window for 2D graphics.
    /// Creates and opens a window. If another window is already open, the new
    /// one does not get the painting orders yet, call setActiveWindow for that.
    /// If no other window is opened, no need to call setActiveWindow.
    /// \param w,h size
    /// \param windowTitle title (default="Imagine++")
    /// \param x,y screen position (default=let OS choose)
    /// \return a window handle
    ///
    /// \dontinclude Graphics/test/test.cpp \skip windows()
    /// \skipline Open
    /// \until ...
    Window openWindow(int w, int h, const std::string& windowTitle="Imagine++",
                      int x = -1, int y = -1);

    /// New window for 3D graphics.
    /// Creates and opens a window. If no other window is opened, becomes the
    /// active window
    /// \param w,h size
    /// \param windowTitle title (default="Imagine++")
    /// \param x,y screen position (default=let OS choose)
    /// \return a window handle
    ///
    /// \dontinclude Graphics/test/test.cpp \skip windows()
    /// \skipline Open
    /// \until ...
    Window openWindow3D(int w, int h,
                        const std::string& windowTitle="Imagine++",
                        int x=-1, int y=-1);

    /// New complex window.
    /// Creates and opens a  complex window with tabsNb tabs. If no other window
    /// or complex window is opened, first tab becomes the active window
    /// \param w,h size
    /// \param name windowTitle title (default="Imagine++")
    /// \param tabsNb number of tabs
    /// \param tabsNames titles of tabs (can be null array)
    /// \param tabsTypes types of tabs (WINDOW_2D or WINDOW_3D). This can be the
    /// null array, in which case all windows are 2D.
    /// \param x,y screen position (default=let OS choose)
    /// \return a window handle
    ///
    /// \dontinclude Graphics/test/test.cpp \skip windows()
    /// \skipline Open
    /// \until ...
    Window openComplexWindow(int w, int h, const std::string& name="Imagine++",
                             int tabsNb=1,
                             const std::string* tabsNames=0,
                             const WindowType* tabsTypes=0,
                             int x = -1, int y = -1);
    /// Close window.
    /// Closes a window.
    /// \param w the window to close
    ///
    /// \dontinclude Graphics/test/test.cpp \skip windows()
    /// \skipline close
    /// \until ...
    void closeWindow(Window w);

    /// Set Active.
    /// Sets the active tab into given ComplexWindow, i.e. the one that will
    /// get the next drawing commands.
    /// \param w Window handle
    /// \param subWin tab index
    ///
    /// \dontinclude Graphics/test/test.cpp \skip windows()
    /// \skipline active
    /// \until ...
    void setActiveWindow(Window w, int subWin = 0);
    /// Set BackGround.
    /// Sets window background.
    /// \param col Background Color
    ///
    /// \dontinclude Graphics/test/test.cpp \skip windows()
    /// \skipline background
    void setBackGround(const Color &col);
    /// clearWindow.
    /// Clears a window.
    /// - 2D: erase all (becomes WHITE)
    /// - 3D: hide all meshes
    ///
    /// \dontinclude Graphics/test/test.cpp \skip windows()
    /// \skipline clear (3D)
    /// \until clear (2D)
    void clearWindow();
    /// Mouse tracking.
    /// If mouse tracking is disabled (the default), the active window only
    /// receives mouse move events when
    /// at least one mouse button is pressed while the mouse is being moved.
    /// If mouse tracking is enabled, the widget receives mouse move events
    /// even if no buttons are pressed.
    ///
    /// \dontinclude Graphics/test/test.cpp \skip events2()
    /// \skipline receiving mouse move events even if no button is pressed
    void enableMouseTracking(bool en);
    /// Show Window.
    /// Brings a window to front and sets it active.
    /// \param w Window handle
    /// \param subWin subwindow number (optional)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip windows()
    /// \skipline show
    /// \until ...
    void showWindow(Window w, int subWin = 0);

    /// @}
} /* namespace Imagine */

#endif // WINDOWCONTROL_H
