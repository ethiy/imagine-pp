// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

#ifndef IMAGINE_GRAPHICS_IMAGEIO_H
#define IMAGINE_GRAPHICS_IMAGEIO_H

class QImage;

namespace Imagine {
    /// \addtogroup Graphics
    /// @{

    // ====================================================
    // ImageIO: displaying, loading, saving, capturing, ...

    // Image displaying functions

    /// Display color bitmap.
    /// Displays a color bitmap.  Color array.
    /// \param x,y top left position of bitmap in window
    /// \param cols array of Color, line after line, from top left to bottom right
    /// \param w,h dimensions (h lines of w pixels)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    /// \param fact scaling factor (default=1.)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline put color bitmap (Color array)
    /// \until ...
    void putColorImage(int x, int y, const Color* cols, int w, int h, bool xorMode = false, double fact = 1.);
    /// Display color bitmap.
    /// Displays a color bitmap. Color array.
    /// \param p top left position of bitmap in window
    /// \param cols array of Color, line after line, from top left to bottom right
    /// \param w,h dimensions (h lines of w pixels)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    /// \param fact scaling factor (default=1.)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline put color bitmap (Color array)
    /// \until ...
    inline void putColorImage(const IntPoint2& p, const Color* cols, int w, int h, bool xorMode = false, double fact = 1.)
    { putColorImage(p.x(), p.y(), cols, w, h, xorMode, fact); }
    /// Display color bitmap.
    /// Displays a color bitmap.  1 rgb array.
    /// \param x,y top left position of bitmap in window
    /// \param rgb array of values, line after line, from top left to bottom right: {r(0,0),g(0,0),b(0,0),r(1,0),g(1,0),b(1,0),...}
    /// \param w,h dimensions (h lines of w pixels)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    /// \param fact scaling factor (default=1.)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline put color bitmap (1 rgb array)
    /// \until ...
    void putColorImage(int x, int y, const byte *rgb, int w, int h, bool xorMode = false, double fact = 1.);
    /// Display color bitmap.
    /// Displays a color bitmap.  1 rgb array.
    /// \param p top left position of bitmap in window
    /// \param rgb array of values, line after line, from top left to bottom right: {r(0,0),g(0,0),b(0,0),r(1,0),g(1,0),b(1,0),...}
    /// \param w,h dimensions (h lines of w pixels)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    /// \param fact scaling factor (default=1.)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline put color bitmap (1 rgb array)
    /// \until ...
    inline void putColorImage(const IntPoint2& p, const byte *rgb, int w, int h, bool xorMode = false, double fact = 1.)
    { putColorImage(p.x(), p.y(), rgb, w, h, xorMode, fact); }
    /// Display color bitmap.
    /// Displays a color bitmap. 3 arrays.
    /// \param x,y top left position of bitmap in window
    /// \param r,g,b arrays of RED/GREEN/BLUE values (0-255), line after line, from top left to bottom right
    /// \param w,h dimensions (h lines of w pixels)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    /// \param fact scaling factor (default=1.)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline put color bitmap (3 arrays)
    /// \until ...
    void putColorImage(int x, int y, const byte *r, const byte *g, const byte *b, int w, int h, bool xorMode = false, double fact = 1.);

    /// Display color bitmap.
    /// Displays a color bitmap. 3 arrays.
    /// \param p top left position of bitmap in window
    /// \param r,g,b arrays of RED/GREEN/BLUE values (0-255), line after line, from top left to bottom right
    /// \param w,h dimensions (h lines of w pixels)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    /// \param fact scaling factor (default=1.)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline put color bitmap (3 arrays)
    /// \until ...
    inline void putColorImage(const IntPoint2& p, const byte *r, const byte *g, const byte *b, int w, int h, bool xorMode = false, double fact = 1.)
    { putColorImage(p.x(), p.y(), r, g, b, w, h, xorMode, fact); }

