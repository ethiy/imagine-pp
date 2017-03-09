// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

namespace Imagine {
    /// \addtogroup LinAlg
    /// @{

    template <typename T> class Matrix;
    template <typename T> class SymMatrix;

    /// \headerfile Imagine/LinAlg.h "Imagine/LinAlg.h"
    /// %Vector of variable size.
    /// %Vector of variable size. Memory is reference counted, i.e.:
    /// - a=b results in a and b sharing the same memory
    /// - the last object using memory frees it when it dies
    /// - use clone() when this sharing is not desired
    ///
    /// \param T value type

    template <typename T>
    class Vector : public Array<T> {
        typedef Array<T> Base;
    public:
        /// Iterator type
        typedef typename Base::iterator iterator;
        /// Const iterator type
        typedef typename Base::const_iterator const_iterator;
        /// Empty constructor.
        /// Constructs an unallocated vector of variables of type T
        ///
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline non allocated
        Vector() : Base() {}
        /// Constructor (known size).
        /// Constructs an allocated vector of size variables of type T
        /// \param n vector size
        ///
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline allocated with specified size
        explicit Vector(size_t n) : Base(n) {}
        /// Copy constructor.
        /// Constructs a vector from another one (sharing memory!)
        /// \param v vector to copy
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline copy constructor
        Vector(const Base& v) : Base(v) {}
        /// Constructor (pre-allocated).
        /// Constructs a vector of variables of type T stored at an already allocated memory.
        /// Does not allocate fresh memory. Does not free given memory at object destruction unless handleDelete=true. This memory must indeed stay available 
        /// during object life.
        /// \param ptr address of memory
        /// \param n vector size
        /// \param handleDelete delete memory at destruction? (default=false)
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline pre-allocated
        /// \until ...
        Vector(T* ptr, size_t n,bool handleDelete=false):Base(ptr,n,handleDelete) {}
        /// Destructor.
        /// Reference counted desctructor: frees memory if the object is the last one to use it.
        ~Vector() {}
        /// Assignment.
        /// Assigns from another vector (sharing its memory)
        /// \param v vector to be assigned to
        /// \return self reference
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline assignment 
        Vector& operator=(const Vector& v) { Base::operator=(v); return *this; }
        /// Cloning.
        /// Clones: creates a new vector, with fresh memory, copying values to it
        /// \return cloned vector
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline cloning (fresh memory)
        Vector clone() const
        {
            Vector v(this->size());
            equalize((int)this->size(),this->data(),1,v.data(),1);
            return v;
        }
        /// Filling.
        /// Fills with constant value
        /// \param x value to be copied to each element
        /// \return self reference
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline filling with constant value
        Vector& fill(T x) { Base::fill(x); return *this; }
        /// Zero vector.
        /// Vector with constant 0 value 
        /// \param n size
        /// \return vector
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline Vector with constant 0 value
        static Vector Zero(size_t n) {
            Vector Z(n);
            memset(Z.data(),0,n*sizeof(T));
            return Z;
        }
        /// Sub vector.
        /// Construct a sub vector, i.e. a new vector with fresh memory, initialized from a part of values of *this
        /// \param offset position of first element of sub vector
        /// \param size size of sub vector
        /// \return sub vector
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline sub vector
        Vector getSubVect(size_t offset, size_t size) const {
            return Vector(Base::getSubArray(offset,size));
        }
        /// Sub vector by reference.
        /// Construct a sub vector without allocating new memory but pointing to some part of *this. \b Beware: *this (or its memory) must not be
        /// destroyed as long as the returned subvectref is used!
        /// \param offset position of first element of sub vector
        /// \param size size of sub vector
        /// \return sub vector
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline sub vector ref (beware of restrictions!)
        Vector getSubVectRef(size_t offset, size_t size) {
            assert(offset+size<=this->size());
            return Vector(this->data()+offset,size);
        }
        /// Addition.
        /// Addition of two Vectors
        /// \param v Vector to be added to myself
        /// \return sum 
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline +
        Vector operator+(const Vector& v) const {
            assert(this->size()==v.size());
            Vector p=this->clone();
            return (p+=v);
        }
        /// In place Addition.
        /// In place Addition of Vectors
        /// \param v Vector to be added to myself
        /// \return self reference 
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline +=
        Vector& operator+=(const Vector& v) {
            assert(this->size()==v.size());
            combine((int)this->size(), 1, v.data(), this->data());
            return *this;
        }
        /// Substraction.
        /// Substraction of two Vectors
        /// \param v Vector to be substracted from myself
        /// \return difference 
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline -
        Vector operator-(const Vector& v) const {
            assert(this->size()==v.size());
            Vector p=this->clone();
            return (p-=v);
        }
        /// In place Substraction.
        /// In place Substraction of Vectors
        /// \param v Vector to be substracted from myself
        /// \return self reference 
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline -=
        Vector& operator-=(const Vector& v) {
            assert(this->size()==v.size());
            combine((int)this->size(), -1, v.data(), this->data());
            return *this;
        }
        /// Scalar Addition.
        /// Adds a scalar to each coordinate
        /// \param x Scalar to be added to myself
        /// \return sum
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline + scalar
        Vector operator+(T x) const {
            Vector p=this->clone();
            return (p+=x);
        }
        /// Scalar in place Addition.
        /// Adds a scalar to each own coordinate
        /// \param x Scalar to be added to myself
        /// \return self reference
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline += scalar
        Vector& operator+=(T x) {
            for (iterator it = this->begin() ; it != this->end() ; ++it)
                *it+=x;
            return *this;
        }
        /// Scalar Substraction.
        /// Substracts a scalar to each coordinate
        /// \param x Scalar to be substracted from myself
        /// \return difference
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline - scalar
        Vector operator-(T x) const {
            Vector p=this->clone();
            return (p-=x);
        }
        /// Scalar in place substractrion.
        /// Subtracts a scalar to each own coordinate
        /// \param x Scalar to be substracted from myself
        /// \return self reference
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline -= scalar
        Vector& operator-=(T x) {
            for (iterator it = this->begin() ; it != this->end() ; ++it)
                *it-=x;
            return *this;
        }
        /// Opposite.
        /// Opposite of a Vector
        /// \return Opposite
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline unary -
        Vector operator - () const {
            return (*this)*T(-1);
        }
        /// Scalar multiplication.
        /// Multiplies each coordinate by a scalar
        /// \param x The scalar
        /// \return Result
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline * scalar
        Vector operator*(T x) const {
            Vector p=this->clone();
            return (p*=x);
        }
        /// Scalar in place multiplication.
        /// Multiplies each coordinate by a scalar
        /// \param x The scalar
        /// \return self reference
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline *= scalar
        Vector& operator*=(T x) {
            multiply((int)this->size(), x, this->data());
            return *this;
        }
        /// Scalar division.
        /// Divides each coordinate by a scalar
        /// \param x The scalar
        /// \return Result
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline / scalar
        Vector operator/(T x) const {
            return (*this)*(1/x);
        }       
        /// Scalar in place division.
        /// Divides each coordinate by a scalar
        /// \param x The scalar
        /// \return self reference
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline /= scalar
        Vector& operator/=(T x) {
            (*this)*=(1/x);
            return *this;
        }
        /// Scalar multiplication.
        /// Multiplies each coordinate by a scalar
        /// \param x The scalar
        /// \param v The Vector
        /// \return The result
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline scalar * Vector
        friend inline Vector operator * (T x, const Vector& v) {return v*x;}
        /// Scalar addition.
        /// Adds a scalar to each coordinate
        /// \param x The scalar
        /// \param v The Vector
        /// \return The result
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline scalar + Vector
        friend inline Vector operator + (T x, const Vector& v) {return v+x;}
        /// Scalar substraction.
        /// Substract each coordinate to a scalar
        /// \param x The scalar
        /// \param v The Vector
        /// \return The result
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline scalar - Vector
        friend inline Vector operator - (T x, const Vector& v) {return (-v)+x;}
        /// Scalar product.
        /// Scalar product of Vectors
        /// \param v Vector to be combined with myself
        /// \return Scalar product
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline scalar product
        T operator*(const Vector& v) const {
            assert(this->size()==v.size());
            return scalarProduct((int)this->size(), this->data(), v.data());
        }
        /// Euclidean norm.
        /// Euclidean norm
        ///\param v argument
        /// \return squared Euclidean norm
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline Euclidean norm
        friend T norm(const Vector& v) {
            return squaredNorm((int) v.size(), v.data());
        }
        /// Squared Euclidean norm.
        /// Squared Euclidean norm. NB: obtained from Euclidean norm, thus it's not faster to use norm2() instead of norm() ...
        /// \param v argument
        /// \return squared Euclidean norm
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline squared Euclidean norm
        friend T norm2(const Vector& v) {
            return norm(v)*norm(v);
        }
        /// Euclidean in-place normalization.
        /// In-place normalization using Euclidean norm
        /// \return self reference
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline Euclidean in-place normalization
        Vector& normalize() {
            T n=norm(*this);
            if (n!=0) return operator /= (n);
            return *this;
        }
        /// Euclidean normalization.
        /// Normalization using Euclidean norm
        /// \param v Vector to normalize
        /// \return normalized vector
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline Euclidean normalization
        friend inline Vector normalized(const Vector& v) {
            T n=norm(v);
            assert(n!=0);
            return v/n;
        }
        /// Maximum norm.
        /// Maximum norm 
        /// \param v argument
        /// \return Maximum norm 
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline Maximum norm
        friend inline T maxNorm(const Vector& v) {
            if (v.empty()) return 0;
            const_iterator it = v.begin();
            T mx=std::abs(*it);
            for ( ++it ; it != v.end() ; ++it) {
                T a = std::abs(*it);
                if (a>mx)
                    mx=a;
            }
            return mx;
        }
        /// Sum of values.
        /// Sum of values
        /// \param v argument
        /// \return Result
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline sum of values
        friend inline T sum(const Vector& v) {
            return std::accumulate(v.begin(),v.end(),T(0));
        }
        /// Mean of values.
        /// Mean of values
        /// \param v argument
        /// \return Result
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline mean of values
        friend inline T mean(const Vector& v) {
            return sum(v)/v.size();
        }
        /// Convolution.
        /// Convolution. Returns a vector which size if sum of sizes minus 1
        /// \param K kernel
        /// \param v vector to convolution with K
        /// \return Result
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline Full convolution
        friend Vector convolution(const Vector& K,const Vector& v)  {
            if (v.size()<K.size()) return convolution(v,K);
            Vector p(K.size()+v.size()-1);
            p.fill(T(0));
            for (size_t i=0; i<v.size(); i++) {
                combine((int)K.size(), v[i], K.data(), p.data()+i);
            }
            return p;
        }
        /// Truncated Convolution.
        /// Truncated convolution. Returns a vector of the same size than v.
        /// \param K kernel
        /// \param v vector to convolution with K
        /// \param n shift
        /// \return Result
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline Truncated convolution
        friend Vector truncConvolution(const Vector& K,const Vector& v, size_t n=0)  {
            assert(n<K.size());
            Vector p(v.size());
            p.fill(T(0));
            for (size_t i=0; i<v.size(); i++) {
                int start = std::max((int)(0),(int)(n)-(int)(i));
                int end = std::min((int)(K.size()),(int)(v.size()+n)-(int)(i));
                combine((end - start), v[i], K.data()+start, p.data() + start + (i - n));
            }
            return p;
        }
        /// Correlation.
        /// Correlation between 2 vectors
        /// \param V1,V2 vectors
        /// \return correlation
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline correlation
        friend inline T correlation(const Vector& V1,const Vector& V2) {
            Vector v1=V1-mean(V1);
            Vector v2=V2-mean(V2);
            return v1*v2;
        }
        /// Normalized Correlation.
        /// Normalized Correlation between 2 vectors
        /// \param V1,V2 vectors
        /// \return correlation
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline normalized correlation
        friend inline T normalizedCorrelation(const Vector& V1,const Vector& V2) {// Non optimized version
            T c1=correlation(V1,V1);
            if (c1==0)
                return 0;
            T c2=correlation(V2,V2);
            if (c2==0)
                return 0;
            return correlation(V1,V2)/::sqrt(c1*c2);
        }   
        /// Distance.
        /// Distance Correlation between 2 vectors
        /// \param V1,V2 vectors
        /// \return distance
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip vectors()
        /// \skipline distance
        friend inline double dist(const Vector& V1,const Vector& V2) {
            double d=0;
            for (size_t i=0;i<V1.size();i++) {
                double e=double(V1[i])-double(V2[i]);
                d+=e*e;
            }
            return ::sqrt(d);
        }
    };


    ///@}
}
