// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

    /// \var byte
    /// 0 to 255 integer type.
    /// alias for 0 to 255 integers
    ///
    /// \dontinclude Common/test/test.cpp \skip colors()
    /// \skipline byte alias
  ///deja inclus dans QT ne pas mettre dans le namespace
    typedef unsigned char byte;

namespace Imagine {
    /// \addtogroup Common
    /// @{


    /// \headerfile Imagine/Common.h "Imagine/Common.h"
    /// RED GREEN BLUE color.
    /// RED GREEN BLUE color
    /// \param T value type
    template <typename T>
    class RGB : public FVector<T,3> {
    private:
        typedef FVector<T,3> Base;
    public:
        /// Empty constructor.
        /// Constructs an uninitialized RGB of type T
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline uninitialized
        RGB() : Base() {}
        /// Constructor with constant value.
        /// Constructs a RGB of type T, each initialized to v
        /// \param v value used for initialization
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline filled with constant value
        explicit RGB(T v) : Base(v) {}
        /// Constructor with r,g,b values
        /// Constructs a RGB of type T
        /// \param r,g,b RED, GREEN, BLUE values
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline rgb values
        RGB(T r,T g,T b) : Base(r,g,b) {}
        /// Constructor from C array.
        /// Constructs a RGB of type T, and copies values to it
        /// \param t C array used for initialization
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline filled from C array 
        /// \until ...
        explicit RGB(const T t[3]): Base(t) {}
        /// Copy constructor.
        /// Constructs from another RGB
        /// \param x RGB to copy
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline copy constructor
        RGB(const Base& x) :  Base(x) {}
        /// Constructor from other value type
        /// Constructs from RGB with different type
        /// \param x RGB to copy
        /// \tparam T2 value type of x
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline from another type
        template <typename T2> RGB(const FVector<T2,3>& x) : Base(x) {}
        /// Constructor from RGBA.
        /// Constructs from RGBA (ignores a)
        /// \param x RGBA to copy
        /// \tparam T2 value type of x
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline RGBA -> RGB
        /// \until ...
        template <typename T2> RGB(const  FArray<T2,4>& x) : Base(T(x[0]), T(x[1]), T(x[2])) {}
        /// Read RED alias.
        /// Read RED alias
        /// \return const ref. to RED
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline Read RED alias
        const T& r() const { return (*this)[0]; }
        /// Write RED alias.
        /// Write RED alias
        /// \return ref. to RED
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline Write RED alias
        T& r() { return (*this)[0]; }
        /// Read GREEN alias.
        /// Read GREEN alias
        /// \return const ref. to GREEN
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline Read GREEN alias
        const T& g() const { return (*this)[1]; }
        /// Write GREEN alias.
        /// Write GREEN alias
        /// \return ref. to GREEN
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline Write GREEN alias
        T& g() { return (*this)[1]; }
        /// Read BLUE alias.
        /// Read BLUE alias
        /// \return const ref. to BLUE
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline Read BLUE alias
        const T& b() const { return (*this)[2]; }
        /// Write BLUE alias.
        /// Write BLUE alias
        /// \return ref. to BLUE
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline Write BLUE alias
        T& b() { return (*this)[2]; }
        /// To greyscale.
        /// Convert to greyscale (grey=0.3*r+0.59*g+0.11*b)
        /// \return greyscale value
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline to greyscale
        operator T () const { return T(0.3*r()+0.59*g()+0.11*b()); }
    };

    /// \headerfile Imagine/Common.h "Imagine/Common.h"
    /// RED GREEN BLUE Alpha color.
    /// RED GREEN BLUE Alpha color
    /// \param T value type
    template <typename T>
    class RGBA : public FVector<T,4> {
    private:
        typedef FVector<T,4> Base;
    public:
        /// Empty constructor.
        /// Constructs an uninitialized RGB of type T
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline uninitialized rgba
        RGBA() : Base() {}
        /// Constructor with constant value.
        /// Constructs a RGBA of type T, rgb initialized to a constant, a to 1
        /// \param x value used for initialization
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline rgb filled with constant value, a=1
        explicit RGBA(T x) : Base(x) { (*this)[3]=T(1); }
        /// Constructor with r,g,b,a values
        /// Constructs a RGBA of type T
        /// \param r,g,b,a RED, GREEN, BLUE, ALPHA values
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline rgba values
        RGBA(T r,T g,T b,T a){
            (*this)[0]=r;(*this)[1]=g;(*this)[2]=b;(*this)[3]=a;
        }
        /// Constructor with r,g,b values
        /// Constructs a RGBA of type T
        /// \param r,g,b RED, GREEN, BLUE values
        /// puts 255 in ALPHA value
        ///
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline rgba values from r, g, b
        RGBA(T r,T g, T b){
            (*this)[0]=r;(*this)[1]=g;(*this)[2]=b;(*this)[3]=T(255);
        }

