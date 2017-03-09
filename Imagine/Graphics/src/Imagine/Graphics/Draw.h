// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

#ifndef IMAGINE_GRAPHICS_DRAW2D_H
#define IMAGINE_GRAPHICS_DRAW2D_H

#include "Types.h"
class QPolygonF;
namespace Imagine {
    class Mesh;
    /// \addtogroup Graphics
    /// @{

    // Drawing commands
    /// Point.
    /// Draws a point.
    /// \param x,y point
    /// \param col Color
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline point
    void drawPoint(int x, int y, const Color& col, bool xorMode = false);
    /// Point (IntPoint2).
    /// Draws a point.
    /// \param p point
    /// \param col Color
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline point (IntPoint2)
    inline void drawPoint(const IntPoint2& p, const Color& col, bool xorMode = false)
    { drawPoint(p.x(), p.y(), col, xorMode); }
    /// Circle.
    /// Draws a circle.
    /// \param xc,yc center
    /// \param r radius
    /// \param col Color
    /// \param penWidth line width (default=1)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline circle
    void drawCircle(int xc, int yc, int r, const Color& col, int penWidth = 1, bool xorMode = false);
    /// Circle (IntPoint2).
    /// Draws a circle.
    /// \param c center
    /// \param r radius
    /// \param col Color
    /// \param penWidth line width (default=1)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline circle (IntPoint2)
    inline void drawCircle(const IntPoint2& c, int r, const Color &col, int penWidth = 1, bool xorMode = false)
    { drawCircle(c.x(), c.y(), r, col, penWidth, xorMode); }
    /// Ellipse.
    /// Draws an ellipse.
    /// \param x,y Top Left
    /// \param w,h Dimensions
    /// \param col Color
    /// \param penWidth line width (default=1)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline ellipse
    void drawEllipse(int x, int y, int w, int h, const Color &col, int penWidth = 1, bool xorMode = false);
    /// Ellipse (IntPoint2).
    /// Draws an ellipse.
    /// \param p Top Left
    /// \param w,h Dimensions
    /// \param col Color
    /// \param penWidth line width (default=1)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline ellipse (IntPoint2)
    inline void drawEllipse(const IntPoint2& p, int w, int h, const Color &col, int penWidth = 1, bool xorMode = false)
    { drawEllipse(p.x(), p.y(), w, h, col, penWidth, xorMode); }
    /// Line.
    /// Draws a line.
    /// \param x1,y1 First point
    /// \param x2,y2 Second point
    /// \param col Color
    /// \param penWidth line width (default=1)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline line
    void drawLine(int x1, int y1, int x2, int y2, const Color &col, int penWidth = 1, bool xorMode = false);
    /// Line (IntPoint2).
    /// Draws a line.
    /// \param p1 First point
    /// \param p2 Second point
    /// \param col Color
    /// \param penWidth line width (default=1)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline line (IntPoint2)
    inline void drawLine(const IntPoint2& p1, const IntPoint2& p2, const Color &col, int penWidth = 1, bool xorMode = false)
    { drawLine(p1.x(), p1.y(), p2.x(), p2.y(), col, penWidth, xorMode); }
    /// Rectangle.
    /// Draws a rectangle.
    /// \param x,y Top Left
    /// \param w,h Dimensions
    /// \param col Color
    /// \param penWidth line width (default=1)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline rectangle
    void drawRect(int x, int y, int w, int h, const Color &col, int penWidth = 1, bool xorMode = false);
    /// Rectangle (IntPoint2).
    /// Draws a rectangle.
    /// \param p Top Left
    /// \param w,h Dimensions
    /// \param col Color
    /// \param penWidth line width (default=1)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline rectangle (IntPoint2)
    inline void drawRect(const IntPoint2& p, int w, int h, const Color &col, int penWidth = 1, bool xorMode = false)
    { drawRect(p.x(), p.y(), w, h, col, penWidth, xorMode); }
    /// Camera
    /// Sets the camera
    /// \param pos  where the camera is
    /// \param dir where the camera is looking at, relative to \a pos
    /// \param up the up direction
    void setCamera(const DoublePoint3& pos,
                   const DoublePoint3& dir,
                   const DoubleVector3& up);
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    void drawPoly(const QPolygonF& poly, const Color& col, int width = 1, bool xorMode = false); // Private : do not use.
#endif