    // Color Image whith transparency displaying functions
    /// Display color bitmap with alpha channel.
    /// Displays a color bitmap. AlphaColor array.
    /// \param x,y top left position of bitmap in window
    /// \param cols array of AlphaColor, line after line, from top left to bottom right
    /// \param w,h dimensions (h lines of w pixels)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    /// \param fact scaling factor (default=1.)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip transparency()
    /// \skipline Load Image with AlphaColor
    /// \until ...
    void putAlphaColorImage(int x, int y, Imagine::AlphaColor *cols, int w, int h, bool xorMode = false, double fact = 1.);
    /// Display color bitmap with alpha channel.
    /// Displays a color bitmap. 4 arrays.
    /// \param x,y top left position of bitmap in window
    /// \param r,g,b,a arrays of RED/GREEN/BLUE/ALPHA values (0-255), line after line, from top left to bottom right
    /// \param w,h dimensions (h lines of w pixels)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    /// \param fact scaling factor (default=1.)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip transparency()
    /// \skipline Load Image with Alpha channel
    /// \until ...
    void putColorImage(int x, int y, const byte *r, const byte *g, const byte *b, const byte *a,int w, int h, bool xorMode = false, double fact = 1.);
    /// Display color bitmap with alpha channel.
    /// Displays a color bitmap. 4 arrays.
    /// \param p top left position of bitmap in window
    /// \param r,g,b,a arrays of RED/GREEN/BLUE/ALPHA values (0-255), line after line, from top left to bottom right
    /// \param w,h dimensions (h lines of w pixels)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    /// \param fact scaling factor (default=1.)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip transparency()
    /// \skipline Load Image with Alpha channel
    /// \until ...
    inline void putColorImage(const IntPoint2& p, const byte *r, const byte *g, const byte *b, const byte *a,int w, int h, bool xorMode = false, double fact = 1.)
    { putColorImage(p.x(), p.y(), r, g, b, a ,w, h, xorMode, fact); }
    /// Display color bitmap with alpha channel.
    /// Displays a color bitmap.  1 rgba array.
    /// \param x,y top left position of bitmap in window
    /// \param rgba array of values, line after line, from top left to bottom right: {r(0,0),g(0,0),b(0,0),a(0,0),r(1,0),g(1,0),b(1,0),b(1,0),...}
    /// \param w,h dimensions (h lines of w pixels)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    /// \param fact scaling factor (default=1.)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip transparency()
    /// \skipline put alphacolor bitmap (1 rgba array)
    /// \until ...
    void putAlphaColorImage(int x, int y, byte *rgba, int w, int h, bool xorMode = false, double fact = 1.);
    /// Display color bitmap with alpha channel.
    /// Displays a color bitmap.  1 rgba array.
    /// \param p top left position of bitmap in window
    /// \param rgba array of values, line after line, from top left to bottom right: {r(0,0),g(0,0),b(0,0),a(0,0),r(1,0),g(1,0),b(1,0),b(1,0),...}
    /// \param w,h dimensions (h lines of w pixels)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    /// \param fact scaling factor (default=1.)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip transparency()
    /// \skipline put alphacolor bitmap (1 rgba array)
    /// \until ...
    void putAlphaColorImage(const IntPoint2& p, byte *rgba, int w, int h, bool xorMode = false, double fact = 1.);
    /// Display grey bitmap.
    /// Displays a grey bitmap.
    /// \param x,y top left position of bitmap in window
    /// \param g array of grey values between 0 and 255, line after line, from top left to bottom right
    /// \param w,h dimensions (h lines of w pixels)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    /// \param fact scaling factor (default=1.)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline put grey bitmap
    /// \until ...
    void putGreyImage(int x, int y, const byte* g, int w, int h, bool xorMode = false, double fact = 1.);
    /// Display grey bitmap.
    /// Displays a grey bitmap.
    /// \param p top left position of bitmap in window
    /// \param g array of grey values between 0 and 255, line after line, from top left to bottom right
    /// \param w,h dimensions (h lines of w pixels)
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    /// \param fact scaling factor (default=1.)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline put grey bitmap
    /// \until ...
    inline void putGreyImage(const IntPoint2& p, const byte* g, int w, int h, bool xorMode = false, double fact = 1.)
    { putGreyImage(p.x(), p.y(), g, w, h, xorMode, fact); }
    /// Create a transparency mask from a specified color-key.
    /// It puts the value 0 to the alpha-channel for all pixels which contain the color you want to hide.
    /// In other words, the Color col becomes invisible
    /// \param r,g,b,a arrays of RED/GREEN/BLUE/ALPHA values (0-255), line after line, from top left to bottom right
    /// \param w,h dimensions (h lines of w pixels)
    /// \param col color that is about to be hidden
    /// /// \dontinclude Graphics/test/test.cpp \skip transparency()
    /// \skipline create mask from a color
    /// \until ...
    void setMaskFromColor(byte *&r, byte *&g, byte *&b, byte *&a, int w, int h, const Color &col);
    /// Create a transparency mask from a specified color-key.
    /// It puts the value 0 to the alpha-channel for all pixels which contain the color you want to hide.
    /// In other words, the Color col becomes invisible
    /// \param rgba array of values, line after line, from top left to bottom right: {r(0,0),g(0,0),b(0,0),a(0,0),r(1,0),g(1,0),b(1,0),a(1,0),...}
    /// \param w,h dimensions (h lines of w pixels)
    /// \param col color that is about to be hidden
    /// \dontinclude Graphics/test/test.cpp \skip transparency()
    /// \skipline create a mask from a color (rgba array)
    /// \until ...
    void setMaskFromColor(byte *&rgba, int w, int h, const Color &col);
    /// Create a transparency mask from a specified color-key.
    /// It puts the value 0 to the alpha-channel for all pixels which contain the color you want to hide.
    /// In other words, the Color col becomes invisible
    /// \param acols array of AlphaColor, line after line, from top left to bottom right
    /// \param w,h dimensions (h lines of w pixels)
    /// \param col color that is about to be hidden
    /// \dontinclude Graphics/test/test.cpp \skip transparency()
    /// \skipline create a mask from a color (AlphaColor array)
    /// \until ...
    void setMaskFromColor(AlphaColor *&acols, int w, int h, AlphaColor col);
    /// Convert a Color Image to a AlphaColor Image.
    /// It puts 255 to the alpha-channel for all pixels
    /// Use this funtion if you want to use setMaskFromColor on a Color Image
    /// \param cols array of Color, line after line, from top left to bottom right
    /// \param w,h dimensions of (h lines of w pixels)
    /// \dontinclude Graphics/test/test.cpp \skip transparency()
    /// \skipline convert Color image to Color image with alpha channel
    /// \until ...
    AlphaColor* convertColorToAlphaColor(const Imagine::Color *cols, int w, int h);
    // Image loading functions
    /// Load color image.
    /// Loads and allocates a color image from a file.
    /// \param name file name
    /// \param cols Color array (see putColorImage())
    /// \param w,h dimensions
    /// \return false if error
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline load color image (Color array)
    /// \until ...
    bool loadColorImage(const std::string& name, Color *&cols, int& w, int& h);
    /// Load color image with alpha channel.
    /// Loads and allocates a color image from a file.
    /// \param name file name
    /// \param acols AlphaColor array (see putAlphaColorImage())
    /// \param w,h dimensions
    /// \return false if error
    ///
    /// \dontinclude Graphics/test/test.cpp \skip transparency()
    /// \skipline Load Image with AlphaColor
    /// \until ...
    bool loadAlphaColorImage(const std::string& name, AlphaColor *&acols, int& w, int& h);
    /// Load color image.
    /// Loads and allocates a color image from a file.
    /// \param name file name
    /// \param rgb array (see putColorImage())
    /// \param w,h dimensions
    /// \return false if error
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline load color image (1 rgb array)
    /// \until ...
    bool loadColorImage(const std::string &name, byte *&rgb, int &w, int &h);
    /// Load color image with alpha channel.
    /// Loads and allocates a color image from a file.
    /// \param name file name
    /// \param rgba array (see putAlphaColorImage())
    /// \param w,h dimensions
    /// \return false if error
    ///
    /// \dontinclude Graphics/test/test.cpp \skip transparency()
    /// \skipline load color image (1 rgba array)
    /// \until ...
    bool loadAlphaColorImage(const std::string &name, byte *&rgba, int &w, int &h);
    /// Load color image.
    /// Loads and allocates a color image from a file.
    /// \param name file name
    /// \param r,g,b arrays (see putColorImage())
    /// \param w,h dimensions
    /// \return false if error
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline load color image (3 arrays)
    /// \until ...
    bool loadColorImage(const std::string &name, byte *&r, byte *&g, byte *&b, int &w, int &h);
    /// Load color image with alpha channel.
    /// Loads and allocates a color image from a file.
    /// \param name file name
    /// \param r,g,b,a arrays (see putAlphaColorImage())
    /// \param w,h dimensions
    /// \return false if error
    ///
    /// \dontinclude Graphics/test/test.cpp \skip transparency()
    /// \skipline Load Image with Alpha channel
    /// \until ...
    bool loadColorImage(const std::string &name, byte *&r, byte *&g, byte *&b, byte*&a, int &w, int &h);
    /// Load grey image.
    /// Loads and allocates a grey image from a file.
    /// \param name file name
    /// \param g array (see putGreyImage())
    /// \param w,h dimensions
    /// \return false if error
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline load grey image
    /// \until ...
    bool loadGreyImage(const std::string& name, byte*& g, int& w, int& h);

