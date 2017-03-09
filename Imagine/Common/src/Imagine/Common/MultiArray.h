// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

namespace Imagine {
    /// \addtogroup Common
    /// @{


    /// \headerfile Imagine/Common.h "Imagine/Common.h"
    /// nD array of variable size.
    /// nD array of variable size. Memory is reference counted, i.e.:
    /// - a=b results in a and b sharing the same memory
    /// - the last object using memory frees it when it dies
    /// - use clone() when this sharing is not desired
    ///
    /// \param T value type
    /// \param dim dimension    
    template <typename T, int dim> class MultiArray : public Array<T> {

    private:
        // Based on Array
        typedef Array<T> Base;
        Coords<dim> _sz;                    // Sizes of the array.
        FArray<size_t,dim> _stride;     // Strides to navigate to neighbors in each dimension
        // Set size and compute stride
        void setSizes(const Coords<dim>& sz)
        {
            _sz=sz;
            _stride[0] = 1;
            for (int i=0;i<dim-1;i++) {
                _stride[i+1] = _stride[i]*_sz[i];
            }
        }
        //  Set size and stride from another MultiArray
        template <typename Y> void setSizes(const MultiArray<Y,dim>& A)
        {
            _sz=A.sizes();  _stride=A.stride();
        }

    public:
        /// Iterator type
        typedef T* iterator;
        /// Const iterator type
        typedef const T* const_iterator;


        /// Empty constructor.
        /// Constructs an unallocated array of variables of type T and dimension dim
        ///
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline non allocated
        MultiArray() : Base() { _sz = 0; }
        /// Constructor (known size).
        /// Constructs an allocated array of variables of type T and dimension dim. sz[i] specifies size for dimension i.
        /// \param sz array sizes
        ///
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline allocated with specified size
        explicit MultiArray(const Coords<dim>& sz) : Base(sz.prod()) { setSizes(sz); }
        /// Constructor (2D shorcut).
        /// Constructs an allocated array of variables of type T, dimension 2 and specified size
        /// \param s0 array size for dimension 0
        /// \param s1 array size for dimension 1
        ///
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline constructor, 2D alias
        MultiArray(int s0,int s1) : Base(size_t(s0)*s1) { assert(dim==2); setSizes(Coords<2>(s0,s1)); }
        /// Constructor (3D shorcut).
        /// Constructs an allocated array of variables of type T, dimension 3 and specified size
        /// \param s0 array size for dimension 0
        /// \param s1 array size for dimension 1
        /// \param s2 array size for dimension 2
        ///
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline constructor, 3D alias
        MultiArray(int s0,int s1, int s2) : Base(size_t(s0)*s1*s2) { assert(dim==3); setSizes(Coords<3>(s0,s1,s2)); }
        /// Constructor (pre-allocated).
        /// Constructs an array of variables of type T and dimension dim, stored at an already allocated memory. ptr contains elements (0,0,...), (1,0,...), ...
        /// Does not allocate fresh memory. Does not free given memory at object destruction unless handleDelete=true. This memory must indeed stay available 
        /// during object life.
        /// \param ptr address of memory
        /// \param sz array sizes
        /// \param handleDelete delete memory at destruction? (default=false)
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline pre-allocated
        /// \until ...
        MultiArray(T* ptr, const Coords<dim>& sz,bool handleDelete=false) : Base(ptr,sz.prod(),handleDelete) { setSizes(sz); }
        /// Constructor (pre-allocated) 2D alias.
        /// Constructs an array of variables of type T and dimension 2, stored at an already allocated memory. ptr contains elements (0,0), (1,0), ...
        /// Does not allocate fresh memory. Does not free given memory at object destruction unless handleDelete=true. This memory must indeed stay available 
        /// during object life.
        /// \param ptr address of memory
        /// \param s0 array size for dimension 0
        /// \param s1 array size for dimension 1
        /// \param handleDelete delete memory at destruction? (default=false)
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline pre-allocated, 2D alias
        MultiArray(T* ptr, int s0,int s1,bool handleDelete=false) : Base(ptr,size_t(s0)*s1,handleDelete) { assert(dim==2); setSizes(Coords<2>(s0,s1)); }
        /// Constructor (pre-allocated) 3D alias.
        /// Constructs an array of variables of type T and dimension 3, stored at an already allocated memory. ptr contains elements (0,0,0), (1,0,0), ...
        /// Does not allocate fresh memory. Does not free given memory at object destruction unless handleDelete=true. This memory must indeed stay available 
        /// during object life.
        /// \param ptr address of memory
        /// \param s0 array size for dimension 0
        /// \param s1 array size for dimension 1
        /// \param s2 array size for dimension 2
        /// \param handleDelete delete memory at destruction? (default=false)
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline pre-allocated, 3D alias
        MultiArray(T* ptr, int s0,int s1,int s2,bool handleDelete=false) : Base(ptr,size_t(s0)*s1*s2,handleDelete) { assert(dim==3); setSizes(Coords<3>(s0,s1,s2)); }
        /// Copy constructor.
        /// Constructs an nD array from another one (sharing memory!)
        /// \param A nD array to copy
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline copy constructor
        explicit MultiArray(const MultiArray& A) : Base(A) { setSizes(A); }
        /// Constructor (different type).
        /// Constructs an nD array of type T from one of another type (thus without sharing memory!)
        /// \param A nD array to copy
        /// \tparam T2 type of A
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline from different type
        template <typename T2> 
        MultiArray(const MultiArray<T2,dim>& A) : Base(A) { setSizes(A); }
        /// Destructor.
        /// Reference counted desctructor: frees memory if the object is the last one to use it.
        virtual ~MultiArray() {}
        /// Change sizes.
        /// Resize nD array:
        /// - reallocates fresh memory
        /// - data is \b not copied from old to new memory
        /// - concerns only this object, not the ones that shared the old memory with it (and continue to use this old memory)
        /// - if the new size is the same as the old one, does nothing
        /// \param sz array sizes
        ///
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline setSize
        void setSize(const Coords<dim>& sz) {
            if (sz==_sz) return;
            Base::setSize(sz.prod());
            setSizes(sz);
        }
        /// Change size 2D alias.
        /// Resize 2D array. 2D alias.
        /// \param s0 array size for dimension 0
        /// \param s1 array size for dimension 1
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline setSize, 2D alias
        void setSize(int s0, int s1) { setSize(Coords<2>(s0,s1)); }
        /// Change size 3D alias.
        /// Resize 3D array. 3D alias.
        /// \param s0 array size for dimension 0
        /// \param s1 array size for dimension 1
        /// \param s2 array size for dimension 2
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline setSize, 3D alias
        void setSize(int s0, int s1, int s2) { setSize(Coords<3>(s0,s1,s2)); }
        /// Assignment.
        /// Assigns from another nD Array (sharing its memory)
        /// \param A array to be assigned to
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline assignment 
        MultiArray& operator=(const MultiArray& A) { Base::operator =(A); setSizes(A); return *this; }
        /// Assignment (different type).
        /// Assign from an array of another type (thus without sharing memory!)
        /// \param A array to copy
        /// \tparam T2 type of A
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline different type assignment
        template <typename T2> MultiArray& operator= (const MultiArray<T2,dim>& A) { Base::operator = (A); setSizes(A); return *this; }
        /// Cloning.
        /// Clones: creates a new nD array, with fresh memory, copying values to it
        /// \return cloned array
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline cloning (fresh memory)
        MultiArray clone() const {
            if (this->empty()) return MultiArray();
            MultiArray A(_sz);
            std::copy( this->begin(), this->end(), A.begin() );
            return A;
        }
        /// Filling.
        /// Fills with constant value
        /// \param x value to be copied to each element
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline filling with constant value
        MultiArray& fill(T x) { Base::fill(x); return *this; }
        /// Sizes.
        /// Sizes of nD Array. 
        /// \return sizes
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline sizes
        Coords<dim> sizes() const { return _sz; }
        /// Total Size.
        /// Number of elements
        /// \return total size
        ///
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline number of elements
        size_t totalSize() const { return Array<T>::size(); }
        /// i<sup>th</sup> size.
        /// Size of nD Array along dimension i. 
        /// \return i<sup>th</sup> size
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline i<sup>th</sup> size
        int size(int i) const { assert(i>=0 && i<dim); return _sz[i]; }
        /// Size alias 0.
        /// Size of nD Array along dimension 0. 
        /// \return width
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline Size. alias 0
        int width() const { assert(dim>=1); return _sz[0]; }
        /// Size alias 1.
        /// Size of nD Array along dimension 1.
        /// \return height
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline Size. alias 1
        int height() const { assert(dim>=2); return _sz[1]; }
        /// Size alias 2.
        /// Size of nD Array along dimension 2. 
        /// \return depth
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline Size. alias 2
        int depth() const { assert(dim>=3); return _sz[2]; }
        /// Stride.
        /// Stride of nD Array (stride(i) gives the distance to next element along dimension i)
        /// \return stride
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline stride
        FArray<size_t,dim> stride() const { return _stride; }
        /// i<sup>th</sup> stride.
        /// i<sup>th</sup> stride of nD Array (distance to element along dimension i)
        /// \return i<sup>th</sup> stride
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline i<sup>th</sup> stride
        size_t stride(int i) const { assert(i>=0 && i<dim); return _stride[i]; }
        /// Sub array.
        /// Construct a sub array, i.e. a new array with fresh memory, initialized from a part of values of *this
        /// \param offset coordinates of first element of sub array
        /// \param sz sizes of sub array
        /// \return sub array
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline sub array
        MultiArray getSubArray(const Coords<dim>& offset, const Coords<dim>& sz) const {
            MultiArray A(sz);
            for (CoordsIterator<dim> p = A.coordsBegin() ; p != A.coordsEnd() ; ++p) {
                A(*p)=operator()(*p+offset);
            }
            return A;
        }
        /// Offset.
        /// Offset (i.e. index of coordinates in the underlying Array) given coordinates
        /// \param c coordinates in the MultiArray domain
        /// \return offset
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline offset
        size_t offset(const Coords<dim>& c) const {
            size_t o = c[dim-1];
            assert(o<size_t(_sz[dim-1]));
            for (int d=dim-2;d>=0;d--) {
                assert(c[d]>=0 && c[d]<_sz[d]);
                o=o*_sz[d]+c[d];
            }
            return o;
        }
        /// Offset (2D alias).
        /// Offset (2D alias)
        /// \param x,y coordinates
        /// \return offset
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline offset 2D alias
        size_t offset(int x, int y) const {
            assert(dim==2);
            return x+(size_t)_sz[0]*y;
        }
        /// Offset (3D alias).
        /// Offset (3D alias)
        /// \param x,y,z coordinates
        /// \return offset
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline offset 3D alias
        size_t offset(int x, int y, int z) const {
            assert(dim==3);
            return x+_sz[0]*(y+(size_t)_sz[1]*z);
        }
        /// Read access.
        /// Reads element at coordinates c
        /// \param c coordinates
        /// \return Const reference to element.
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline read access ()
        const T& operator() (const Coords<dim>& c) const {
            return (*this)[offset(c)];
        }
        /// Write access.
        /// Writes element at coordinates c
        /// \param c coordinates
        /// \return Reference to element.
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline write access ()
        T& operator() (const Coords<dim>& c) { return (*this)[offset(c)]; }
        /// Read access 2D alias.
        /// Read access 2D alias
        /// \param x,y coordinates
        /// \return Const reference to element.
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline read access 2D alias
        const T& operator()(int x, int y) const { return (*this)[offset(x,y)]; }
        /// Write access 2D alias.
        /// Write access 2D alias
        /// \param x,y coordinates
        /// \return Reference to element.
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline write access 2D alias
        T& operator()(int x, int y) { return (*this)[offset(x,y)]; }
        /// Read access 3D alias.
        /// Read access 3D alias
        /// \param x,y,z coordinates
        /// \return Const reference to element.
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline read access 3D alias
        const T& operator()(int x, int y, int z) const { return (*this)[offset(x,y,z)]; } 
        /// Write access 3D alias.
        /// Write access 3D alias
        /// \param x,y,z coordinates
        /// \return Reference to element.
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline write access 3D alias
        T& operator()(int x, int y, int z) { return (*this)[offset(x,y,z)]; }
        /// Begin coords iterator.
        /// Coordinates iterator over the array domain. Use this to iterates over an nD array if coordinates are needed (otherwise, use a standard Array::iterator)
        /// \return begin iterator
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline coords iterator
        /// \until ...
        CoordsIterator<dim> coordsBegin() const { return CoordsIterator<dim>( Coords<dim>(0), _sz -Coords<dim>(1) ); }
        /// End coords iterator.
        /// Coordinates iterator over the array domain. Use this to iterates over an nD array if coordinates are needed (otherwise, use a standard Array::iterator)
        /// \return end iterator
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline coords iterator
        /// \until ...
        CoordsIterator<dim> coordsEnd() const { return CoordsIterator<dim>(); }
        /// Binary write.
        /// Writes Array to binary stream (size and values)
        /// \param out output stream
        /// \param A MultiArray to write
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline binary write
        /// \until ...
        friend void write(std::ostream& out,const MultiArray& A) {
            write(out,A._sz);
            out.write((const char*)A.data(),A.totalSize()*sizeof(T));
        }
        /// Binary read.
        /// Reads and allocates Array from binary stream (providing size and values)
        /// \param in input stream
        /// \param A MultiArray to read
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline binary read
        /// \until ...

        friend void read(std::istream& in,MultiArray& A) {
            Coords<dim> sz;
            read(in,sz);
            A.setSize(sz);
            in.read((char*)A.data(),A.totalSize()*sizeof(T));
        }
        /// ASCII write.
        /// Writes Array to stream (size and values)
        /// \param out output stream
        /// \param A MultiArray to write
        /// \return updated stream
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline ASCII write
        /// \until ...
        friend inline std::ostream& operator<<(std::ostream& out,const MultiArray& A) {
            out<<A.sizes()<<" ";
            for (size_t i=0;i<A.totalSize();i++) {
                out<<A[i];
                if (i<A.totalSize()-1) out<<" ";
            }
            return out;
        }
        /// ASCII read.
        /// Reads and allocates Array from stream (providing size and values)
        /// \param in input stream
        /// \param A MultiArray to read
        /// \return updated stream
        /// 
        /// \dontinclude Common/test/test.cpp \skip multiArrays()
        /// \skipline ASCII read
        /// \until ...
        friend inline std::istream& operator>>(std::istream& in,MultiArray& A) {
            Coords<dim> sz;
            in>>sz;
            A.setSize(sz);
            for (size_t i=0;i<A.totalSize();i++) 
                in>>A[i];
            return in;
        }
    };


    ///@}
}
