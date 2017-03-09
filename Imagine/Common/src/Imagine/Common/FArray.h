// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

namespace Imagine {
    /// \addtogroup Common
    /// @{


    /// \headerfile Imagine/Common.h "Imagine/Common.h"
    /// %Array of fixed size.
    /// Fixed size arrays.
    /// \param T value type
    /// \param S array size
    template <typename T,int S> class FArray {

    protected:
        /// internal storage.
        T _data[S];

    public:
        /// Iterator type
        typedef T* iterator;
        /// Const iterator type
        typedef const T* const_iterator;

        /// Empty constructor.
        /// Constructs an uninitialized array of S variables of type T
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline uninitialized
        FArray(){}
        /// Constructor with constant value.
        /// Constructs an array of S variables of type T, each initialized to v
        /// \param v value used for initialization
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline filled with constant value
        explicit FArray(const T& v) {
            fill(v);
        }
        /// Constructor from C array.
        /// Constructs from a C array (with a possibly different type)
        /// \param t C array used for initialization
        /// \tparam T2 value type of t
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline filled from C array 
        /// \until copying
        template <typename T2> FArray(const T2 t[S]) {
            for (int i=0;i<S;i++) (*this)[i] = T(t[i]);
        }
        /// Copy constructor.
        /// Constructs from another FArray (with a possibly different type)
        /// \param a FArray to be copied (has to be of the same size)
        /// \tparam T2 value type of a
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline copy constructor
        /// \until FArray copy from different type
        template <typename T2> FArray(const FArray<T2,S>& a) {
            for (int i=0;i<S;i++) (*this)[i] = T(a[i]);
        }
        /// 2D alias.
        /// Short constructor for 2D FArray
        /// \param v0 value for index 0 component
        /// \param v1 value for index 1 component
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline alias for 2D case
        FArray(T v0, T v1) { 
            assert(S==2);
            (*this)[0]=v0; (*this)[1]=v1;
        }
        /// 3D alias.
        /// Short constructor for 3D FArray
        /// \param v0 value for index 0 component
        /// \param v1 value for index 1 component
        /// \param v2 value for index 2 component
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline alias for 3D case
        FArray(T v0, T v1, T v2) {
            assert(S==3);
            (*this)[0]=v0; (*this)[1]=v1; (*this)[2]=v2;
        }
        /// 4D alias.
        /// Short constructor for 4D FArray
        /// \param v0 value for index 0 component
        /// \param v1 value for index 1 component
        /// \param v2 value for index 2 component
        /// \param v3 value for index 3 component
        ///
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline alias for 4D case
        FArray(T v0, T v1, T v2, T v3) {
            assert(S==4);
            (*this)[0]=v0; (*this)[1]=v1; (*this)[2]=v2; (*this)[3]=v3;
        }
        /// Filling.
        /// Fills with constant value
        /// \param v value to be copied to each element
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline Fills with constant value
        FArray& fill(const T& v) {
            std::fill(begin(),end(),v);
            return *this;
        }
        /// C array of different type copy.
        /// Copies C array of different type
        /// \param t C array to be copied into FArray
        /// \tparam T2 value type of t
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline Copies C array of different type into FArray
        template <typename T2> FArray& copy(const T2 t[S]) {
            for (int i=0;i<S;i++) (*this)[i] = T(t[i]);
            return *this;
        }
        /// Copy.
        /// Copies another FArray of possibly different type but same size.
        /// \param b C array to be copied into FArray
        /// \tparam T2 value type of b
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline Copies C array of different type into FArray
        template <typename T2> FArray& copy(const FArray<T2,S>& b) {
            for (int i=0;i<S;i++) (*this)[i] = T(b[i]);
            return *this;
        }
        /// Assignment.
        /// Assigns from another FArray of possibly different type but same size
        /// \param b Source FArray
        /// \tparam T2 value type of b
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline assignment 
        /// \until FArray assignment from different type
        template <typename T2> FArray& operator = (const FArray<T2,S>& b) {
            return copy(b);
        }
        /// Is empty.
        /// True if FArray is empty
        /// \return false
        bool empty() const { return false; }
        /// Size.
        /// Dimension of FArray
        /// \return size
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline size
        int size() const { return S; }
        /// Read access.
        /// Reads i<sup>th</sup> element
        /// \param i element index (from 0 to S-1)
        /// \return const reference to i<sup>th</sup> element.
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline read access []
        const T& operator [] (int i) const {
            assert(i>=0 && i<S);
            return _data[i];
        }
        /// Write access.
        /// Writes i<sup>th</sup> element
        /// \param i element index (from 0 to S-1)
        /// \return Reference to i<sup>th</sup> element.
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline write access []
        T& operator [] (int i) {
            assert(i>=0 && i<S);
            return _data[i];
        }
        /// Data pointer (read).
        /// Pointer to data for reading
        /// \return const pointer to FArray elements
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline data pointer (read)
        const T* data() const { return _data; }
        /// Data pointer (write).
        /// Pointer to data for writing
        /// \return pointer to FArray elements
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline data pointer (write)
        T* data() { return _data; }
        /// Begin iterator.
        /// Begin iterator
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline Iterator
        /// \until ...
        iterator begin() { return _data; }
        /// Begin const iterator.
        /// Begin const iterator
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline const iterator
        /// \until ...
        const_iterator begin() const { return _data; }
        /// End iterator.
        /// End iterator
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline Iterator
        /// \until ...
        iterator end() { return _data+S; }
        /// End const iterator.
        /// End const iterator
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline const iterator
        /// \until ...
        const_iterator end() const { return _data+S; }
        /// Equality test.
        /// Equality test (component wise)
        /// \param b FArray for comparison
        /// \return true if *this equals b
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline ==
        bool operator == (const FArray& b) const {
            return std::equal(begin(),end(),b.begin());
        }
        /// Inequality test.
        /// Inequality test (component wise)
        /// \param b FArray for comparison
        /// \return true if *this is different from b
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline !=
        bool operator != (const FArray& b) const {
            return !(*this == b);
        }
        /// Range.
        /// Compute min and max of component values (provided comparisons are defined for type T)
        /// \param a inpu array
        /// \return pair of min,max values
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline range
        friend std::pair<T,T> range(const FArray& a)
        {   
            std::pair<T,T> r(a[0],a[0]);
            for (const_iterator it = a.begin()+1 ; it != a.end() ; ++it)
            {
                r.first = std::min(r.first, *it);
                r.second = std::max(r.second, *it);
            }
            return r;
        }
        /// Binary write.
        /// Writes FArray to binary stream
        /// \param out output stream
        /// \param a FArray to write
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline binary write
        /// \until ...
        friend inline void write(std::ostream& out,const FArray& a) {
            out.write((const char*)a._data,(std::streamsize)S*sizeof(T));
        }
        /// Binary read.
        /// Reads FArray from binary stream
        /// \param in input stream
        /// \param a FArray to read
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline binary read
        /// \until ...
        friend inline void read(std::istream& in, FArray& a) {
            in.read((char*)a._data,(std::streamsize)S*sizeof(T));
        }
        /// ASCII write.
        /// Writes FArray to stream
        /// \param out output stream
        /// \param a FArray to write
        /// \return updated stream
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline ASCII write
        /// \until ...
        friend inline std::ostream& operator<<(std::ostream& out,const FArray& a) {
            for (const_iterator it = a.begin() ; it != a.end() ; ++it)
                out<<*it<<' ';
            return out;
        }
        /// ASCII read.
        /// Reads FArray from stream
        /// \param in input stream
        /// \param a FArray to read
        /// \return updated stream
        /// 
        /// \dontinclude Common/test/test.cpp \skip fArrays()
        /// \skipline ASCII read
        /// \until ...
        friend inline std::istream& operator>>(std::istream& in, FArray& a) {
            for (iterator it = a.begin() ; it != a.end() ; ++it)
                in>>*it;
            return in;
        }
    };


    ///@}
}
