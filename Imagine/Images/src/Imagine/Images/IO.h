// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

namespace Imagine {
    /// \addtogroup Images
    /// @{



    /// Create a transparency mask from a specified color-key.
    /// Create a transparency mask from a specified color-key.
    /// Hides a color in current image by making it invisible.
    /// \param I image to modify
    /// \param col color to hide
    ///
    /// \dontinclude Images/test/test.cpp \skip io_transparency()
    /// \skipline Create mask
    /// \until ...
    inline void createMaskFromColor(Image<AlphaColor>& I, AlphaColor col) {
        AlphaColor* aC = I.data();
        setMaskFromColor(aC,I.width(), I.height(), col);
    }

    // Files

    /// Load grey image.
    /// Loads a grey (i.e byte) image from a file. Known formats are JPG, PNG, TIFF
    /// \param I image to load
    /// \param name file name
    /// \return true if OK
    ///
    /// \dontinclude Images/test/test.cpp \skip io()
    /// \skipline load grey
    inline bool load(Image<byte>& I, std::string name) {
        int W,H;
        byte* G;
        if (!loadGreyImage(name,G,W,H))
            return false;
        I = Image<byte>(G,W,H,true);
        return true;
    }
    /// Save grey image.
    /// Saves a grey (i.e byte) image to a file. Known formats are JPG, PNG, TIFF
    /// \param I image to save
    /// \param name file name
    /// \return true if OK
    ///
    /// \dontinclude Images/test/test.cpp \skip io()
    /// \skipline save grey
    inline bool save(const Image<byte>& I, std::string name) {
        return saveGreyImage(name,(byte *)I.data(),I.width(),I.height());
    }
    /// Load color image.
    /// Loads a color (i.e Color) image from a file. Known formats are JPG, PNG, TIFF
    /// \param I image to load
    /// \param name file name
    /// \return true if OK
    ///
    /// \dontinclude Images/test/test.cpp \skip io()
    /// \skipline load color
    inline bool load(Image<Color>& I, std::string name) {
        int W,H;
        Color* G;
        if (!loadColorImage(name,G,W,H))
            return false;
        I = Image<Color>(G,W,H,true);
        return true;
    }
    /// Load color image with alpha channel.
    /// Loads a alpha color (i.e AlphaColor) image from a file. Known formats are JPG, PNG, TIFF, GIF.
    /// Prefer PNG for image with transparency displaying.
    /// \param I image to load
    /// \param name file name
    /// \return true if OK
    ///
    /// \dontinclude Images/test/test.cpp \skip io_transparency()
    /// \skipline Load PNG image
    /// \until ...
    inline bool load(Image<AlphaColor>& I, std::string name) {
        int W,H;
        AlphaColor* aC;
        if(!loadAlphaColorImage(name,aC,W,H))
            return false;
        I = Image<AlphaColor>(aC,W,H,true);
        return true;
    }

    /// Load color image.
    /// Loads a color (i.e 3 chanels) images from a file. Known formats are JPG, PNG, TIFF
    /// \param IR,IG,IB R,G,B images to load
    /// \param name file name
    /// \return true if OK
    ///
    /// \dontinclude Images/test/test.cpp \skip io()
    /// \skipline load color chanels
    inline bool load(Image<byte>& IR, Image<byte>& IG, Image<byte>& IB, std::string name) {
        int W,H;
        byte *R,*G,*B;
        if (!loadColorImage(name,R,G,B,W,H))
            return false;
        IR = Image<byte>(R,W,H,true);
        IG = Image<byte>(G,W,H,true);
        IB = Image<byte>(B,W,H,true);
        return true;
    }
    /// Save color image.
    /// Saves a color (i.e Color) image to a file. Known formats are JPG, PNG, TIFF
    /// \param I image to save
    /// \param name file name
    /// \param quality Jpeg quality (between 0 and 100)
    /// \return true if OK
    ///
    /// \dontinclude Images/test/test.cpp \skip io()
    /// \skipline save color
    /// \until ...
    inline bool save(const Image<Color>& I, std::string name,int quality=85) {
        return saveColorImage(name,I.data(),I.width(),I.height(),quality);
    }
    /// Save color imagewith alpha channel.
    /// Saves a alpha color (i.e AlphaColor) image to a file. Known formats are JPG, PNG, TIFF, GIF
    /// \param I image to save
    /// \param name file name
    /// \param quality Jpeg quality (between 0 and 100)
    /// \return true if OK
    ///
    /// \dontinclude Images/test/test.cpp \skip io_transparency()
    /// \skipline save image with alpha channel
    inline bool save(Image<AlphaColor>& I, std::string name, int quality=85) {
        return saveAlphaColorImage(name, I.data(), I.width(), I.height(), quality);
    }


