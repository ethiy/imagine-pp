// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

namespace Imagine {
    /// \addtogroup Common
    /// @{


    /// \headerfile Imagine/Common.h "Imagine/Common.h"
    /// %Array of variable size.
    /// %Array of variable size. Memory is reference counted, i.e.:
    /// - a=b results in a and b sharing the same memory
    /// - the last object using memory frees it when it dies
    /// - use clone() when this sharing is not desired
    ///
    /// \param T value type 
    template <typename T> class Array {
    private:
        int* _count;    // pointer to reference counter
        T *_data;       // pointer to data
        size_t _size;   // size of array
        // Allocates memory
        void alloc(size_t size,T* ptr=0,bool handleDelete=false) 
        {
            _size=size;
            if (!ptr) {
                if (size > 0)
                {
                    _data= new T[size];
                    _count=new int(1);
                }
                else
                {
                    _data = 0;
                    _count = 0;
                }
            }
            else {
                _data=ptr;
                _count= (handleDelete? new int(1): 0);
            }
        }
        // Frees memory unless reference counter indicates other users
        void kill()
        {
            if (!_count)
                return;
            (*_count)--;
            if (!(*_count)) {
                delete _count;
                delete[] _data;
                _data = 0;
                _count = 0;
                _size = 0;
            }
        }
        // Declares myself as a new user
        void copy(const Array& A)
        {
            _count=A._count;
            _data=A._data;
            _size=A._size;
            if(_count)
                (*_count)++;
        }
    public:
        /// Iterator type
        typedef T* iterator;
        /// Const iterator type
        typedef const T* const_iterator;

        /// Empty constructor.
        /// Constructs an unallocated array of variables of type T
        ///
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline non allocated
        Array(): _count(0), _data(0), _size(0) {}
        /// Constructor (known size).
        /// Constructs an allocated array of size variables of type T
        /// \param size array size
        ///
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline allocated with specified size
        explicit Array(size_t size) { alloc(size); }
        /// Constructor (pre-allocated).
        /// Constructs an array pointing to variables of type T stored at an already allocated memory. Does not allocate fresh memory.
        /// This memory must indeed stay available during object life.
        /// Does not free given memory at object destruction unless handleDelete=true. 
        /// \param ptr address of memory
        /// \param size array size
        /// \param handleDelete delete memory at destruction? (default=false)
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline pre-allocated
        /// \until ...
        Array(T* ptr, size_t size,bool handleDelete=false) { alloc(size,ptr,handleDelete); }
        /// Copy constructor.
        /// Constructs an array from another one (sharing memory!)
        /// \param A array to copy
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline copy constructor
        explicit Array(const Array& A) { copy(A); }
        /// Constructor (different type).
        /// Constructs an array of type T from one of another type (thus without sharing memory!)
        /// \param A array to copy
        /// \tparam T2 type of A
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline from different type
        template <typename T2> Array(const Array<T2>& A) {
            alloc(A.size());
            for (size_t i=0;i<A.size();i++) _data[i] = T(A[i]) ;
        }
        /// Constructor (from list).
        /// Constructs an array of variables of type T from a list.
        /// \param L the list
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline from list
        /// \until ...
        Array(const std::list<T>& L) {
            alloc(L.size());
            size_t i=0;
            for (typename std::list<T>::const_iterator it=L.begin();it!=L.end();++it,++i)
                (*this)[i]= *it;
        }
        /// Destructor.
        /// Reference counted desctructor: frees memory if the object is the last one to use it.
        virtual ~Array() { kill(); }
        /// Change size.
        /// Change array size:
        /// - (re)allocates fresh memory
        /// - <b>data is not copied from old to new memory</b>
        /// - <b>concerns only this object, not the ones that shared the old memory with it (and continue to use the old memory)</b>
        /// - <b>if the new size is the same as the old one, does nothing</b>
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline setSize
        void setSize(size_t size) {
            if (size==_size) return;
            kill(); alloc(size);
        }
        /// Assignment.
        /// Assigns from another Array (sharing its memory)
        /// \param A array to be assigned to
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline assignment 
        Array& operator = (const Array& A) { kill(); copy(A); return *this; }
        /// Assignment (different type).
        /// Assign from an array of another type (thus without sharing memory!)
        /// \param A array to copy
        /// \tparam T2 type of A
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline different type assignment
        template <typename T2> Array& operator = (const Array<T2>& A) {
            kill();
            alloc(A.size());
            for (size_t i=0;i<A.size();i++) _data[i] = T( A[i] );
            return *this;
        }
        /// Cloning.
        /// Clones: creates a new array, with fresh memory, copying values to it
        /// \return cloned array
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline cloning (fresh memory)
        Array clone() const {
            Array A(_size);
            std::copy( begin(), end(), A.begin() );
            return A;
        }
        /// Is empty.
        /// True if array is not allocated
        /// \return emptyness
        ///
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline is empty?
        /// \until ...
        bool empty() const { return (_size==0); }
        /// Size.
        /// Number of elements
        /// \return size
        ///
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline number of elements
        size_t size() const { return _size; }
        /// Read access.
        /// Reads i<sup>th</sup> element
        /// \param i element index (from 0 to size-1)
        /// \return Const reference to i<sup>th</sup> element.
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline read access []
        const T& operator[](size_t i) const { assert(i<_size);return _data[i]; }
        /// Write access.
        /// Writes i<sup>th</sup> element
        /// \param i element index (from 0 to size-1)
        /// \return Reference to i<sup>th</sup> element.
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline write access []
        T& operator[](size_t i) { assert(i<_size); return _data[i];  }
        /// Data pointer (read/write).
        /// Pointer to data for reading and writing
        /// \return pointer to array elements
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline data pointer (write)
        T* data() { return _data; }
        /// Data pointer (read).
        /// Pointer to data for reading only
        /// \return const pointer to elements
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline data pointer (read)
        const T* data() const { return _data; }
        /// Begin iterator.
        /// Begin iterator
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline Iterator
        /// \until ...
        iterator begin() { return _data; }
        /// Begin const iterator.
        /// Begin const iterator
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline const iterator
        /// \until ...
        const_iterator begin() const { return _data; }
        /// End iterator.
        /// End iterator
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline Iterator
        /// \until ...
        iterator end() { return _data+_size; }
        /// End const iterator.
        /// End const iterator
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline const iterator
        /// \until ...
        const_iterator end() const { return _data+_size; }
        /// Sub array.
        /// Construct a sub array, i.e. a <b>new array with fresh memory, initialized from a part of values of *this</b>
        /// \param offset position of first element of sub array
        /// \param size size of sub array
        /// \return sub array
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline sub array
        
        Array getSubArray(size_t offset, size_t size) const {
            Array A(size);
            for (size_t i=0;i<A.size();i++) {
                A[i] = (*this)[i+offset];
            }
            return A;
        }
        /// Filling.
        /// Fills with constant value
        /// \param x value to be copied to each element
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline filling with constant value
        Array& fill(const T& x) {
            std::fill(begin(),end(),x);
            return *this;
        }
        /// Equality test.
        /// Equality test, component wise, i.e. if arrays are of the same size and with the same values
        /// \param A array for comparison
        /// \return true if *this equals A
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline ==
        bool operator == (const Array& A) const {
            if (A.size() != size()) return false;
            for (size_t i=0;i<size();i++)
                if (!(_data[i] == A[i]))
                    return false;
            return true;
        }
        /// Inequality test.
        /// Inequality test (component wise)
        /// \param A array for comparison
        /// \return true if *this is different from b
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline !=
        bool operator != (const Array& A) const {
            return !(*this == A);
        }
        /// Range.
        /// Compute min and max of component values (provided comparisons are defined for type T)
        /// \param A input array
        /// \return pair of min,max values
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline range
        /// \until ...
        friend std::pair<T,T> range(const Array& A) {   
            const_iterator it = A.begin();
            std::pair<T,T> r(*it,*it);
            for ( ++it; it != A.end() ; ++it) {
                r.first=std::min(r.first,*it);
                r.second=std::max(r.second,*it);
            }
            return r;
        }
        /// Pointwise range.
        /// Compute pointwise min and pointwise max of component values (provided pointwise comparisons are defined for type T, e.g. FVector)
        /// \param A input array
        /// \return pair of pmin, pmax values
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline pointwise range
        /// \until ...
        friend std::pair<T,T> prange(const Array& A) {  
            const_iterator it = A.begin();
            std::pair<T,T> r(*it,*it);
            for ( ++it; it != A.end() ; ++it) {
                r.first=pmin(r.first,*it);
                r.second=pmax(r.second,*it);
            }
            return r;
        }
        /// Binary write.
        /// Writes Array to binary stream (size and values)
        /// \param out output stream
        /// \param A Array to write
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline binary write
        /// \until ...
        friend void write(std::ostream& out,const Array& A) {
            size_t n = A._size;
            out.write((const char*)&n,sizeof(size_t));
            out.write((const char*)A._data,(std::streamsize)A._size*sizeof(T));
        }
        /// Binary read.
        /// Reads and allocates Array from binary stream (providing size and values)
        /// \param in input stream
        /// \param A Array to read
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline binary read
        /// \until ...
        friend void read(std::istream& in,Array& A) {
            size_t n;
            in.read((char*)&n,sizeof(size_t));
            A.setSize(n);
            in.read((char*)A._data,(std::streamsize)A._size*sizeof(T));
        }
        /// ASCII write.
        /// Writes Array to stream (size and values)
        /// \param out output stream
        /// \param A Array to write
        /// \return updated stream
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline ASCII write
        /// \until ...
        friend inline std::ostream& operator<<(std::ostream& out,const Array& A) {
            out<<A.size()<<" ";
            for (size_t i=0;i<A.size();i++) {
                out<<A[i];
                if (i<A.size()-1) out<<" ";
            }
            return out;
        }
        /// ASCII read.
        /// Reads and allocates Array from stream (providing size and values)
        /// \param in input stream
        /// \param A Array to read
        /// \return updated stream
        /// 
        /// \dontinclude Common/test/test.cpp \skip arrays()
        /// \skipline ASCII read
        /// \until ...
        friend inline std::istream& operator>>(std::istream& in,Array& A) {
            size_t n;
            in>>n;
            A.setSize(n);
            for (size_t i=0;i<A.size();i++) 
                in>>A[i];
            return in;
        }
    };


    ///@}
}
