// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

namespace Imagine {
    /// \addtogroup LinAlg
    /// @{

    template <typename T> class Matrix;

    /// \headerfile Imagine/LinAlg.h "Imagine/LinAlg.h"
    /// Symmetric %Matrix of variable size.
    /// Symmetric %Matrix of variable size. Memory is reference counted, i.e.:
    /// - a=b results in a and b sharing the same memory
    /// - the last object using memory frees it when it dies
    /// - use clone() when this sharing is not desired
    ///
    /// \param T value type
    template <typename T>
    class SymMatrix : public Array<T> {
        typedef Array<T> Base;
        int _n;
        size_t sz(int n) { return size_t(n)*(n+1)/2; } 
    public:
        /// Iterator type
        typedef typename Base::iterator iterator;
        /// Const iterator type
        typedef typename Base::const_iterator const_iterator;
        /// Empty constructor.
        /// Constructs an unallocated symmetric matrix of variables of type T
        ///
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline non allocated
        SymMatrix() : Base(), _n(0) {}
        /// Constructor (known size).
        /// Constructs an allocated symmetric matrix of variables of type T
        /// \param N matrix size
        ///
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline allocated with specified size
        explicit SymMatrix(int N) : Base(sz(N)), _n(N) {}
        /// Copy constructor.
        /// Constructs a symmetric matrix from another one (sharing memory!)
        /// \param A matrix to copy
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline copy constructor
        SymMatrix(const SymMatrix& A) : Base(A), _n(A._n) {}
        /// Constructor (pre-allocated).
        /// Constructs an symmetric matrix from variables type T stored at an already allocated memory. t contains partial rows (0,0), (1,0), (1,1), (2,0), ...
        /// Does not allocate fresh memory. Does not free given memory at object destruction unless handleDelete=true. This memory must indeed stay available 
        /// during object life.
        /// \param t address of memory
        /// \param N matrix size
    /// \param handleDelete delete memory at destruction? (default=false)
            /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline pre-allocated
        /// \until ...
        SymMatrix(T* t, int N,bool handleDelete=false) : Base(t,sz(N),handleDelete), _n(N) {  }
        /// Conversion from Matrix.
        /// Constructs a symmetric matrix from a plain one, using upper part.
        /// \param A matrix to copy
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline conversion Matrix -> SymMatrix
        SymMatrix(const Matrix<T>& A) : Base(sz(A.nrow())), _n(A.nrow()) { // Upper part
            assert(A.nrow()==A.ncol());
            for (int j=0; j<A.nrow(); j++)
                equalize(j+1,A.data()+size_t(j)*A.nrow(),1,this->data()+sz(j),1);
        }
        /// Destructor.
        /// Reference counted desctructor: frees memory if the object is the last one to use it.
        ~SymMatrix() {}
        /// Assignment.
        /// Assigns from another symmetric matrix (sharing its memory)
        /// \param A symmetric to be assigned to
        /// \return self reference
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline assignment 
        SymMatrix& operator=(const SymMatrix& A) { Base::operator =(A); _n = A._n; return *this; }
        /// Cloning.
        /// Clones: creates a new symmetric matrix, with fresh memory, copying values to it
        /// \return cloned symmetric matrix
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline cloning (fresh memory)
        SymMatrix clone() const
        {
            SymMatrix A(nrow());
            equalize((int)this->size(),this->data(),1,A.data(),1);
            return A;
        }
        /// Change sizes.
        /// Resize symmetric matrix:
        /// - reallocates fresh memory
        /// - data is \b not copied from old to new memory
        /// - concerns only this object, not the ones that shared the old memory with it (and continue to use this old memory)
        /// - if the new size is the same as the old one, does nothing
        /// \param n new size
        ///
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline setSize
        void setSize(int n) {
            Base::setSize(sz(n));
            _n = n;
        }
        /// Number of rows.
        /// Number of rows
        /// \return Number of rows
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline numbers of rows and columns (both equal to specified size!)
        int nrow() const { return _n; }
        /// Number of columns.
        /// Number of columns
        /// \return Number of columns
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline numbers of rows and columns (both equal to specified size!)
        int ncol() const { return _n; }
        /// Filling.
        /// Fills with constant value
        /// \param x value to be copied to each element
        /// \return self reference
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline filling with constant value