    /// Save color image.
    /// Saves a color (i.e 3 chanels) image to a file. Known formats are JPG, PNG, TIFF
    /// \param IR,IG,IB R,G,B chanels to save
    /// \param name file name
    /// \param quality Jpeg quality (between 0 and 100)
    /// \return true if OK
    ///
    /// \dontinclude Images/test/test.cpp \skip io()
    /// \skipline save color chanels
    inline bool save(const Image<byte>& IR, const Image<byte>& IG, const Image<byte>& IB, std::string name,int quality=85) {
        assert(IR.sizes() == IG.sizes() && IR.sizes() == IB.sizes());
        return saveColorImage(name,(byte *)IR.data(),(byte *)IG.data(),(byte *)IB.data(),IR.width(),IR.height(),quality);
    }

    //==================== DISPLAY ===============

    /// Display grey image.
    /// Displays a grey image in current Window. NB: zooming factor is a fast hardware rendering and does not necesseraly use interpolation or anti aliasing. 
    /// \param I image to display
    /// \param x,y position in window (default=(0,0))
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    /// \param fact scaling factor (default=1.)
    ///
    /// \dontinclude Images/test/test.cpp \skip io()
    /// \skipline display grey
    inline void display(const Image<byte>& I, int x=0, int y=0,bool xorMode=false,double fact=1.) {
        putGreyImage(x,y,(byte *)I.data(),I.width(),I.height(),xorMode,fact);
    }
    /// Display grey image (IntPoint2 alias).
    inline void display(const Image<byte>& I,IntPoint2 p,bool xorMode=false,double fact=1.) { display(I,p.x(),p.y(),xorMode,fact); }
    /// Display color image.
    /// Displays a color image in current Window. NB: zooming factor is a fast hardware rendering and does not necesseraly use interpolation or anti aliasing. 
    /// \param I image to display
    /// \param x,y position in window (default=(0,0))
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    /// \param fact scaling factor (default=1.)
    ///
    /// \dontinclude Images/test/test.cpp \skip io()
    /// \skipline display color
    inline void display(const Image<Color>& I, int x=0, int y=0,bool xorMode=false,double fact=1.) {
        putColorImage(x,y,(Color *)I.data(),I.width(),I.height(),xorMode,fact);
    }
    /// Display color image with alpha channel.
    /// Displays a alpha color image in current Window. NB: zooming factor is a fast hardware rendering and does not necesseraly use interpolation or anti aliasing.
    /// \param I image to display
    /// \param x,y position in window (default=(0,0))
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    /// \param fact scaling factor (default=1.)
    ///
    /// \dontinclude Images/test/test.cpp \skip io_transparency()
    /// \skipline Display PNG Image
    inline void display(const Image<AlphaColor>& I, int x = 0, int y = 0, bool xorMode = false, double fact=1.) {
        putAlphaColorImage(x,y,(AlphaColor *)I.data(), I.width(), I.height(), xorMode, fact);
    }

    /// Display color image (IntPoint2 alias).
    inline void display(const Image<Color>& I,IntPoint2 p,bool xorMode=false,double fact=1.) { display(I,p.x(),p.y(),xorMode,fact); }
    /// Display color image (3 chanels).
    /// Displays a color image given by 3 chanels in current Window. NB: zooming factor is a fast hardware rendering and does not necesseraly use interpolation or anti aliasing. 
    /// \param IR,IG,IB image to display
    /// \param x,y position in window (default=(0,0))
    /// \param xorMode XOR drawing (default=off). Used twice, recovers the original content
    /// \param fact scaling factor (default=1.)
    ///
    /// \dontinclude Images/test/test.cpp \skip io()
    /// \skipline display color (3 chanels)
    inline void display(const Image<byte>& IR, const Image<byte>& IG, const Image<byte>& IB, int x=0, int y=0,bool xorMode=false,double fact=1.) {
        assert( IR.sizes() == IG.sizes() && IR.sizes() == IB.sizes());
        putColorImage(x,y,(byte *)IR.data(),(byte *)IG.data(),(byte *)IB.data(),IR.width(),IR.height(),xorMode,fact);
    }
    /// Display color image (3 chanels, IntPoint2 alias).
    inline void display(const Image<byte>& IR, const Image<byte>& IG, const Image<byte>& IB,IntPoint2 p,bool xorMode=false,double fact=1.) { display(IR,IG,IB,p.x(),p.y(),xorMode,fact);    }
    /// 2D cut.
    /// Extract a 2D cut from a N-dimensional image
    /// \param I image to cut
    /// \param cut a point of the cut (used to set every fixed coordinates).
    /// \param d1 the first moving coordinate.
    /// \param d2 the second moving coordinate.
    ///
    /// \dontinclude Images/test/test.cpp \skip io()
    /// \skipline 2D cut
    template <typename T, int dim> 
    Image<T> cut2D(const Image<T,dim>& I,const Coords<dim>& cut,int d1,int d2) 
    {
        Coords<2> sz=Coords<2>(I.size(d1),I.size(d2));
        Image<T> C(sz);
        Coords<dim> p=cut;
        for (CoordsIterator<2> r=C.coordsBegin();r!=C.coordsEnd();++r) {
            p[d1]=(*r)[0];
            p[d2]=(*r)[1];
            C(*r)=I(p);
        }
        return C;
    }

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    // Finds the color of from a rainbow palette from m to M (BLUE to RED)
    // Private usage...
    template <typename T> Color rainbowColor(T x, T m, T M) {   
        const T r=T(.25);
        x=(x-m)/(M-m);
        x=std::min(T(1.),std::max(T(0.),x));
        if (x<r) 
            return Color(0,byte(255*x/r),255);
        x-=r;
        if (x<r) 
            return Color(0,255,byte(255*(1-x/r)));
        x-=r;
        if (x<r) 
            return Color(byte(255*x/r),255,0);
        x-=r;
        return Color(255,byte(255*(1-x/r)),0);
    }
#endif