    // Image saving functions

    /// Save color image.
    /// Saves a color image into a file.
    /// \param name file name
    /// \param cols array (see putColorImage())
    /// \param w,h dimensions
    /// \param quality Jpeg quality (between 0 and 100)
    /// \return false if error
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline load color image (Color array)
    /// \until ...
    bool saveColorImage(const std::string& name,const Color* cols, int w, int h, int quality = 85);
    /// Save color image with alpha channel.
    /// Saves a color image into a file.
    /// \param name file name
    /// \param cols array (see putAlphaColorImage())
    /// \param w,h dimensions
    /// \param quality Jpeg quality (between 0 and 100)
    /// \return false if error
    ///
    /// \dontinclude Graphics/test/test.cpp \skip transparency()
    /// \skipline create a mask from a color (AlphaColor array)
    /// \until ...
    bool saveAlphaColorImage(const std::string& name, Imagine::AlphaColor *cols, int w, int h, int quality = 85);
    /// Save color image.
    /// Saves a color image into a file.
    /// \param name file name
    /// \param rgb array (see putColorImage())
    /// \param w,h dimensions
    /// \param quality Jpeg quality (between 0 and 100)
    /// \return false if error
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline load color image (1 rgb array)
    /// \until ...
    bool saveColorImage(const std::string &name, const byte *rgb, int w, int h, int quality = 85);
    /// Save color image with alpha channel.
    /// Saves a color image into a file.
    /// \param name file name
    /// \param rgba array (see putAlphaColorImage())
    /// \param w,h dimensions
    /// \param quality Jpeg quality (between 0 and 100)
    /// \return false if error
    ///
    /// \dontinclude Graphics/test/test.cpp \skip transparency()
    /// \skipline create a mask from a color (rgba array)
    /// \until ...
    bool saveAlphaColorImage(const std::string &name, byte *rgba, int w, int h, int quality = 85);
    /// Save color image.
    /// Saves a color image into a file.
    /// \param name file name
    /// \param r,g,b arrays (see putColorImage())
    /// \param w,h dimensions
    /// \param quality Jpeg quality (between 0 and 100)
    /// \return false if error
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline load color image (3 arrays)
    /// \until ...
    bool saveColorImage(const std::string &name, const byte *r, const byte *g, const byte *b, int w, int h, int quality = 85);
    /// Save color image with alpha channel.
    /// Saves a color image into a file.
    /// \param name file name
    /// \param r,g,b,a arrays (see putColorImage())
    /// \param w,h dimensions
    /// \param quality Jpeg quality (between 0 and 100)
    /// \return false if error
    ///
    /// \dontinclude Graphics/test/test.cpp \skip transparency()
    /// \skipline // Save Image with an alpha channel
    /// \until ...
    bool saveAlphaColorImage(const std::string &name, const byte *r, const byte *g, const byte *b, const byte *a,int w, int h, int quality = 85);
    /// Save grey image.
    /// Saves a grey image into a file.
    /// \param name file name
    /// \param g array (see putGreyImage())
    /// \param w,h dimensions
    /// \param quality Jpeg quality (between 0 and 100)
    /// \return false if error
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline load grey image
    /// \until ...
    bool saveGreyImage(const std::string& name, const byte* g, int w, int h, int quality = 85);