        /// Constructor from C array.
        /// Constructs a RGBA of type T, and copies values to it
        /// \param t C array used for initialization
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline rgba filled from C array
        /// \until ...
        RGBA(const T t[4]): Base(t) {}
        /// Copy constructor.
        /// Constructs from another RGBA
        /// \param x RGBA to copy
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline rgba copy constructor
        RGBA(const Base& x) :  Base(x) {}
        /// Constructor from other value type
        /// Constructs from RGBA with different type
        /// \param x RGBA to copy
        /// \tparam T2 value type of x
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline rgba from another type
        template <typename T2> RGBA(const FArray<T2,4>& x) : Base(x) {}
        /// Constructor from RGB.
        /// Constructs from RGB (a=1)
        /// \param x RGB to copy
        /// \tparam T2 value type of x
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline RGB -> RGBA
        template <typename T2> RGBA(const FArray<T2,3>& x){
            (*this)[0]=T(x[0]);
            (*this)[1]=T(x[1]);
            (*this)[2]=T(x[2]);
            (*this)[3]=T(255);
        }
        /// Read RED alias.
        /// Read RED alias
        /// \return const ref. to RED
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline RGBA Read RED alias 
        const T& r() const { return (*this)[0]; }
        /// Write RED alias.
        /// Write RED alias
        /// \return ref. to RED
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline RGBA Write RED alias
        T& r() { return (*this)[0]; }
        /// Read GREEN alias.
        /// Read GREEN alias
        /// \return const ref. to GREEN
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline RGBA Read GREEN alias
        const T& g() const { return (*this)[1]; }
        /// Write GREEN alias.
        /// Write GREEN alias
        /// \return ref. to GREEN
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline RGBA Write GREEN alias
        T& g() { return (*this)[1]; }
        /// Read BLUE alias.
        /// Read BLUE alias
        /// \return const ref. to BLUE
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline RGBA Read BLUE alias
        const T& b() const { return (*this)[2]; }
        /// Write BLUE alias.
        /// Write BLUE alias
        /// \return ref. to BLUE
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline RGBA Write BLUE alias
        T& b() { return (*this)[2]; }
        /// Read alpha alias.
        /// Read alpha alias
        /// \return const ref. to alpha
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline RGBA Read alpha alias
        const T& a() const { return (*this)[3]; }
        /// Write alpha alias.
        /// Write alpha alias
        /// \return ref. to alpha
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline RGBA Write alpha alias
        T& a() { return (*this)[3]; }
        /// To greyscale.
        /// Convert to greyscale (grey=0.3*r+0.59*g+0.11*b)
        /// \return greyscale value
        /// 
        /// \dontinclude Common/test/test.cpp \skip colors()
        /// \skipline RGBA to greyscale
        operator T () const { return T(0.3*r()+0.59*g()+0.11*b()); }
    };
    /// \var Color
    /// RGB<byte> alias.
    /// alias for the most common type of color!
    ///
    /// \dontinclude Common/test/test.cpp \skip colors()
    /// \skipline color alias
    typedef RGB<byte> Color;
    /// Predefined color.
    /// Predefined color
    ///
    /// \dontinclude Common/test/test.cpp \skip base()
    /// \skipline predefined WHITE
    const Color WHITE=Color(255,255,255);
    /// Predefined color.
    /// Predefined color
    ///
    /// \dontinclude Common/test/test.cpp \skip base()
    /// \skipline predefined BLACK
    const Color BLACK=Color(0,0,0);
    /// Predefined color.
    /// Predefined color
    ///
    /// \dontinclude Common/test/test.cpp \skip base()
    /// \skipline predefined BLUE
    const Color BLUE=Color(0,0,255);
    /// Predefined color.
    /// Predefined color
    ///
    /// \dontinclude Common/test/test.cpp \skip base()
    /// \skipline predefined RED
    const Color RED=Color(255,0,0);
    /// Predefined color.
    /// Predefined color
    ///
    /// \dontinclude Common/test/test.cpp \skip base()
    /// \skipline predefined GREEN
    const Color GREEN=Color(0,255,0);
    /// Predefined color.
    /// Predefined color
    ///
    /// \dontinclude Common/test/test.cpp \skip base()
    /// \skipline predefined YELLOW
    const Color YELLOW=Color(255,255,0);
    /// Predefined color.
    /// Predefined color
    ///
    /// \dontinclude Common/test/test.cpp \skip base()
    /// \skipline predefined CYAN
    const Color CYAN=Color(0,255,255);
    /// Predefined color.
    /// Predefined color
    ///
    /// \dontinclude Common/test/test.cpp \skip base()
    /// \skipline predefined MAGENTA
    const Color MAGENTA=Color(255,0,255);