        SymMatrix& fill(T x) { Base::fill(x); return *this; }
        /// Zero matrix.
        /// Matrix with constant 0 value
        /// \param n size
        /// \return matrix
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline Matrix with constant 0 value
        static SymMatrix Zero(int n){
            SymMatrix Z(n);
            memset(Z.data(),0,Z.size()*sizeof(T));
            return Z;
        }
        /// Identity.
        /// Identity
        /// \param n size
        /// \return matrix
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline Identity
        static SymMatrix Identity(int n){
            SymMatrix I=SymMatrix::Zero(n);
            for (int i=0;i<n;i++)
                I(i,i)=T(1);
            return I;
        }
        /// Read access.
        /// Reads element (i,j)
        /// \param i row index
        /// \param j column index
        /// \return const reference to element (i,j)
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline read access
        const T& operator()(int i,int j) const {
            assert(i>=0 && i<_n && j>=0 && j<_n);
            if(i<=j)
                return (*this)[i+size_t(j)*(j+1)/2];
            else
                return (*this)[j+size_t(i)*(i+1)/2];
        }
        /// Write access.
        /// Writes element (i,j)
        /// \param i row index
        /// \param j column index
        /// \return Reference to element (i,j)
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline write access
        T& operator()(int i,int j) {
            assert(i>=0 && i<_n && j>=0 && j<_n);
            if(i<=j)
                return (*this)[i+size_t(j)*(j+1)/2];
            else
                return (*this)[j+size_t(i)*(i+1)/2];
        }
        /// Get sub matrix.
        /// Constructs a new matrix a copies a part of *this into it.
        /// \param i0 starting row
        /// \param m number of rows
        /// \param j0 starting column
        /// \param n number of columns
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline Get sub matrix
        Matrix<T> getSubMat(int i0, int m, int j0, int n) const { 
            assert (i0>=0 && i0+m<=nrow() && j0>=0 && j0+n<=ncol());
            Matrix<T> retMat(m,n);
            for(int j=0;j<n;j++)
                for(int i=0;i<m;i++)
                    retMat(i,j)=(*this)(i0+i,j0+j);
            return retMat;
        }
        /// Get diagonal.
        /// Returns diagonal vector
        /// \return diagonal vector
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline Get diagonal
        Vector<T> getDiagonal() const {
            Vector<T> v(_n);
            for (int i=0;i<_n;i++)
                v[i]=(*this)(i,i);
            return v;
        }
        /// Product with vector.
        /// SymMatrix vector product
        /// \param v right operand
        /// \return (*this)* v
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline matrix * vector
        Vector<T> operator *(const Vector<T> &v) const {
            assert((size_t)_n==v.size());
            Vector<T> y(_n);
            y.fill(T(0));
            int _nn=_n;
            vectorProduct(_nn,T(1),this->data(),v.data(),T(0),y.data());
            return y;
        }
        /// Inverse.
        /// Inverse matrix. If non invertible, ouptuts a message to cerr and returns a matrix with zeroed elements.
        /// \param A argument
        /// \return Inverse
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline inverse
        /// \until ...
        friend SymMatrix inverse(const SymMatrix& A) {

            SymMatrix invA=A.clone();
            T *pivots=new T[A.nrow()*A.nrow()];
            int info,n=A.nrow();
            // LU Inverse

            symInverse(&n,invA.data(),pivots,&info);
      Matrix<T> inv(pivots,A.nrow(),A.nrow());
      SymMatrix<T> invA2(inv);
            delete[] pivots;
            if(info!=0) {
                std::cerr << "Cannot invert symmetric matrix" << std::endl;
                invA.fill(T(0));
                return invA;
            }
            return invA2;
        }
        /// Inverse (variant).
        /// Inverse matrix if positive-definite. If not the case invertible, ouptuts a message to cerr and returns a matrix with zeroed elements.
        /// \param A argument
        /// \return Inverse
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline positive-definite inverse
        /// \until ...
        friend SymMatrix posDefInverse(const SymMatrix& A) {

            SymMatrix invA=A.clone();
            T *pivots=new T[A.nrow()*A.nrow()];
            int info,n=A.nrow();
            // LU Inverse

            symDPInverse(&n,invA.data(),pivots,&info);
      Matrix<T> inv(pivots,A.nrow(),A.nrow());
      SymMatrix<T> invA2(inv);
            delete[] pivots;
            if(info!=0) {
                std::cerr << "Cannot invert symmetric matrix" << std::endl;
                invA.fill(T(0));
                return invA;
            }
            return invA2;
        }
        /// Determinant.
        /// Determinant.
        /// \param A argument
        /// \return determinant
        ///
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline Determinant
    /// remplacer le calcul du det par eigen? (plutot que bunch)
        friend T det(const SymMatrix& A) 
        {
            int info,n=A.nrow();
      SymMatrix symtemp = A.clone();
            T d =1;
      d = symDeterminant(&n,symtemp.data(),&info);
            if(info!=0) {
                std::cerr << "Cannot compute determinant" << std::endl;
                return 0;
            };
            return d;
        }
        /// Eigen values.
        /// Eigen values. Value Lambda[i] is associated with vector stored at
	/// i<sup>th</sup> column of Q.
        /// Thus Q is orthonormal and A=Q*diag(Lambda)*Q^T
        /// \param A argument
        /// \param Q Eigen vectors
        /// \param Lambda Eigen values in increasing order
        ///
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline Eigen values
        /// \until ...
        friend void EVD(const SymMatrix& A,Matrix<T>& Q, Vector<T>& Lambda) {
            SymMatrix symtemp = A.clone();
            Lambda = Vector<T>(A.nrow());
            Q = Matrix<T>(A.nrow(),A.nrow());
            int info,n=A.nrow();
            symEigenValues(&n,symtemp.data(),Lambda.data(),Q.data(),&info);
            if(info) {
                std::cerr << "Cannot compute EVD decomposition" << std::endl;
                return;
            }
        }
        /// Product.
        /// sym matrix * sym matrix product. NB: result is not symmetric!
        /// \param B right operand
        /// \return *this * B
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline symmatrix * symmatrix
        Matrix<T> operator *(const SymMatrix& B) const {
            // No blas function
            assert(ncol()==B.nrow());
            Matrix<T> C(nrow(),B.ncol());
            for (int j=0;j<B.ncol();j++) 
                for (int i=0;i<nrow();i++) {
                    C(i,j)=0;
                    for (int k=0;k<ncol();k++)
                        C(i,j)+=(*this)(i,k)*B(k,j);
                }
                return C;
        }
        /// Product.
        /// sym matrix * matrix product.
        /// \param B right operand
        /// \return *this * B
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline symmatrix * matrix
        Matrix<T> operator *(const Matrix<T>& B) const {
            // No blas function
            assert(ncol()==B.nrow());
            Matrix<T> C(nrow(),B.ncol());
            for (int j=0;j<B.ncol();j++) 
                for (int i=0;i<nrow();i++) {
                    C(i,j)=0;
                    for (int k=0;k<ncol();k++)
                        C(i,j)+=(*this)(i,k)*B(k,j);
                }
                return C;
        }
        /// Addition.
        /// Addition of two SymMatrix
        /// \param B Matrix to be added to myself
        /// \return sum 
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline +
        SymMatrix operator +(const SymMatrix& B) const {
            SymMatrix C=clone();
            return (C+=B);
        }
        /// In place Addition.
        /// In place Addition of SymMatrix
        /// \param B SymMatrix to be added to myself
        /// \return self reference 
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline +=
        SymMatrix& operator +=(const SymMatrix& B) {
            assert(nrow()==B.nrow());
            combine((int)this->size(), T(1), B.data(), this->data());
            return *this;
        }
        /// Substraction.
        /// Substraction of two SymMatrix
        /// \param B SymMatrix to be substracted from myself
        /// \return difference 
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline -
        SymMatrix operator -(const SymMatrix& B) const {
            SymMatrix C=clone();
            return (C-=B);
        }
        /// In place Substraction.
        /// In place Substraction of SymMatrix
        /// \param B SymMatrix to be substracted from myself
        /// \return self reference 
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline -=
        SymMatrix& operator -=(const SymMatrix& B) {
            assert(nrow()==B.nrow());
            combine((int)this->size(), T(-1), B.data(), this->data());
            return *this;
        }
        /// Opposite.
        /// Opposite of a SymMatrix
        /// \return Opposite
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline unary -
        SymMatrix operator - () const {
            return (*this)*T(-1);
        }
        /// Scalar multiplication.
        /// Multiplies each element by a scalar
        /// \param x The scalar
        /// \return Result
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline * scalar
        SymMatrix operator *(T x) const {
            SymMatrix C=clone();
            return (C*=x);
        }
        /// Scalar multiplication.
        /// Multiplies each element by a scalar
        /// \param x The scalar
        /// \param B The SymMatrix
        /// \return The result
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline scalar * SymMatrix
        friend inline SymMatrix operator *(T x, const SymMatrix& B) {return B*x;}
        /// Scalar division.
        /// Divides each element by a scalar
        /// \param x The scalar
        /// \return Result
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline / scalar
        SymMatrix operator /(T x) const {
            SymMatrix C=clone();
            return (C/=x);
        }
        /// Scalar in place multiplication.
        /// Multiplies each element by a scalar
        /// \param x The scalar
        /// \return self reference
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline *= scalar
        SymMatrix& operator *=(T x) {
            multiply((int)this->size(), x, this->data());
            return *this;
        }
        /// Scalar in place division.
        /// Divides each element by a scalar
        /// \param x The scalar
        /// \return self reference
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline /= scalar
        SymMatrix& operator /=(T x) {
            multiply((int)this->size(), T(1)/x, this->data());
            return *this;
        }
        /// Linear system.
        /// Solves symmetric system. Returns x such that Ax=b
        /// \param A argument
        /// \param b right term
        /// \return solution (zeroed vector if no solution)
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline Linear solve
        /// \until ...
        friend Vector<T> linSolve(const SymMatrix& A,const Vector<T>& b) 
        {
            assert(b.size()==(size_t)A.nrow());
            SymMatrix invA=A.clone();
            Vector<T> x=b.clone();
            // Bunch Kaufmann factorization
            int *pivots=new int[A.nrow()];
            int info,n=A.nrow();
            // Solve linear system using factorization
            symSolve(&n,invA.data(),pivots,x.data(),&info);
            if (info) {
                x.fill(T(0));
                std::cerr<<"Cannot solve linear system"<<std::endl;
            }
            delete[] pivots;
            return x;
        }
        /// Binary write.
        /// Writes SymMatrix to binary stream
        /// \param out output stream
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline binary write
        /// \until ...
        void write(std::ostream& out) const {
            int n=nrow();
            out.write((const char*)&n,sizeof(int));
            out.write((const char*)this->data(),(std::streamsize)this->size()*sizeof(T));
        }
        /// Binary read.
        /// Reads SymMatrix from binary stream
        /// \param in input stream
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline binary read
        /// \until ...
        void read(std::istream& in) {
            int n;
            in.read((char*)&n,sizeof(int));
            setSize(n);
            in.read((char*)this->data(),(std::streamsize)this->size()*sizeof(T));
        }
        /// ASCII write.
        /// Writes SymMatrix to stream
        /// \param out output stream
        /// \param A SymMatrix to write
        /// \return updated stream
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline ASCII write
        /// \until ...
        friend inline std::ostream& operator<<(std::ostream& out,const SymMatrix& A) {
            out<<A.nrow()<<" "<<A.ncol()<< std::endl;
            for (int i=0;i<A.nrow();i++) {
                for (int j=0;j<A.ncol();j++) {
                    out<<A(i,j);
                    if (j<A.ncol()-1) out<<" ";
                }
                out<<std::endl;
            }
            return out;
        }
        /// ASCII read.
        /// Reads SymMatrix from stream
        /// \param in input stream
        /// \param A SymMatrix to read
        /// \return updated stream
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline ASCII read
        /// \until ...
        friend inline std::istream& operator>>(std::istream& in,SymMatrix& A) {
            int m,n;
            in>>m>>n;
            assert(m==n);
            A.setSize(n);
            for (int i=0;i<A.nrow();i++)
                for (int j=0;j<A.ncol();j++)
                    in>>A(i,j);
            return in;
        }
    };

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    // Declaration in Matrix.h
    template <typename T> 
    Matrix<T>::Matrix(const SymMatrix<T>& A) : MultiArray<T,2>(A.nrow(),A.ncol()) {
        for (int j=0; j<ncol(); j++)
            for (int i=0; i<nrow(); i++)
                (*this)(i,j)=A(i,j);
    }
    // Declaration in Matrix.h
    template <typename T> 
    Matrix<T> Matrix<T>::operator *(const SymMatrix<T>& B) const
    {
        assert(ncol()==B.nrow());
        Matrix<T> C(nrow(),B.ncol());
        for (int j=0;j<B.ncol();j++) 
            for (int i=0;i<nrow();i++) {
                C(i,j)=0;
                for (int k=0;k<ncol();k++)
                    C(i,j)+=(*this)(i,k)*B(k,j);
            }
            return C;
    }
#endif

    ///@}
}