    // Image capture functions

    /// Capture (point).
    /// Captures one pixel of the active window. Do not call for all pixels!
    /// \param x,y point to capture
    /// \return color of pixel
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline 2D capture (point)
    Color capturePoint(int x, int y);
    /// Capture (point).
    /// Captures one pixel of the active window. Do not call for all pixels!
    /// \param p point to capture
    /// \return color of pixel
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline 2D capture (point) (IntPoint2)
    inline Color capturePoint(const IntPoint2& p)
    { return capturePoint(p.x(), p.y()); }
    /// Capture (sub window).
    /// Captures part of the active window.
    /// \param x,y top left
    /// \param c Color array (have to be already allocated)
    /// \param w,h dimensions
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline 2D capture (subwindow Color array)
    void captureRectangle(int x, int y, Color *c, int w, int h);
    /// Capture (sub window).
    /// Captures part of the active window.
    /// \param p top left
    /// \param c Color array (have to be already allocated)
    /// \param w,h dimensions
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline 2D capture (subwindow Color array) (IntPoint2)
    inline void captureRectangle(const IntPoint2& p, Color *c, int w, int h)
    { captureRectangle(p.x(), p.y(), c, w, h); }
    /// Capture (sub window).
    /// Captures part of the active window.
    /// \param x,y top left
    /// \param RGB 1 RGB array (have to be already allocated)
    /// \param w,h dimensions
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline 2D capture (subwindow 1 array)
    void captureRectangle(int x, int y, byte *RGB, int w, int h);
    /// Capture (sub window).
    /// Captures part of the active window.
    /// \param p top left
    /// \param RGB 1 RGB array (have to be already allocated)
    /// \param w,h dimensions
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline 2D capture (subwindow 1 array) (IntPoint2)
    inline void captureRectangle(const IntPoint2& p, byte *RGB, int w, int h)
    { captureRectangle(p.x(), p.y(), RGB, w, h); }
    /// Capture (sub window).
    /// Captures part of the active window.
    /// \param x,y top left
    /// \param R,G,B RGB arrays (have to be already allocated)
    /// \param w,h dimensions
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline 2D capture (subwindow 3 arrays)
    void captureRectangle(int x, int y, byte *R, byte *G, byte *B, int w, int h);
    /// Capture (sub window).
    /// Captures part of the active window.
    /// \param p top left
    /// \param R,G,B RGB arrays (have to be already allocated)
    /// \param w,h dimensions
    /// \return color of pixel
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline 2D capture (subwindow 3 arrays) (IntPoint2)
    inline void captureRectangle(const IntPoint2& p, byte *R, byte *G, byte *B, int w, int h)
    { captureRectangle(p.x(), p.y(), R, G, B, w, h); }
    /// Window capture.
    /// Captures the active window. Allocates buffers.
    /// \param cols captured array
    /// \param w,h dimensions (note: might have changed since openWindow!)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline 2D capture (Color array)
    /// \until ...
    void captureWindow(Color *&cols, int &w, int &h);
    /// Window capture.
    /// Captures the active window. Allocates buffers.
    /// \param RGB captured array
    /// \param w,h dimensions (note: might have changed since openWindow!)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline 2D capture (1 array)
    /// \until ...
    void captureWindow(byte *&RGB, int &w, int &h);
    /// Window capture.
    /// Captures the active window. Allocates buffers.
    /// \param R,G,B captured RGB arrays
    /// \param w,h dimensions (note: might have changed since openWindow!)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline 2D capture (3 arrays)
    /// \until ...
    void captureWindow(byte *&R, byte *&G, byte *&B, int &w, int &h);