    /// Polygon.
    /// Draws a polygon. Close it, drawing a line from last point to first one.
    /// \param x,y Points positions (x[0],y[0]), ..., (x[n-1],y[n-1])
    /// \param n Number of points
    /// \param col Color
    /// \param width Line width (default=1)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline polygon
    /// \until contour
    void drawPoly(const int x[], const int y[], int n, const Color& col, int width = 1, bool xorMode = false);
    /// Polygon (IntPoint2).
    /// Draws a polygon. Close it, drawing a line from last point to first one.
    /// \param p Points positions
    /// \param n Number of points
    /// \param col Color
    /// \param width Line width (default=1)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline polygon (IntPoint2)
    /// \until contour
    void drawPoly(const IntPoint2* p, int n, const Color& col,int width = 1, bool xorMode = false);
    /// Polygon (one array).
    /// Draws a polygon. Close it, drawing a line from last point to first one.
    /// \param xy Points positions (one array points are (xy[0],xy[1]), (xy[2],xy[3]) ...
    /// \param n Number of points
    /// \param col Color
    /// \param width Line width (default=1)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline polygon (one array)
    /// \until contour
    inline void drawPoly(const int xy[], int n, const Color &col, int width = 1, bool xorMode = false)
    { drawPoly((const IntPoint2*)xy,n,col,width, xorMode); }
    /// String.
    /// Draws a string. \b NB: xorMode does not work!
    /// \param x,y Position (first char)
    /// \param s String
    /// \param col AlphaColor or Color
    /// \param fontSize size (default=12) (NB: cannot choose font yet)
    /// \param alpha Angle (default=0=horizontal)
    /// \param italic, bold, underlined style (default=no)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline strings
    /// \until ...
    void drawString(int x, int y, const std::string &s, const AlphaColor &col, int fontSize = 12,
                    double alpha = 0, bool italic = false, bool bold = false, bool underlined = false, bool xorMode = false);
    /// String (IntPoint2).
    /// Draws a string. \b NB: xorMode does not work!
    /// \param p Position (first char)
    /// \param s String
    /// \param col AlphaColor or Color
    /// \param fontSize size (default=12) (NB: cannot choose font yet)
    /// \param alpha Angle (default=0=horizontal)
    /// \param italic,bold,underlined style (default=no)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline strings
    /// \until ...
    inline void drawString(const IntPoint2& p, const std::string &s, const AlphaColor& col, int fontSize = 12,
                           double alpha = 0, bool italic = false, bool bold = false, bool underlined = false, bool xorMode = false)
    { drawString(p.x(), p.y(), s, col, fontSize, alpha, italic, bold, underlined, xorMode); }
    /// Arrow.
    /// Draws an arrow.
    /// \param x1,y1 beginning point
    /// \param x2,y2 end point
    /// \param col AlphaColor or Color
    /// \param arrowWidth,arrowHeight Tip box dimension (default 8x5)
    /// \param style (0,1 or 2, default=0)
    /// \param width Line width (default=1)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline arrow
    void drawArrow(int x1, int y1, int x2, int y2, const AlphaColor &col, int arrowWidth = 8, int arrowHeight = 5,
                   int style = 0, int width = 1, bool xorMode = false);
    /// Arrow (IntPoint2).
    /// Draws an arrow.
    /// \param p1 beginning point
    /// \param p2 end point
    /// \param col AlphaColor or Color
    /// \param arrowWidth,arrowHeight Tip box dimension (default 8x5)
    /// \param style (0,1 or 2, default=0)
    /// \param width Line width (default=1)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline arrow (IntPoint2)
    inline void drawArrow(const IntPoint2& p1, const IntPoint2& p2, const AlphaColor& col, int arrowWidth = 8, int arrowHeight = 5,
                          int style = 0, int width = 1, bool xorMode = false)
    { drawArrow(p1.x(), p1.y(), p2.x(), p2.y(), col, arrowWidth, arrowHeight,
                style, width, xorMode); }
    /// Arrow.
    /// Draws an arrow.
    /// \param x1,y1 beginning point
    /// \param x2,y2 end point
    /// \param col AlphaColor or Color
    /// \param ta,tl Tip box angle and length
    /// \param style (0,1 or 2, default=0)
    /// \param width Line width (default=1)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline arrow (angle)
    inline void drawArrow(int x1, int y1, int x2, int y2, const AlphaColor&  col, double ta, double tl, int style = 0, int width = 1, bool xorMode = false)
    { drawArrow(x1, y1, x2, y2, col,
                int(tl*cos(ta*3.14/180)), int(2*tl*sin(ta*3.14/180)),
                style, width, xorMode); }
    /// Arrow.
    /// Draws an arrow.
    /// \param p1 beginning point
    /// \param p2 end point
    /// \param col AlphaColor or Color
    /// \param ta,tl Tip box angle and length
    /// \param style (0,1 or 2, default=0)
    /// \param width Line width (default=1)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline arrow (angle IntPoint2)
    inline void drawArrow(const IntPoint2& p1, const IntPoint2& p2, const AlphaColor&  col, double ta, double tl, int style = 0, int width = 1, bool xorMode = false)
    { drawArrow(p1.x(), p1.y(), p2.x(), p2.y(), col, ta, tl, style, width, xorMode); }
    /// Filled Ellipse.
    /// Fills an ellipse.
    /// \param x,y Top Left
    /// \param w,h Dimensions
    /// \param col AlphaColor or Color
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline filled ellipse
    void fillEllipse(int x, int y, int w, int h, const AlphaColor &col, bool xorMode = false);
    /// Filled Ellipse (IntPoint2).
    /// Fills an ellipse.
    /// \param p Top Left
    /// \param w,h Dimensions
    /// \param col AlphaColor or Color
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline filled ellipse (IntPoint2)
    inline void fillEllipse(const IntPoint2& p, int w, int h, const AlphaColor& col, bool xorMode = false)
    { fillEllipse(p.x(), p.y(), w, h, col, xorMode); }
    /// Filled rectangle.
    /// Fills a rectangle.
    /// \param x,y Top Left
    /// \param w,h Dimensions
    /// \param col AlphaColor or Color
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline filled rectangle
    void fillRect(int x, int y, int w, int h, const AlphaColor &col, bool xorMode = false);
    /// Filled rectangle (IntPoint2).
    /// Fills a rectangle.
    /// \param p Top Left
    /// \param w,h Dimensions
    /// \param col AlphaColor or Color
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline filled rectangle (IntPoint2)
    inline void fillRect(const IntPoint2& p, int w, int h, const AlphaColor& col, bool xorMode = false)
    { fillRect(p.x(), p.y(), w, h, col, xorMode); }
    /// Filled Circle.
    /// Fills a circle.
    /// \param xc,yc center
    /// \param r radius
    /// \param col AlphaColor or Color
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline filled circle
    void fillCircle(int xc, int yc, int r, const AlphaColor &col, bool xorMode = false);
    /// Filled Circle (IntPoint2).
    /// Fills a circle.
    /// \param c center
    /// \param r radius
    /// \param col AlphaColor or Color
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline filled circle (IntPoint2)
    inline void fillCircle(const IntPoint2& c, int r, const AlphaColor& col, bool xorMode = false)
    { fillCircle(c.x(), c.y(), r, col, xorMode); }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    void fillPoly(const QPolygonF& polygon, const AlphaColor &col, bool xorMode = false); // Private : do not use.
#endif
    /// Filled Polygon.
    /// Draws a filled polygon. Close it, from last point to first one.
    /// \param x,y Points positions (x[0],y[0]), ..., (x[n-1],y[n-1])
    /// \param n Number of points
    /// \param col AlphaColor or Color
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline polygon
    /// \until inside
    void fillPoly(const int x[], const int y[], int n, const AlphaColor &col, bool xorMode = false);
    /// Filled Polygon (IntPoint2).
    /// Draws a filled polygon. Close it, from last point to first one.
    /// \param p Points positions
    /// \param n Number of points
    /// \param col AlphaColor or Color
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline polygon (IntPoint2)
    /// \until inside
    void fillPoly(const IntPoint2* p, int n, const AlphaColor &col, bool xorMode = false);
    /// Filled Polygon.
    /// Draws a filled polygon. Close it, from last point to first one.
    /// \param xy Points positions (one array points are (xy[0],xy[1]), (xy[2],xy[3]) ...
    /// \param n Number of points
    /// \param col AlphaColor or Color
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline polygon (one array)
    /// \until inside
    void fillPoly(const int xy[], int n, const AlphaColor &col, bool xorMode = false);

    // No refresh functions
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    int noRefreshStack(int i); // Private : do not use.
#endif

    /// Norefresh begin.
    /// To draw faster, stop refreshing 2D drawings. They are buffered until
    /// noRefreshEnd() is called.
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline No refresh section
    /// \until ...
    void noRefreshBegin();
    /// Norefresh end.
    /// Ends a section started with noRefreshBegin().
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline No refresh section
    /// \until ...
    void noRefreshEnd();
    /// Norefresh push.
    /// To draw faster, stop refreshing 2D drawings. They are buffered until
    /// corresponding noRefreshPop() is called. Push and pop might be
    /// recursively included.
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline No refresh section (push/pop)
    /// \until ...
    inline void noRefreshPush()
    { if(noRefreshStack(1) == 1) noRefreshBegin(); }
    /// Norefresh pop.
    /// Ends a section started with noRefreshPush()
    ///
    /// \dontinclude Graphics/test/test.cpp \skip draw2D()
    /// \skipline No refresh section (push/pop)
    /// \until ...
    inline void noRefreshPop()
    { if(noRefreshStack(-1) == 0) noRefreshEnd(); }

    /// @}
} /* namespace Imagine */

#endif // IMAGINE_GRAPHICS_DRAW2D_H
