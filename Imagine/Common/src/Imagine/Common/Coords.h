// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

namespace Imagine {
    /// \addtogroup Common
    /// @{


    /// \headerfile Imagine/Common.h "Imagine/Common.h"
    /// Coordinates.
    /// Coordinates used by MultiArray
    /// \param dim dimension
    template <int dim> class Coords : public FVector<int,dim> {
    private: 
        typedef FVector<int,dim> Base;
    public:
        /// Empty constructor.
        /// Constructs an uninitialized Coords
        /// 
        /// \dontinclude Common/test/test.cpp \skip coords()
        /// \skipline uninitialized
        Coords() : Base() {}
        /// Copy constructor
        /// Constructs from anit Coords
        /// \param v Coords to be copied 
        /// 
        /// \dontinclude Common/test/test.cpp \skip coords()
        /// \skipline copy constructor
        Coords(const Base& v) :  Base(v) {}
        /// Constructor from C array.
        /// Constructs a Coords and copies values to it
        /// \param v C array used for initialization
        /// 
        /// \dontinclude Common/test/test.cpp \skip coords()
        /// \skipline filled from C array 
        /// \until copying
        Coords(const int v[dim]): Base(v) {}
        /// Constructor with constant value.
        /// Constructs a Coords and sets each coordinate to v
        /// \param v value used for initialization
        /// 
        /// \dontinclude Common/test/test.cpp \skip coords()
        /// \skipline filled with constant value
        Coords(int v) : Base(v) {}
        /// 2D alias.
        /// Short constructor for 2D Coords
        /// \param x value for index 0 coordinate
        /// \param y value for index 1 coordinate
        /// 
        /// \dontinclude Common/test/test.cpp \skip coords()
        /// \skipline alias for 2D case
        Coords(int x,int y) : Base(x,y) {}
        /// 3D alias.
        /// Short constructor for 3D Coords
        /// \param x value for index 0 coordinate
        /// \param y value for index 1 coordinate
        /// \param z value for index 2 coordinate
        /// 
        /// \dontinclude Common/test/test.cpp \skip coords()
        /// \skipline alias for 3D case
        Coords(int x,int y,int z) : Base(x,y,z) {}
        /// Product of coordinates.
        /// Product of coordinates (note: result is of type size_t)
        /// \return Result
        /// 
        /// \dontinclude Common/test/test.cpp \skip coords()
        /// \skipline product of coordinates
        size_t prod() const {
            size_t p=1;
            for (int i=0;i<dim;i++)
                p*=(*this)[i];
            return p;
        }
    };

    /// \headerfile Imagine/Common.h "Imagine/Common.h"
    /// Iterator on Coordinates.
    /// Iterator on Coords. Iterates over rectangular region. Used to iterate over a MultiArray while being aware of coordinates.
    /// \param dim dimension
    template <int dim> class CoordsIterator : public std::iterator<std::input_iterator_tag, Coords<dim> > {
    protected:
        /// begin
        Coords<dim> _a;
        /// end
        Coords<dim> _b;
        /// Current position
        Coords<dim> _pos;
        /// end reached?
        bool _stop;
    public:
        /// Empty constructor.
        /// Constructs a stopped iterator, useful to check end of iteration
        /// with \c operator!=.
        /// 
        /// \dontinclude Common/test/test.cpp \skip coords()
        /// \skipline uninitialized iterator
        CoordsIterator() : _stop(true) {}
        /// Constructor.
        /// Constructs an iterator over a rectangular region from a to b
        /// \param a,b limits of rectangular region 
        /// 
        /// \dontinclude Common/test/test.cpp \skip coords()
        /// \skipline iterator for 1<=x<=5, 1<=y<=3
        CoordsIterator(const Coords<dim>& a, const Coords<dim>& b) : _a(a), _b(b), _pos(a), _stop(false) {}
        /// Assignment.
        /// Assigns from another CoordsIterator
        /// \param it source iterator
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip coords()
        /// \skipline iterator assignment 
        CoordsIterator& operator = (const CoordsIterator& it) {
            _a = it._a;
            _b = it._b;
            _pos = it._pos;
            _stop = it._stop;
            return *this;
        }   
        /// Equality test.
        /// Equality test 
        /// \param it iterator for comparision
        /// \return true if 
        /// - both are stopped
        /// - or both are non stopped and at same position
        /// 
        /// \dontinclude Common/test/test.cpp \skip coords()
        /// \skipline ==
        bool operator == (const CoordsIterator& it) const {
            return (_stop ? it._stop : !it._stop && _pos == it._pos);
        }
        /// Inequality test.
        /// Inequality test 
        /// \param it iterator for comparision
        /// \return true if operator==() is false
        /// 
        /// \dontinclude Common/test/test.cpp \skip coords()
        /// \skipline !=
        bool operator != (const CoordsIterator& it) const {
            return (_stop ? !it._stop : it._stop || _pos != it._pos);
        }
        /// Pre-increment.
        /// Pre-increment: advance to next position. Becomes stopped if end is reached
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip coords()
        /// \skipline pre ++
        /// \until dereference
        CoordsIterator& operator ++ () {
            for (int i=0;i<dim;i++) {
                if (_pos[i]!=_b[i]) {
                    _pos[i]++;
                    return *this;
                }
                _pos[i]=_a[i];
            }
            _stop = true;
            return *this;
        }
        /// Post-increment.
        /// Post-increment: advance to next position. Becomes stopped if end is reached
        /// \return value before increment
        /// 
        /// \dontinclude Common/test/test.cpp \skip coords()
        /// \skipline post ++ and member selection
        /// \until ...
        CoordsIterator operator ++(int) {
            CoordsIterator tmp(*this);
            ++(*this);
            return tmp;
        }
        /// Dereference.
        /// Dereference: coordinate position
        /// \return position
        /// 
        /// \dontinclude Common/test/test.cpp \skip coords()
        /// \skipline pre ++
        /// \until dereference
        Coords<dim> operator * () const {
            return _pos;
        }
        /// Member selection.
        /// Member selection: pointer to coordinate position
        /// \return pointer to position
        /// 
        /// \dontinclude Common/test/test.cpp \skip coords()
        /// \skipline post ++ and member selection
        /// \until ...
        const Coords<dim>* operator -> () const {
            return &_pos;
        }
    };


    ///@}
}