    /// Rainbow representation.
    /// Represents a scalar image by a rainbow scale (from RED to BLUE) for display purposes
    /// \param I image to represent
    /// \param m,M extremal values (m (or less) will be RED, M (or more) will be BLUE)
    ///
    /// \dontinclude Images/test/test.cpp \skip io()
    /// \skipline to rainbow (given range)
    template <typename T, int dim> 
    Image<Color,dim> rainbow(const Image<T,dim>& I, T m, T M) 
    {
        Image<Color,dim> c(I.sizes());
        typename Image<T,dim>::const_iterator it1 = I.begin();
        typename Image<Color,dim>::iterator it2 = c.begin();
        for ( ; it1 != I.end() ; ++it1, ++it2) {
            *it2 = rainbowColor(*it1,m,M);
        }
        return c;
    }
    /// Rainbow representation.
    /// Represents a scalar image by a rainbow scale (from RED for min value to BLUE for max value) for display purposes
    /// \param I image to represent
    ///
    /// \dontinclude Images/test/test.cpp \skip io()
    /// \skipline to rainbow
    template <typename T, int dim> 
    Image<Color,dim> rainbow(const Image<T,dim>& I) 
    {
        std::pair<T,T> r=range(I);
        return rainbow(I,r.first,r.second);
    }
    /// Grey level representation.
    /// Represents a scalar image by a grey scale (from BLACK to WHITE) for display purposes
    /// \param I image to represent
    /// \param m,M extremal values (m (or less) will be BLACK, M (or more) WHITE)
    ///
    /// \dontinclude Images/test/test.cpp \skip io()
    /// \skipline to grey (given range)
    template <typename T, int dim> 
    Image<byte,dim> grey(const Image<T,dim>& I, T m, T M) 
    {
        Image<byte,dim> c(I.sizes());
        typename Image<T,dim>::const_iterator it1 = I.begin();
        typename Image<byte,dim>::iterator it2 = c.begin();
        for ( ; it1 != I.end() ; ++it1, ++it2) {
            T v=std::min(M,std::max(m,*it1));
            *it2 = byte((v-m)*255/(M-m));
        }
        return c;
    }
    /// Grey level representation.
    /// Represents a scalar image by a grey scale (from BLACK for min value to WHITE for max value) for display purposes
    /// \param I image to represent
    ///
    /// \dontinclude Images/test/test.cpp \skip io()
    /// \skipline to grey
    template <typename T, int dim> 
    Image<byte,dim> grey(const Image<T,dim>& I) 
    {
        std::pair<T,T> r=range(I);
        if (r.first==r.second)
            r.second=r.second+T(1);
        return grey(I,r.first,r.second);
    }
    /// Color representation.
    /// Represents a RGB<T> image by a Color one (each coordinate being rescaled from 0 to 255 and stored to respective R,G or B channel) 
    /// \param I image to represent
    /// \param m,M extremal values (For each channel, m[i] (or less) will be 0, M[i] (or more) 255)
    ///
    /// \dontinclude Images/test/test.cpp \skip io()
    /// \skipline to color (given range)
    template <typename T, int dim> 
    Image<Color,dim> color(const Image<RGB<T>,dim>& I,const RGB<T>& m,const RGB<T>& M) 
    {
        Image<Color,dim> C(I.sizes());
        typename Image<RGB<T>,dim>::const_iterator it1 = I.begin();
        typename Image<Color,dim>::iterator it2 = C.begin();
        for ( ; it1 != I.end() ; ++it1, ++it2) {
            RGB<T> v=pmin(M,pmax(m,*it1));
            *it2 = Color(div((v-m)*255,(M-m)));
        };
        return C;
    }
    /// Color representation.
    /// Represents a RGB<T> image by a Color one (each coordinate being rescaled from 0 for min value to 255 for max value, and stored to respective R,G or B channel) 
    /// \param I image to represent
    ///
    /// \dontinclude Images/test/test.cpp \skip io()
    /// \skipline to color
    template <typename T, int dim> 
    Image<Color,dim> color(const Image<RGB<T>,dim>& I) 
    {
        std::pair<RGB<T>, RGB<T> > r=prange(I);
        return color(I,r.first,r.second);
    }


    ///@}
}

#include "Analyze.h"
