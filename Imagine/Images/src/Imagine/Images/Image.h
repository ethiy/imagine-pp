// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

#include "PixelTraits.h"
#include "Interpol.h"
#include "Border.h"

namespace Imagine {
    /// \addtogroup Images
    /// @{

    /// \headerfile Imagine/Images.h "Imagine/Images.h"
    /// %Image.
    /// %Image of variable size, dimension and pixel type. Memory is reference counted, i.e.:
    /// - a=b results in a and b sharing the same memory
    /// - the last object using memory frees it when it dies
    /// - use clone() when this sharing is not desired
    ///
    /// \param T pixel type
    /// \param dim dimension (default=2)
    template <typename T, int dim=2> class Image : public MultiArray<T,dim> {
        typedef MultiArray<T,dim> Base;

    public:
        /// Scalar type.
        /// This is useful for images whose pixel type T is itself composed,
        /// like an FVector<U>, RGB<U>, or Color, in which case scalar_type is
        /// U (byte for Color).
        typedef typename PixelTraits<T>::scalar_type scalar_type;
        /// Iterator type.
        typedef typename Base::iterator iterator;
        /// Const iterator type.
        typedef typename Base::const_iterator const_iterator;

        /// Empty constructor.
        /// Constructs an unallocated image of pixels of type T
        ///
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline non allocated
        Image() : Base() {}
        /// Constructor (known size).
        /// Constructs an allocated image of pixels of type T and dimension dim. sz[i] specifies size for dimension i.
        /// \param sz image sizes
        ///
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline allocated with specified size
        explicit Image(const Coords<dim>& sz) : Base(sz) {}
        /// Constructor (known size, 2D).
        /// Constructs an allocated image of pixels of type T and dimension 2.
        /// \param w,h image size
        ///
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline allocated with specified size (2D alias)
        Image(int w, int h) : Base(w,h) {}
        /// Constructor (known size, 3D).
        /// Constructs an allocated image of pixels of type T and dimension 3.
        /// \param w,h,d image size
        ///
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline allocated with specified size (3D alias)
        Image(int w, int h, int d) : Base(w,h,d) {}
        /// Constructor (pre-allocated).
        /// Constructs an image of pixels of type T and dimension dim, stored at an already allocated memory. ptr contains elements (0,0,...), (1,0,...), ...
        /// Does not allocate fresh memory. Does not free given memory at object destruction unless handleDelete=true. This memory must indeed stay available 
        /// during object life.
        /// \param ptr address of memory
        /// \param sz image sizes
        /// \param handleDelete delete memory at destruction? (default=false)
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline pre-allocated
        /// \until ...
        Image(T* ptr, const Coords<dim>& sz,bool handleDelete=false) : Base(ptr,sz,handleDelete) {}
        /// Constructor (pre-allocated 2D).
        /// Constructs an image of pixels of type T and dimension 2, stored at an already allocated memory.
        /// Does not allocate fresh memory. Does not free given memory at object destruction unless handleDelete=true. This memory must indeed stay available 
        /// during object life.
        /// \param ptr address of memory
        /// \param w,h image size
        /// \param handleDelete delete memory at destruction? (default=false)
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline pre-allocated, 2D
        ///
        Image(T* ptr, int w,int h,bool handleDelete=false) : Base(ptr,w,h,handleDelete) {}
        /// Constructor (pre-allocated 3D).
        /// Constructs an image of pixels of type T and dimension 3, stored at an already allocated memory.
        /// Does not allocate fresh memory. Does not free given memory at object destruction unless handleDelete=true. This memory must indeed stay available 
        /// during object life.
        /// \param ptr address of memory
        /// \param w,h,d image size
        /// \param handleDelete delete memory at destruction? (default=false)
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline pre-allocated, 3D
        Image(T* ptr, int w,int h,int d,bool handleDelete=false) : Base(ptr,w,h,d,handleDelete) {}
        /// Copy constructor.
        /// Constructs an image from another one (sharing memory!)
        /// \param I image to copy
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline copy constructor
        Image(const Base& I) : Base(I) {}
        /// Constructor (different type).
        /// Constructs an image of type T from one of another type (thus without sharing memory!)
        /// \param I image to copy
        /// \tparam T2 type of I
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline from different type
        /// \until ...
        template <typename T2> Image(const MultiArray<T2,dim> &I) : Base(I) {}
        /// Destructor.
        /// Reference counted desctructor: frees memory if the object is the last one to use it.
        virtual ~Image() {}
        /// Assignment.
        /// Assigns from image (sharing its memory)
        /// \param I image to be assigned to
        /// \return self reference
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline assignment 
        Image& operator=(const Base& I) { Base::operator = (I); return *this; }
        /// Assignment (different type).
        /// Assign from an image of another type (thus without sharing memory!)
        /// \param I image to copy
        /// \tparam T2 type of I
        /// \return self reference
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline different type assignment
        /// \until ...
        template <typename T2> Image& operator= (const MultiArray<T2,dim> &I) {
            Base::operator = (I);
            return *this;
        }
        /// Cloning.
        /// Clones: creates a new image, with fresh memory, copying values to it
        /// \return cloned image
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline cloning (fresh memory)
        Image clone() const { return Base::clone(); }
        /// Filling.
        /// Fills with constant value
        /// \param x value to be copied to each element
        /// \return self reference
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline filling with constant value
        Image& fill(T x) { Base::fill(x); return *this; }
        /// Sub image.
        /// Constructs a sub image, i.e. a new one with fresh memory, initialized from a part of values of *this
        /// \param offset coordinates of first element
        /// \param sz sizes of sub image
        /// \return sub image
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline sub image
        Image getSubImage(const Coords<dim> &offset, const Coords<dim> &sz) const {
            return this->getSubArray(offset,sz);
        }

        /// Sub image (2D).
        /// Construct a sub image, i.e. a new one with fresh memory, initialized from a part of values of *this
        /// \param x,y coordinates of first element
        /// \param w,h sizes of sub image
        /// \return sub image
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline sub image 2D
        Image getSubImage(int x,int y,int w,int h) const {
            return this->getSubArray(Coords<2>(x,y),Coords<2>(w,h));
        }
        /// Sub image (3D).
        /// Construct a sub image, i.e. a new one with fresh memory, initialized from a part of values of *this
        /// \param x,y,z coordinates of first element
        /// \param w,h,d sizes of sub image
        /// \return sub image
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline sub image 3D
        Image getSubImage(int x,int y,int z,int w,int h,int d) const {
            return this->getSubArray(Coords<3>(x,y,z),Coords<3>(w,h,d));
        }
        /// Interpolation.
        /// Bilinear interpolation of a pixel value. Return type depends on coordinates type (e.g double coordinates yield double of RGB<double> value)
        /// \tparam V coordinates type
        /// \param c coordinates
        /// \return interpolated value
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline interpolation
        /// \until ...
        template <typename V> typename PixelTraits<T>::template CastPixel<V>::value_type interpolate(const FVector<V,dim>& c) const { return Imagine::interpolate(*this,c); }
        /// Interpolation with automated return type, 2D alias.
        template <typename V> typename PixelTraits<T>::template CastPixel<V>::value_type interpolate(V x, V y) const { return Imagine::interpolate(*this,FVector<V,2>(x,y)); }
        /// Interpolation with automated return type, 3D alias.
        template <typename V> typename PixelTraits<T>::template CastPixel<V>::value_type interpolate(V x, V y, V z) const { return Imagine::interpolate(*this,FVector<V,3>(x,y,z)); }
        /// Neumann access.
        /// Acces with Neumann border conditions: I(x,y)=I(0,y) if x<0, ...
        /// \param c coordinates
        /// \return value
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline Neumann access
        T neumann(const Coords<dim>& c) const { return NeumannBorder<T,dim>()(*this,c); }
        /// Neumann (2D alias).
        T neumann(int x, int y) const { return NeumannBorder<T,2>()(*this,Coords<2>(x,y)); }
        /// Neumann (3D alias).
        T neumann(int x, int y, int z) const { return NeumannBorder<T,3>()(*this,Coords<3>(x,y,z)); }
        /// Dirichlet access.
        /// Acces with Dirichlet border conditions: I(x,y)=out if x<0, ...
        /// \param c coordinates
        /// \param out constant (default=T(0))
        /// \return value
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline Dirichlet access
        T dirichlet(const Coords<dim>& c, T out= T(0)) const { return DirichletBorder<T,dim>(out)(*this,c); }
        /// Dirichlet (2D alias).
        T dirichlet(int x, int y, T out= T(0)) const { return DirichletBorder<T,2>(out)(*this,Coords<2>(x,y)); }
        /// Dirichlet (3D alias).
        T dirichlet(int x, int y, int z, T out= T(0)) const { return DirichletBorder<T,3>(out)(*this,Coords<3>(x,y,z)); }
        /// Mirror access.
        /// Acces with mirror border conditions: I(x,y)=I(-x,y) if x<0, ...
        /// \param c coordinates
        /// \return value
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline mirror access
        T mirror(const Coords<dim>& c) const { return MirrorBorder<T,dim>()(*this,c); }
        /// Mirror access (2D alias).
        T mirror(int x, int y) const { return MirrorBorder<T,2>()(*this,Coords<2>(x,y)); }
        /// Mirror access (3D alias).
        T mirror(int x, int y, int z) const { return MirrorBorder<T,3>()(*this,Coords<3>(x,y,z)); }
        /// Inversed mirror access.
        /// Acces with inversed mirror border conditions: I(x,y)=2*I(0,y)-I(-x,y) if x<0, ...
        /// \param c coordinates
        /// \return value
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline inversed mirror access
        T invMirror(const Coords<dim>& c) const { return InvMirrorBorder<T,dim>()(*this,c); }
        /// Inversed mirror access (2D alias).
        T invMirror(int x, int y) const { return InvMirrorBorder<T,2>()(*this,Coords<2>(x,y)); }
        /// Inversed mirror access (3D alias).
        T invMirror(int x, int y, int z) const { return InvMirrorBorder<T,3>()(*this,Coords<3>(x,y,z)); }
        
        
        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        /// Sum of pixels.
        /// Sum of pixel values. <b>Beware of overflow</b>.
        /// \param I argument
        /// \return sum
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline sum of pixels
        friend inline T sum(const Image& I) {
            return std::accumulate(I.begin(), I.end(), T(scalar_type(0)));
        }
        /// Squared Euclidean norm.
        /// Squared Euclidean norm of pixel values, i.e the sum of the squared norm of pixels. <b>Beware of overflow</b>.
        /// \param I argument
        /// \return squared norm.
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline Squared Euclidean norm
        friend inline scalar_type norm2(const Image& I) {
            scalar_type n = 0;
            for (const_iterator it = I.begin() ; it != I.end() ; ++it) {
                n += (*it) * (*it);
            }
            return n;
        }
        /// Euclidean norm.
        /// Euclidean norm of pixel values. <b>Beware of overflow</b>.
        /// \param I argument
        /// \return norm.
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline Euclidean norm
        friend inline scalar_type norm(const Image& I) {
            assert( !std::numeric_limits<T>::is_integer );
            return ::sqrt(norm2(I));
        }
        /// Opposite.
        /// Oppsite of an image
        /// \return opposite 
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline unary -
        Image operator-() const {
            Image C(this->sizes());
            iterator it3 = C.begin();
            for (const_iterator it1 = this->begin() ; it1 != this->end() ; ++it1, ++it3)
                *it3 = - *it1;
            return C;
        }
        /// Addition.
        /// Addition of two images
        /// \param B image to be added to myself
        /// \return sum 
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline image +
        Image operator+(const Image& B) const {
            assert(this->sizes()==B.sizes());
            Image C(this->sizes());
            iterator it3 = C.begin();
            for (const_iterator it1 = this->begin(), it2 = B.begin() ; it1 != this->end() ; ++it1, ++it2, ++it3)
                *it3 = *it1 + *it2;
            return C;
        }
        /// In place Addition.
        /// In place Addition of two images
        /// \param B image to be added to myself
        /// \return self reference
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline image +=
        Image& operator+=(const Image& B) {
            assert(this->sizes()==B.sizes());
            iterator it1 = this->begin();
            for (const_iterator it2 = B.begin() ; it2 != B.end() ; ++it1, ++it2)
                *it1+=*it2;
            return *this;
        }
        /// Substraction.
        /// Substraction of two images
        /// \param B image to be substracted from myself
        /// \return difference 
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline image -
        Image operator-(const Image& B) const {
            assert(this->sizes()==B.sizes());
            Image C(this->sizes());
            iterator it3 = C.begin();
            for (const_iterator it1 = this->begin(), it2 = B.begin() ; it1 != this->end() ; ++it1, ++it2, ++it3)
                *it3 = *it1 - *it2;
            return C;
        }
        /// In place substraction.
        /// In place substraction of two images
        /// \param B image to be substracted from myself
        /// \return self reference
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline image -=
        Image& operator-=(const Image& B) {
            assert(this->sizes()==B.sizes());
            iterator it1 = this->begin();
            for (const_iterator it2 = B.begin() ; it2 != B.end() ; ++it1, ++it2)
                *it1-=*it2;
            return *this;
        }
        /// Constant addition.
        /// Addition of a constant
        /// \param v constant to be added to myself
        /// \return result 
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline constant +
        Image operator+(T v) const {
            Image C(this->sizes());
            iterator it3 = C.begin();
            for (const_iterator it1 = this->begin() ; it1 != this->end() ; ++it1, ++it3)
                *it3 = *it1 + v;
            return C;
        }
        /// Constant addition.
        /// Addition of a constant
        /// \param v constant to be added to I
        /// \param I image
        /// \return result 
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline constant + image
        friend inline Image operator+(T v, const Image& I) { return I+v; }
        /// In place constant addition.
        /// In place addition of a constant
        /// \param v constant to be added to myself
        /// \return self reference 
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline constant +=
        Image& operator+=(T v){
            for (iterator it = this->begin() ; it != this->end() ; ++it)
                *it+=v;
            return *this;
        }
        /// Constant substraction.
        /// Substraction of a constant
        /// \param v constant to be substracted from myself
        /// \return result 
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline constant -
        Image operator-(T v) const {
            Image C(this->sizes());
            iterator it3 = C.begin();
            for (const_iterator it1 = this->begin() ; it1 != this->end() ; ++it1, ++it3)
                *it3 = *it1 - v;
            return C;
        }
        /// Constant substraction.
        /// Substraction of a constant
        /// \param v constant from which I is to be substracted
        /// \param I image
        /// \return result 
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline constant - image
        friend inline Image operator-(T v, const Image& I) { return (-I)+v; }
        /// In place constant substraction.
        /// In place substraction of a constant
        /// \param v constant to be substracted from myself
        /// \return self reference 
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline constant -=
        Image& operator-=(T v){
            for (iterator it = this->begin() ; it != this->end() ; ++it)
                *it-=v;
            return *this;
        }
        /// Scalar multiplication.
        /// Multiplication by a scalar
        /// \param s scalar factor
        /// \return result 
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline scalar *
        Image operator*(scalar_type s) const {
            Image C(this->sizes());
            iterator it3 = C.begin();
            for (const_iterator it1 = this->begin() ; it1 != this->end() ; ++it1, ++it3)
                *it3 = *it1 * s;
            return C;
        }
        /// Scalar multiplication.
        /// Multiplication by a scalar
        /// \param s scalar factor
        /// \param I image
        /// \return result 
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline scalar * image
        friend inline Image operator*(scalar_type s, const Image& I) { return I*s; }
        /// In place scalar multiplication.
        /// In place multiplication by a scalar
        /// \param s scalar factor
        /// \return self reference 
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline scalar *=
        Image& operator*=(scalar_type s){
            for (iterator it = this->begin() ; it != this->end() ; ++it)
                *it*=s;
            return *this;
        }
        /// Scalar division.
        /// Division by a scalar
        /// \param s scalar factor
        /// \return result 
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline scalar /
        Image operator/(scalar_type s) const {
            Image C(this->sizes());
            iterator it3 = C.begin();
            for (const_iterator it1 = this->begin() ; it1 != this->end() ; ++it1, ++it3)
                *it3 = *it1 / s;
            return C;
        }
        /// In place scalar division.
        /// In place division by a scalar
        /// \param s scalar factor
        /// \return self reference 
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline scalar /=
        Image& operator/=(scalar_type s){
            for (iterator it = this->begin() ; it != this->end() ; ++it)
                *it/=s;
            return *this;
        }
        /// Pointwise scalar multiplication.
        /// Pointwise multiplication by a scalar image
        /// \param B scalar image
        /// \return result 
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline pointwise scalar *
        Image operator*(const Image<scalar_type,dim>& B) const {
            assert(this->sizes()==B.sizes());
            Image C(this->sizes());
            iterator it3 = C.begin();
            typename Image<scalar_type,dim>::const_iterator it2 = B.begin();
            for (const_iterator it1 = this->begin() ; it1 != this->end() ; ++it1, ++it2, ++it3)
                *it3 = *it1 * *it2;
            return C;
        }
        /// In place pointwise scalar multiplication.
        /// In place pointwise multiplication by a scalar image
        /// \param B scalar image
        /// \return self reference 
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline pointwise scalar *=
        Image& operator*=(const Image<scalar_type,dim>& B) {
            assert(this->sizes()==B.sizes());
            iterator it1 = this->begin();
            for (typename Image<scalar_type,dim>::const_iterator it2 = B.begin() ; it2 != B.end() ; ++it1, ++it2)
                *it1*=*it2;
            return *this;
        }
        /// Pointwise scalar division.
        /// Pointwise division by a scalar image
        /// \param B scalar image
        /// \return result 
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline pointwise scalar /
        Image operator/(const Image<scalar_type,dim>& B) const {
            assert(this->sizes()==B.sizes());
            Image C(this->sizes());
            iterator it3 = C.begin();
            typename Image<scalar_type,dim>::const_iterator it2 = B.begin();
            for (const_iterator it1 = this->begin() ; it1 != this->end() ; ++it1, ++it2, ++it3)
                *it3 = *it1 / *it2;
            return C;
        }
        /// In place pointwise scalar division.
        /// In place pointwise division by a scalar image
        /// \param B scalar image
        /// \return self reference 
        /// 
        /// \dontinclude Images/test/test.cpp \skip images()
        /// \skipline pointwise scalar /=
        Image& operator/=(const Image<scalar_type,dim>& B) {
            assert(this->sizes()==B.sizes());
            iterator it1 = this->begin();
            for (typename Image<scalar_type,dim>::const_iterator it2 = B.begin() ; it2 != B.end() ; ++it1, ++it2)
                *it1/=*it2;
            return *this;
        }
    };

    ///@}
}