    // ====================================================
    // NativeBitmap class
#ifndef DOXYGEN_SHOULD_SKIP_THIS
    class NativeBitmapInternal; // Private
    class NativeBitmap;
#endif
    /// Display native bitmap.
    /// Displays native bitmap into active window
    /// \param x,y drawing position (top left in window)
    /// \param bm the native bitmap to display
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    /// \param fact scaling factor (default=1.)
    ///
    /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
    /// \skipline Put native bitmap
    /// \until ...
    void putNativeBitmap(int x,int y,const NativeBitmap &bm,bool xorMode=false,double fact=1.);

    /// \headerfile Imagine/Graphics.h "Imagine/Graphics.h"
    /// Native bitmap: image stored in graphics card format, fast to display.
    /// Use it if you want to display the image many times (for example
    /// in an animation).
    class NativeBitmap {
        NativeBitmapInternal* priv;
    public:
        /// Empty constructor.
        NativeBitmap();
        /// Constructor with dimensions.
        /// Contructs a native bitmap of dimensions (w,h)
        /// \param w,h dimensions
        ///
        /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
        /// \skipline with dimensions
        NativeBitmap(int w,int h);
        /// Copy constructor.
        NativeBitmap(const NativeBitmap& I);
        /// Destructor.
        ~NativeBitmap();
        /// Assignment.
        const NativeBitmap& operator=(const NativeBitmap& I);
        /// Set color image.
        /// Fills part of a native bitmap with a bitmap.
        /// \param x,y top left position in native bitmap
        /// \param r,g,b source to be copied into native bitmap
        /// \param w,h dimensions
        ///
        /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
        /// \skipline Set color image (3 arrays)
        /// \until ...
        void setColorImage(int x,int y,const byte *r,const byte *g,const byte *b,int w,int h);
        /// Set color image.
        /// Fills part of a native bitmap with a bitmap.
        /// \param p top left position in native bitmap
        /// \param r,g,b source to be copied into native bitmap
        /// \param w,h dimensions
        ///
        /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
        /// \skipline Set color image (3 arrays)
        /// \until ...
        inline void setColorImage(const IntPoint2&p,const byte *r,const byte *g,const byte *b,int w,int h)
        {       setColorImage(p.x(),p.y(),r,g,b,w,h);   }
        /// Set color image.
        /// Fills part of a native bitmap with a bitmap.
        /// \param x,y top left position in native bitmap
        /// \param cols source to be copied into native bitmap
        /// \param w,h dimensions
        ///
        /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
        /// \skipline Set color image (Color array)
        /// \until ...
        void setColorImage(int x,int y,const Color *cols,int w,int h);
        /// Set color image.
        /// Fills part of a native bitmap with a bitmap.
        /// \param p top left position in native bitmap
        /// \param cols source to be copied into native bitmap
        /// \param w,h dimensions
        ///
        /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
        /// \skipline Set color image (Color array)
        /// \until ...
        inline void setColorImage(const IntPoint2& p,const Color *cols,int w,int h)
        {       setColorImage(p.x(),p.y(),cols,w,h);    }
        /// Set color image.
        /// Fills part of a native bitmap with a bitmap.
        /// \param x,y top left position in native bitmap
        /// \param rgb source to be copied into native bitmap
        /// \param w,h dimensions
        ///
        /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
        /// \skipline Set color image (1 array)
        /// \until ...
        inline void setColorImage(int x,int y,const byte *rgb,int w,int h)
        {       setColorImage(x,y,(const Color*)rgb,w,h);   }
        /// Set color image.
        /// Fills part of a native bitmap with a bitmap.
        /// \param p top left position in native bitmap
        /// \param rgb source to be copied into native bitmap
        /// \param w,h dimensions
        ///
        /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
        /// \skipline Set color image (1 array)
        /// \until ...
        inline void setColorImage(const IntPoint2& p,const byte *rgb,int w,int h)
        {       setColorImage(p.x(),p.y(),(const Color*)rgb,w,h);   }
        /// Set grey image.
        /// Fills part of a native bitmap with a grey bitmap.
        /// \param x,y top left position in native bitmap
        /// \param g source to be copied into native bitmap
        /// \param w,h dimensions
        ///
        /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
        /// \skipline Set grey image
        /// \until ...
        void setGreyImage(int x,int y,const byte *g,int w,int h);
        /// Set grey image.
        /// Fills part of a native bitmap with a grey bitmap.
        /// \param p top left position in native bitmap
        /// \param g source to be copied into native bitmap
        /// \param w,h dimensions
        ///
        /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
        /// \skipline Set grey image
        /// \until ...
        inline void setGreyImage(const IntPoint2 &p,const byte *g,int w,int h)
        {       setGreyImage(p.x(),p.y(),g,w,h);    }
        /// Set point.
        /// Set color of one point in a native bitmap.
        /// \param x,y position
        /// \param col Color to be copied into native bitmap
        ///
        /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
        /// \skipline Set point
        /// \until ...
        void setPoint(int x,int y,Color col);
        /// Set point.
        /// Set color of one point in a native bitmap.
        /// \param p position
        /// \param col Color to be copied into native bitmap
        ///
        /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
        /// \skipline Set point
        /// \until ...
        inline void setPoint(const IntPoint2&p,Color col)
        {       setPoint(p.x(),p.y(),col);  }
        friend void putNativeBitmap(int x,int y,const NativeBitmap &bm,bool xorMode,double fact);
        /// Display native bitmap.
        /// Displays native bitmap into active window
        /// \param p drawing position (top left in window)
        /// \param bm the native bitmap to display
        /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
        /// \param fact scaling factor (default=1.)
        ///
        /// \dontinclude Graphics/test/test.cpp \skip bitmaps()
        /// \skipline Put native bitmap
        /// \until ...
        friend inline void putNativeBitmap(const IntPoint2& p,const NativeBitmap &bm,bool xorMode=false,double fact=1.) // Variant with IntPoint2
        {       putNativeBitmap(p.x(),p.y(),bm,xorMode,fact);   }
    };

    /// @}
} /* namespace Imagine */

#endif // IMAGINE_GRAPHICS_IMAGEIO_H
