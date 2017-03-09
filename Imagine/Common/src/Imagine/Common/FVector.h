// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

namespace Imagine {
    /// \addtogroup Common
    /// @{


    /// \headerfile Imagine/Common.h "Imagine/Common.h"
    /// %Vector of fixed size.
    /// Fixed size vectors.
    /// \param T value type
    /// \param dim size
    template <typename T,int dim> class FVector : public FArray<T,dim> {
        typedef FArray<T,dim> Base;
    public:
        /// Empty constructor.
        /// Constructs an uninitialized vector of dim variables of type T
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline uninitialized
        FVector(){}
        /// Constructor with constant value.
        /// Constructs a vector of dim variables of type T, each initialized to v
        /// \param v value used for initialization
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline filled with constant value
        explicit FVector(const T& v) : Base(v) {}
        /// Constructor from C array.
        /// Constructs from a C array (with a possibly different type)
        /// \param t C array used for initialization
        /// \tparam T2 value type of a
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline filled from C array 
        /// \until copying
        template <typename T2> FVector(const T2 t[dim]) : Base(t) {}
        /// Copy constructor.
        /// Constructs from another FArray (with a possibly different type)
        /// \param a FArray to be copied (has to be of the same size)
        /// \tparam T2 value type of a
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline copy constructor
        /// \until copy from different type
        template <typename T2> FVector(const FArray<T2,dim>& a) : Base(a) {}
        /// 2D alias.
        /// Short constructor for 2D FVector
        /// \param x value for index 0 coordinate
        /// \param y value for index 1 coordinate
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline alias for 2D case
        FVector(T x, T y) : Base(x,y) {}
        /// 3D alias.
        /// Short constructor for 3D FVector
        /// \param x value for index 0 coordinate
        /// \param y value for index 1 coordinate
        /// \param z value for index 2 coordinate
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline alias for 3D case
        FVector(T x, T y, T z) : Base(x,y,z) {}
        /// Filling.
        /// Fills with constant value
        /// \param v value to be copied to each element
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline Fills with constant value
        FVector& fill(const T& v) { Base::fill(v); return *this; }
        /// Zero vector
        /// Vector with constant 0 value
        /// \return vector
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline Vector with const 0 value
        static FVector Zero() {
            FVector Z;
            memset(Z._data,0,dim*sizeof(T));
            return Z;
        }
        /// Assignment.
        /// Assigns from another FVector (of possibly different type but same size)
        /// \param b Source FVector
        /// \tparam T2 value type of b
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline assignment 
        /// \until assignment from different type
        template <typename T2> 
        FVector& operator = (const FArray<T2,dim>& b) { Base::operator=(b); return *this; }
        /// Read alias.
        /// Alias to element of index 0
        /// \return Const reference to Element 0
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline read alias 0
        const T& x() const { assert(dim>=1); return (*this)[0]; }
        /// Write alias.
        /// Alias to element of index 0
        /// \return Reference to element 0
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline write alias 0
        T& x() { assert(dim>=1); return (*this)[0]; }
        /// Read alias.
        /// Alias to element of index 1
        /// \return Const reference to Element 1
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline read alias 1
        const T& y() const { assert(dim>=2); return (*this)[1]; }
        /// Write alias.
        /// Alias to element of index 1
        /// \return Reference to element 1
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline write alias 1
        T& y() { assert(dim>=2); return (*this)[1]; }
        /// Read alias.
        /// Alias to element of index 2
        /// \return Const reference to Element 2
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline read alias 2
        const T& z() const { assert(dim>=3); return (*this)[2]; }
        /// Write alias.
        /// Alias to element of index 2
        /// \return Reference to element 2
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline write alias 2
        T& z() { assert(dim>=3); return (*this)[2]; }
        /// Addition.
        /// Addition of two FVector
        /// \param v FVector to be added to myself
        /// \return sum 
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline +
        FVector operator + (const FVector& v) const {
            FVector w;
            for (int i=0;i<dim;i++)
                w[i]=(*this)[i]+v[i];
            return w;
        }
        /// Substraction.
        /// Substraction of two FVector
        /// \param v FVector to be substracted from myself
        /// \return difference 
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline -
        FVector operator - (const FVector& v) const {
            FVector w;
            for (int i=0;i<dim;i++)
                w[i]=(*this)[i]-v[i];
            return w;
        }
        /// In place Addition.
        /// In place Addition of FVector
        /// \param v FVector to be added to myself
        /// \return self reference 
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline +=
        FVector& operator += (const FVector& v) {
            for (int i=0;i<dim;i++)
                (*this)[i] += v[i];
            return *this;
        }
        /// In place Substraction.
        /// In place Substraction of FVector
        /// \param v FVector to be substracted from myself
        /// \return self reference 
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline -=
        FVector& operator -= (const FVector& v) {
            for (int i=0;i<dim;i++)
                (*this)[i] -= v[i];
            return *this;
        }
        /// Scalar Addition.
        /// Adds a scalar to each coordinate
        /// \param s Scalar to be added to myself
        /// \return sum
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline + scalar
        FVector operator + (T s) const {
            FVector w;
            for (int i=0;i<dim;i++)
                w[i]=(*this)[i]+s;
            return w;
        }
        /// Scalar Substraction.
        /// Substracts a scalar to each coordinate
        /// \param s Scalar to be substracted from myself
        /// \return difference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline - scalar
        FVector operator - (T s) const {
            FVector w;
            for (int i=0;i<dim;i++)
                w[i]=(*this)[i]-s;
            return w;
        }
        /// Scalar in place Addition.
        /// Adds a scalar to each own coordinate
        /// \param s Scalar to be added to myself
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline += scalar
        FVector& operator += (T s) {
            for (int i=0;i<dim;i++)
                (*this)[i] += s;
            return *this;
        }
        /// Scalar in place substractrion.
        /// Subtracts a scalar to each own coordinate
        /// \param s Scalar to be substracted from myself
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline -= scalar
        FVector& operator -= (T s) {
            for (int i=0;i<dim;i++)
                (*this)[i] -= s;
            return *this;
        }
        /// Opposite.
        /// Opposite of a FVector
        /// \return Opposite
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline unary -
        FVector operator - () const {
            FVector w;
            for (int i=0;i<dim;i++)
                w[i]=-(*this)[i];
            return w;
        }
        /// Scalar product.
        /// Scalar product of FVector
        /// \param v FVector to be combined with myself
        /// \return Scalar product
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline scalar product
        T operator * (const FVector& v) const {
            T s=0;
            for (int i=0;i<dim;i++)
                s+=(*this)[i]*v[i];
            return s;
        }
        /// 2D cross product.
        /// Scalar Cross product of 2D FVector (dim must be 2)
        /// \param v FVector to be combined with myself
        /// \return Cross product
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline 2D cross product
        T operator ^ (const FVector<T,2>& v) const {
            assert(dim==2);
            return (*this)[0]*v[1]-(*this)[1]*v[0];
        }
        /// 3D cross product.
        /// Vector Cross product of 3D FVector (dim must be 3)
        /// \param v FVector to be combined with myself
        /// \return Cross product
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline 3D cross product
        FVector<T,3> operator ^ (const FVector<T,3>& v) const {
            assert(dim==3);
            FVector<T,3> w;
            w[0]=(*this)[1]*v[2]-(*this)[2]*v[1];
            w[1]=(*this)[2]*v[0]-(*this)[0]*v[2];
            w[2]=(*this)[0]*v[1]-(*this)[1]*v[0];
            return w;
        }
        /// Scalar multiplication.
        /// Multiplies each coordinate by a scalar
        /// \param s The scalar
        /// \return Result
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline * scalar
        FVector operator*(T s) const {
            FVector v;
            for (int i=0;i<dim;i++)
                v[i]=(*this)[i]*s;
            return v;
        }
        /// Scalar division.
        /// Divides each coordinate by a scalar
        /// \param s The scalar
        /// \return Result
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline / scalar
        FVector operator/(T s) const {
            FVector v;
            for (int i=0;i<dim;i++)
                v[i]=(*this)[i]/s;
            return v;
        }
        /// Scalar in place multiplication.
        /// Multiplies each coordinate by a scalar
        /// \param s The scalar
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline *= scalar
        FVector& operator*=(T s) {
            for (int i=0;i<dim;i++)
                (*this)[i] *= s;
            return *this;
        }
        /// Scalar in place division.
        /// Divides each coordinate by a scalar
        /// \param s The scalar
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline /= scalar
        FVector& operator/=(T s) {
            for (int i=0;i<dim;i++)
                (*this)[i] /= s;
            return *this;
        }
        /// Scalar multiplication.
        /// Multiplies each coordinate by a scalar
        /// \param s The scalar
        /// \param v The FVector
        /// \return The result
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline scalar * FVector
        friend inline FVector operator*(T s,const FVector& v) {
            return v*s;
        }
        /// Scalar addition.
        /// Adds a scalar to each coordinate
        /// \param s The scalar
        /// \param v The FVector
        /// \return The result
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline scalar + FVector
        friend inline FVector operator+(T s,const FVector& v) {
            return v+s;
        }
        /// Scalar substraction.
        /// Substract each coordinate to a scalar
        /// \param s The scalar
        /// \param v The FVector
        /// \return The result
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline scalar - FVector
        friend inline FVector operator-(T s,const FVector& v) {
            return (-v)+s;
        }
        /// Squared Euclidean norm.
        /// Squared Euclidean norm (NB: assuming T type is OK)
        /// \param v argument
        /// \return squared Euclidean norm
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline squared Euclidean norm
        friend inline T norm2(const FVector& v) {
            T n=0;
            for (int i=0;i<dim;i++)
                n+=v[i]*v[i];
            return n;
        }
        /// Euclidean norm.
        /// Euclidean norm (NB: assuming T type is OK)
        /// \param v argument
        /// \return Euclidean norm
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline Euclidean norm
        friend inline T norm(const FVector& v) {
            assert( !std::numeric_limits<T>::is_integer );
            return ::sqrt(norm2(v));
        }
        /// Euclidean in-place normalization.
        /// In-place normalization using Euclidean norm
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline Euclidean in-place normalization
        FVector& normalize() {
            T n=norm(*this);
            if (n!=0) return operator /= (n);
            return *this;
        }
        /// Euclidean normalization.
        /// Normalization using Euclidean norm
        /// \param v FVector to normalize
        /// \return normalized vector
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline Euclidean normalization
        friend inline FVector normalized(const FVector& v) {
            T n=norm(v);
            assert(n!=0);
            return v/n;
        }
        /// Maximum norm.
        /// Maximum norm 
        /// \param v argument
        /// \return Maximum norm 
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline Maximum norm
        friend inline T maxNorm(const FVector& v) {
            T mx = std::abs(v[0]);
            for (int i=0;i<dim;i++){
                T a = std::abs(v[i]);
                if (a>mx) mx = a;
            }
            return mx;
        }
        /// Integer L1-norm.
        /// Integer L1-Euclidean norm ((to avoid overflow for vectors of char or short ints)
        /// \param v argument
        /// \return Integer L1-norm.
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline integer L1-norm
        friend inline int intNorm1(const FVector & v)
        {
            assert( std::numeric_limits<T>::is_integer );
            int n = 0;
            for(int i=0; i < dim; ++i)
                n+= abs(v[i]);
            return n;
        }
        /// Integer squared Euclidean norm.
        /// Integer squared Euclidean norm ((to avoid overflow for vectors of char or short ints)
        /// \param v argument
        /// \return Integer squared Euclidean norm
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline integer squared Euclidean norm
        friend inline int intNorm2(const FVector& v) {
            assert( std::numeric_limits<T>::is_integer );
            int n=0;
            for (int i=0;i<dim;i++)
                n+=int(v[i])*int(v[i]);
            return n;
        }
        /// Double L1-norm.
        /// Double L1-norm
        /// \param v argument
        /// \return Double L1-norm
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline double L1-norm
        friend inline double doubleNorm1(const FVector& v) {
            double d=0;
            for (int i=0;i<dim;++i)
                d+=fabs(double(v[i]));
            return d;
        }
        /// Double squared Euclidean norm.
        /// Double squared Euclidean norm
        /// \param v argument
        /// \return Double squared Euclidean norm
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline double squared Euclidean norm
        friend inline double doubleNorm2(const FVector& v) {
            double n=0;
            for (int i=0;i<dim;i++)
                n+=double(v[i])*double(v[i]);
            return n;
        }
        /// Double Euclidean norm.
        /// Double Euclidean norm
        /// \param v argument
        /// \return Double Euclidean norm
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline double Euclidean norm
        friend inline double doubleNorm(const FVector& v) {
            return ::sqrt(doubleNorm2(v));
        }
        /// Sum of coordinates.
        /// Sum of coordinates (beware of overflow)
        /// \param v argument
        /// \return Result
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline sum of coordinates
        friend inline T sum(const FVector& v) {
            T n=0;
            for (int i=0;i<dim;i++)
                n+=v[i];
            return n;
        }
        /// Pointwise multiplication.
        /// Multiplies coordinates two by two
        /// \param v,w FVector 
        /// \return v*w
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline pointwise *
        friend inline FVector mult(const FVector &v, const FVector& w) {
            FVector r;
            for (int i=0;i<dim;i++)
                r[i]=v[i]*w[i];
            return r;
        }
        /// Pointwise division.
        /// Divides coordinates two by two
        /// \param v,w FVector 
        /// \return v/w
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline pointwise /
        friend inline FVector div(const FVector &v, const FVector& w) { 
            FVector r;
            for (int i=0;i<dim;i++)
                r[i]=v[i]/w[i];
            return r;
        }
        /// Pointwise square root 
        /// Square roots of each coordinate
        /// \param a FVector 
        /// \return Result
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline pointwise sqrt
        friend inline FVector sqrt(const FVector& a) {
            assert( !std::numeric_limits<T>::is_integer );
            FVector v;
            for (int i=0;i<dim;i++)
                v[i]=::sqrt(a._data[i]);
            return v;
        }
        /// Pointwise log 
        /// logs of each coordinate
        /// \param a FVector 
        /// \return Result
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline pointwise log
        friend inline FVector log(const FVector& a) {
            assert( !std::numeric_limits<T>::is_integer );
            FVector v;
            for (int i=0;i<dim;i++)
                v[i]=::log(a._data[i]);
            return v;
        }
        /// Pointwise exp 
        /// exps of each coordinate
        /// \param a FVector 
        /// \return Result
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline pointwise exp
        friend inline FVector exp(const FVector& a) {
            assert( !std::numeric_limits<T>::is_integer );
            FVector v;
            for (int i=0;i<dim;i++)
                v[i]=::exp(a._data[i]);
            return v;
        }
        /// Pointwise min.
        /// Min of each coordinate
        /// \param a,b FVector 
        /// \return Result
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline pointwise min
        friend inline FVector pmin(const FVector& a, const FVector& b) {
            FVector m;
            for (int i=0;i<dim;++i)
                m[i]=std::min(a[i],b[i]);
            return m;
        }
        /// Pointwise max.
        /// Max of each coordinate
        /// \param a,b FVector 
        /// \return Result
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline pointwise max
        friend inline FVector pmax(const FVector& a, const FVector& b) {
            FVector m;
            for (int i=0;i<dim;++i)
                m[i]=std::max(a[i],b[i]);
            return m;
        }
        /// Integer L1-distance.
        /// Integer L1-distance between two vectors with integer coordinates
        /// \param a,b FVector 
        /// \return Result
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline L1-distance
        friend inline int intL1Dist(const FVector &a, const FVector& b) {
            assert( std::numeric_limits<T>::is_integer );
            int n=0;
            for (int i = 0; i<dim; ++i)
                n += abs(int(a[i])-int(b[i]));
            return n;
        }
        /// Double L1-distance.
        /// Double L1-distance between two vectors, regardless of their type
        /// \param a,b FVector 
        /// \return Result
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline L1-distance
        friend inline double L1Dist(const FVector &a, const FVector& b) {
            double d=0;
            for (int i = 0; i < dim; ++i)
                d += fabs(double(a[i])-double(b[i]));
            return d;
        }
        /// Squared distance.
        /// Squared distance between two vectors, whatever their type
        /// \param a,b FVector 
        /// \return Result
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline squared distance
        friend inline double squaredDist(const FVector &a, const FVector& b) {
            double d=0;
            for (int i=0;i<dim;i++) {
                double e=double(a[i])-double(b[i]);
                d+=e*e;
            }
            return d;
        }
        /// Distance.
        /// Distance between two vectors, whatever their type
        /// \param a,b FVector 
        /// \return Result
        /// 
        /// \dontinclude Common/test/test.cpp \skip fVectors()
        /// \skipline distance
        friend inline double dist(const FVector&a, const FVector& b) {
            return std::sqrt( squaredDist(a,b) );
        }
    };


    ///@}
}