    /// Display color as three integral values
    inline std::ostream& operator<<(std::ostream& out, const Color& c) {
        return out << (int)c[0] << ' ' << (int)c[1] << ' ' << (int)c[2];
    }
    /// \var AlphaColor
    /// RGBA<byte> alias.
    /// alias for the most common type of color with alpha channel!
    ///
    /// \dontinclude Common/test/test.cpp \skip colors()
    /// \skipline color alias with alpha channel
    /// \until ...
    typedef RGBA<byte> AlphaColor;
    /// Predefined color.
    /// Predefined color
    ///
    /// \dontinclude Common/test/test.cpp \skip base()
    /// \skipline predefined WHITE
    const AlphaColor AWHITE=AlphaColor(255,255,255);
    /// Predefined color.
    /// Predefined color
    ///
    /// \dontinclude Common/test/test.cpp \skip base()
    /// \skipline predefined BLACK
    const AlphaColor ABLACK=AlphaColor(0,0,0);
    /// Predefined color.
    /// Predefined color
    ///
    /// \dontinclude Common/test/test.cpp \skip base()
    /// \skipline predefined BLUE
    const AlphaColor ABLUE=AlphaColor(0,0,255);
    /// Predefined color.
    /// Predefined color
    ///
    /// \dontinclude Common/test/test.cpp \skip base()
    /// \skipline predefined RED
    const AlphaColor ARED=AlphaColor(255,0,0);
    /// Predefined color.
    /// Predefined color
    ///
    /// \dontinclude Common/test/test.cpp \skip base()
    /// \skipline predefined GREEN
    const AlphaColor AGREEN=AlphaColor(0,255,0);
    /// Predefined color.
    /// Predefined color
    ///
    /// \dontinclude Common/test/test.cpp \skip base()
    /// \skipline predefined YELLOW
    const AlphaColor AYELLOW=AlphaColor(255,255,0);
    /// Predefined color.
    /// Predefined color
    ///
    /// \dontinclude Common/test/test.cpp \skip base()
    /// \skipline predefined CYAN
    const AlphaColor ACYAN=AlphaColor(0,255,255);
    /// Predefined color.
    /// Predefined color
    ///
    /// \dontinclude Common/test/test.cpp \skip base()
    /// \skipline predefined MAGENTA
    const AlphaColor AMAGENTA=AlphaColor(255,0,255);

    /// RGB to YUV.
    /// RGB to YUV
    /// \param rgb RGB color to convert
    /// \return YUV as a vector of doubles
    /// 
    /// \dontinclude Common/test/test.cpp \skip colors()
    /// \skipline RGB to YUV
    template<typename T> inline FVector<double,3> RGB2YUV(const RGB<T>& rgb) {
        double y=.299*double(rgb[0])+.587*double(rgb[1])+.114*double(rgb[2]);
        return FVector<double,3>(y,.492*(double(rgb[2])-y),.877*(double(rgb[0])-y));
    }
    /// YUV to RGB.
    /// YUV to RGB
    /// \param yuv YUV vector to convert
    /// \return RGB color
    /// 
    /// \dontinclude Common/test/test.cpp \skip colors()
    /// \skipline YUV to RGB
    template<typename T> inline RGB<T> YUV2RGB(const FVector<double,3>& yuv) {
        double r(yuv[2]/.877+yuv[0]);
        double b(yuv[1]/.492+yuv[0]);
        double g((yuv[0]-.299*r-.114*b)/.587);
        return RGB<T>(T(r),T(g),T(b));
    }


    ///@}
}
