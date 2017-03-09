 // ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================


namespace Imagine {
    /// \addtogroup LinAlg
    /// @{

    template<typename T> class SymMatrix;

    /// \headerfile Imagine/LinAlg.h "Imagine/LinAlg.h"
    /// %Matrix of variable size.
    /// %Matrix of variable size. Memory is reference counted, i.e.:
    /// - a=b results in a and b sharing the same memory
    /// - the last object using memory frees it when it dies
    /// - use clone() when this sharing is not desired
    ///
    /// \param T value type
    template <typename T>
    class Matrix : public MultiArray<T,2> {
        typedef MultiArray<T,2> Base;
    public:
        /// Iterator type
        typedef typename Base::iterator iterator;
        /// Const iterator type
        typedef typename Base::const_iterator const_iterator;

        /// Empty constructor.
        /// Constructs an unallocated matrix of variables of type T
        ///
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline non allocated
        Matrix() : Base() {}
        /// Constructor (known size).
        /// Constructs an allocated matrix of variables of type T
        /// \param M number of rows
        /// \param N number of columns
        ///
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline allocated with specified size
        Matrix(int M,int N) : Base(M,N) {}
        /// Constructor (pre-allocated).
        /// Constructs an MxN matrix from variables type T stored at an already allocated memory. t contains (0,0), (1,0), ...
        /// Does not allocate fresh memory. Does not free given memory at object destruction unless handleDelete=true. This memory must indeed stay available 
        /// during object life.
        /// \param t address of memory
        /// \param M number of rows
        /// \param N number of columns
        /// \param handleDelete delete memory at destruction? (default=false)
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline pre-allocated
        /// \until ...
        Matrix(T* t,int M,int N,bool handleDelete=false) : Base(t,M,N,handleDelete) {}
        /// Copy constructor.
        /// Constructs a matrix from another one (sharing memory!)
        /// \param A matrix to copy
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline copy constructor
        Matrix(const Base& A) : Base(A) {}
        /// Conversion from SymMatrix.
        /// Constructs a matrix from a symmetric one
        /// \param A matrix to copy
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline conversion SymMatrix -> Matrix
        Matrix(const SymMatrix<T>& A);
        /// Destructor.
        /// Reference counted desctructor: frees memory if the object is the last one to use it.
        ~Matrix() {}
        /// Assignment.
        /// Assigns from another matrix (sharing its memory)
        /// \param A matrix to be assigned to
        /// \return self reference
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline assignment 
        Matrix& operator=(const Matrix& A) { Base::operator=(A); return *this; }
        /// Cloning.
        /// Clones: creates a new matrix, with fresh memory, copying values
        /// \return cloned matrix
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline cloning (fresh memory)
        Matrix clone() const
        {
            Matrix A(nrow(),ncol());
            equalize((int)this->totalSize(),this->data(),1,A.data(),1);
            return A;
        }
        /// Number of rows.
        /// Number of rows
        /// \return Number of rows
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline Dimensions
        int nrow() const { return this->width(); }
        /// Number of columns.
        /// Number of columns
        /// \return Number of columns
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline Dimensions
        int ncol() const { return this->height(); }
        /// Filling.
        /// Fills with constant value
        /// \param x value to be copied to each element
        /// \return self reference
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline filling with constant value
        Matrix& fill(T x) { Base::fill(x); return *this; }
        /// Zero matrix.
        /// Matrix with constant 0 value 
        /// \param M,N dimensions
        /// \return matrix
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline Matrix with constant 0 value
        static Matrix Zero(int M,int N){
            Matrix Z(M,N);
            memset(Z.data(),0,Z.totalSize()*sizeof(T));
            return Z;
        }
        /// Identity.
        /// Identity
        /// \param N dimension (NxN matrix)
        /// \return matrix
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline Identity
        static Matrix Identity(int N){
            Matrix I=Matrix::Zero(N,N);
            for (int i=0;i<N;i++)
                I(i,i)=T(1);
            return I;
        }
        /// Get column.
        /// Returns column of index j
        /// \param j column index
        /// \return column vector
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline Get column
        Vector<T> getCol(int j) const {
            assert(j>=0 && j<ncol());
            Vector<T> v(nrow());
            equalize(nrow(),this->data()+nrow()*j,1,v.data(),1);
            return v;
        }
        /// Get row.
        /// Returns row of index i
        /// \param i row index
        /// \return row vector
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline Get row
        Vector<T> getRow(int i) const {
            assert(i>=0 && i<nrow());
            Vector<T> v(ncol());
            equalize(ncol(),this->data()+i,nrow(),v.data(),1);
            return v;
        }
        /// Get diagonal.
        /// Returns diagonal vector of size=min(nrow,ncol)
        /// \return diagonal vector
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline Get diagonal
        Vector<T> getDiagonal() const {
            int n=std::min(nrow(),ncol());
            Vector<T> v(n);
            for (int i=0;i<n;i++)
                v[i]=(*this)(i,i);
            return v;
        }
        /// Set column.
        /// Sets column of index j
        /// \param j column index
        /// \param v column
        /// \return self reference
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline Set column
        Matrix& setCol(int j, const Vector<T>& v) {
            assert(v.size()==(size_t)nrow() && j>=0 && j<ncol());
            equalize(nrow(),v.data(),1,this->data()+nrow()*j,1);
            return *this;
        }
        /// Set row.
        /// Sets row of index i
        /// \param i row index
        /// \param v row
        /// \return self reference
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline Set row
        Matrix& setRow(int i, const Vector<T>& v) {
            assert(v.size()==(size_t)ncol() && i>=0 && i<nrow());
            equalize(ncol(),v.data(),1,this->data()+i,nrow());
            return *this;
        }
        /// Set diagonal.
        /// Set diagonal from vector of size=min(nrow,ncol)
        /// \param v diagonal
        /// \return self reference
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline Set diagonal
        Matrix& setDiagonal(const Vector<T>& v) {
            int n=int(v.size());
            assert(n==std::min(nrow(),ncol()));
            for (int i=0;i<n;i++)
                (*this)(i,i)=v[i];
            return *this;
        }
        /// Get column by reference.
        /// Construct a vector without allocating new memory but pointing to a column of *this. \b Beware: *this (or its memory) must not be
        /// destroyed as long as the returned vector is used!
        /// \param j column index
        /// \return column
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline Vector pointing to column (beware of restrictions!)
        Vector<T> getColRef(int j) {
            assert (j>=0 && j<ncol());
            return Vector<T>(this->data()+(size_t)nrow()*j,nrow());
        }
        /// Get sub column by reference.
        /// Construct a vector without allocating new memory but pointing to part of a column of *this. \b Beware: *this (or its memory) must not be
        /// destroyed as long as the returned vector is used!
        /// \param j column index
        /// \param i0 starting row
        /// \param m number of rows
        /// \return column
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline Vector pointing to sub-column (beware of restrictions!)
        Vector<T> getSubColRef(int j, int i0, int m) {
            assert (j>=0 && j<ncol() && i0>=0 && m>=0 && i0+m<=nrow());
            return Vector<T>(this->data()+i0+(size_t)+nrow()*j,m);
        }
        /// Get sub matrix.
        /// Constructs a new matrix a copies a part of *this into it.
        /// \param i0 starting row
        /// \param m number of rows
        /// \param j0 starting column
        /// \param n number of columns
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline Get sub matrix
        Matrix getSubMat(int i0, int m, int j0, int n) const { 
            assert (i0>=0 && i0+m<=nrow() && j0>=0 && j0+n<=ncol());
            Matrix retMat(m,n);
            for(int j=0;j<n;j++)
                equalize(m,this->data()+(j+j0)*nrow()+i0, 1, retMat.data()+j*m, 1);
            return retMat;
        }
        /// Get part of columns by reference.
        /// Construct a matrix without allocating new memory but pointing to part of columns of *this. \b Beware: *this (or its memory) must not be
        /// destroyed as long as the returned vector is used!
        /// \param j0 starting column index
        /// \param n number of columns
        /// \return columns
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline Matrix pointing to part of columns (beware of restrictions!)
        Matrix getColsRef(int j0,int n) {
            assert (j0>=0 && n>=0 && j0+n<=ncol());
            return Matrix(this->data()+(size_t)nrow()*j0, nrow(), n);
        }
        /// Product with vector.
        /// Matrix vector product
        /// \param v right operand
        /// \return (*this)* v
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline matrix * vector
        Vector<T> operator *(const Vector<T>& v) const {
            assert((size_t)ncol()==v.size());
            Vector<T> y(nrow());
            y.fill(T(0));
            affinity(nrow(), ncol(), T(1), this->data(), v.data(), T(0), y.data(), '0');
            return y;
        }
        /// Product with vector.
        /// Matrix vector product (variant)
        /// \param A left operand
        /// \param v right operand
        /// \return transpose(A)* v
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline matrix^T * vector
        friend Vector<T> tmult(const Matrix& A,const Vector<T>& v) {
            assert((size_t)A.nrow()==v.size());
            Vector<T> y(A.ncol());
            y.fill(T(0));
            affinity(A.nrow(), A.ncol(), T(1), A.data(), v.data(), T(0), y.data(), 'T');
            return y;
        }
        /// Transpose.
        /// Transposed matrix
        /// \param A argument
        /// \return Transposed matrix
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline transpose
        friend Matrix transpose(const Matrix& A) {
            Matrix r(A.ncol(),A.nrow());
            for(int i=0;i<A.nrow();i++) for(int j=0;j<A.ncol();j++) r(j,i)=A(i,j);
            return r;
        }
        /// Inverse.
        /// Inverse matrix. If non invertible, outputs a message to cerr and returns a matrix with zeroed elements.
        /// \param A matrix to inverse
        /// \return the inverse matrix
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline inverse
        friend Matrix inverse(const Matrix& A) {
            assert(A.nrow()==A.ncol());
            Matrix invA=A.clone();
            int *pivots=new int[A.nrow()];
            int info,n=A.ncol();
            // LU Inverse
            matrixInverse(&n,invA.data(),&n,pivots,&info);
            if (info) {
                std::cerr<<"Cannot invert matrix"<<std::endl;
                invA.fill(T(0));
                delete [] pivots;
                return invA;
            }
            delete[] pivots;
            return invA;
        }
        /// Product.
        /// Matrix matrix product
        /// \param B right operand
        /// \return *this * B
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline matrix * matrix
        Matrix operator *(const Matrix& B) const {
            assert(ncol()==B.nrow());
            int p=ncol();
            Matrix C(nrow(),B.ncol());
            C.fill(T(0));
            matrixProduct(C.nrow(),C.ncol(),p,T(1),this->data(),nrow(),B.data(),B.nrow(),T(0),C.data(), 'N', 'N');
            return C;
        }
        /// Product.
        /// Matrix matrix product (variant)
        /// \param A left operand
        /// \param B right operand
        /// \return transpose(A) * B
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline matrix^T * matrix
        friend Matrix tmult(const Matrix& A,const Matrix& B)  {
            assert(A.nrow()==B.nrow());
            int p=A.nrow();
            Matrix C(A.ncol(),B.ncol());
            C.fill(T(0));
            matrixProduct(C.nrow(),C.ncol(),p,T(1),A.data(),A.nrow(),B.data(),B.nrow(),T(0),C.data(),'T','N');
            return C;
        }
        /// Product.
        /// Matrix matrix product (variant)
        /// \param A left operand
        /// \param B right operand
        /// \return A * transpose(B)
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline matrix * matrix^T
        friend Matrix multt(const Matrix& A,const Matrix& B)  {
            assert(A.ncol()==B.ncol());
            int p=A.ncol();
            Matrix C(A.nrow(),B.nrow());
            C.fill(T(0));
            matrixProduct(C.nrow(),C.ncol(),p,T(1),A.data(),A.nrow(),B.data(),B.nrow(),T(0),C.data(),'N','T');
            return C;
        }
        /// Product.
        /// Matrix matrix product (variant)
        /// \param A left operand
        /// \param B right operand
        /// \return transpose(A) * transpose(B)
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline matrix^T * matrix^T
        friend Matrix tmultt(const Matrix& A,const Matrix& B)  {
            assert(A.nrow()==B.ncol());
            int p=A.nrow();
            Matrix C(A.ncol(),B.nrow());
            C.fill(T(0));
            matrixProduct(C.nrow(),C.ncol(),p,T(1),A.data(),A.nrow(),B.data(),B.nrow(),T(0),C.data(),'T','T');
            return C;
        }
        /// Product.
        /// Matrix symmatrix product
        /// \param B right operand
        /// \return *this * B
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip symMatrices()
        /// \skipline matrix * symmatrix
        Matrix operator *(const SymMatrix<T>& B) const;
        /// Addition.
        /// Addition of two Matrix
        /// \param B Matrix to be added to myself
        /// \return sum 
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline +
        Matrix operator +(const Matrix& B) const {
            Matrix C=clone();
            return (C+=B);
        }
        /// Substraction.
        /// Substraction of two Matrix
        /// \param B Matrix to be substracted from myself
        /// \return difference 
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline -
        Matrix operator -(const Matrix& B) const {
            Matrix C=clone();
            return (C-=B);
        }
        /// In place Addition.
        /// In place Addition of Matrix
        /// \param B Matrix to be added to myself
        /// \return self reference 
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline +=
        Matrix& operator +=(const Matrix& B) {
            assert(ncol()==B.ncol());
            assert(nrow()==B.nrow());
            combine((int)this->totalSize(), 1, B.data(), this->data());
            return *this;
        }
        /// In place Substraction.
        /// In place Substraction of Matrix
        /// \param B Matrix to be substracted from myself
        /// \return self reference 
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline -=
        Matrix& operator -=(const Matrix& B) {
            assert(ncol()==B.ncol());
            assert(nrow()==B.nrow());
            combine((int)this->totalSize(), -1, B.data(), this->data());
            return *this;
        }
        /// Opposite.
        /// Opposite of a matrix
        /// \return Opposite
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline unary -
        Matrix operator - () const {
            return (*this)*T(-1);
        }
        /// Scalar multiplication.
        /// Multiplies each element by a scalar
        /// \param x The scalar
        /// \return Result
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline * scalar
        Matrix operator *(T x) const {
            Matrix C=clone();
            return (C*=x);
        }
        /// Scalar division.
        /// Divides each element by a scalar
        /// \param x The scalar
        /// \return Result
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline / scalar
        Matrix operator /(T x) const {
            Matrix C=clone();
            return (C/=x);
        }
        /// Scalar in place multiplication.
        /// Multiplies each element by a scalar
        /// \param x The scalar
        /// \return self reference
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline *= scalar
        Matrix& operator *=(T x) {
            multiply((int)this->totalSize(), x, this->data());
            return *this;
        }
        /// Scalar in place division.
        /// Divides each element by a scalar
        /// \param x The scalar
        /// \return self reference
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline /= scalar
        Matrix& operator /=(T x) {
            multiply((int)this->totalSize(), 1 / x, this->data());
            return *this;
        }
        /// Scalar multiplication.
        /// Multiplies each element by a scalar
        /// \param x The scalar
        /// \param B The Matrix
        /// \return The result
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline scalar * Matrix
        friend inline Matrix operator *(T x, const Matrix& B) {return B*x;}
        /// Scalar product.
        /// Scalar product (L^2)
        /// \param a left term
        /// \param b right term
        /// \return scalar product
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline scalar product
        friend T dot(const Matrix& a,const Matrix& b) {
            assert(a.nrow()==b.nrow() && a.ncol()==b.ncol());
            return scalarProduct((int)a.totalSize(), a.data(), b.data());
        }
        /// Norm.
        /// Matrix norms. 
        /// \param A argument
        /// \param type norm choice:
        /// - 'F' (default): frobenius (sqrt of sum of squares)
        /// - '1': 1-norm (max column sum)
        /// - 'I': infinity-norm (max row sum)
        /// - 'M': max-norm (largest abs value)
        /// \return norm
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline frobenius norm
        /// \until ...
        friend T norm(const Matrix& A,char type='F') {
            int nr=A.nrow(),nc=A.ncol();
            T n = matrixNorm(&type,&nr,&nc,(T*)A.data(),&nr);
            return n;
        }
        /// Reciprocal condition number.
        /// Reciprocal condition number in the 1-norm
        /// \param A argument
        /// \return condition number
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline reciprocal condition number
        friend T rcond(const Matrix& A) 
        {   
            if (A.nrow()<A.ncol())
                return rcond(transpose(A));
            // QR decomposition
            Matrix tmpA=A.clone();
            int info,m=A.nrow(),n=A.ncol();
            // Estimation of condition number
            T rcond;
            conditionNumber(&n,tmpA.data(),&m,&rcond,&info);
            if (info!=0) {
                std::cerr << "Bad cond number " << std::endl;
                rcond = T(-1);
            }
            return rcond;
        }
        /// SVD.
        /// Singular value decomposition. A is MxN. S is of size min(M,N) with decreasing singular values. A=U*diag(S)*Vt where U (resp. Vt) is
        /// MxM (resp NxN) orthonormal, diag(S) is MxN with S as diagonal. If M<N (resp. M>N) then Vt (resp. U) is incompletely filled, expect all is true.
        /// \param A matrix
        /// \param U,S,Vt SVD output
        /// \param all complete U and V is true
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline Singular value decomposition
        /// \until ...
        friend void svd(const Matrix& A,Matrix &U,Vector<T> &S, Matrix &Vt,bool all=false) {
            Matrix cpy=A.clone();
            U=Matrix(A.nrow(),A.nrow());
            Vt=Matrix(A.ncol(),A.ncol());
            S=Vector<T>(std::min(A.nrow(),A.ncol()));
            int nr=A.nrow(),nc=A.ncol();
            int info;
            singularValuesDecomposition(all?"A":"S",&nr,&nc,cpy.data(),S.data(),U.data(),Vt.data(),&info);
            if (info) {
                std::cerr<<"Cannot compute SVD"<<std::endl;
                return;
            }
        }
        /// Linear system.
        /// Solve linear system. Returns x such that:
        /// - M=N, square system: Ax=b
        /// - M>N, over determined system: x=argmin_y|Ay-b|
        /// - M<N, under determined system: x=argmin_{y,Ay=b}|y|
        ///
        /// \param A matrix
        /// \param b right term
        /// \return solution (zeroed vector if no solution)
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline Linear solve
        /// \until ...
        friend Vector<T> linSolve(const Matrix& A,const Vector<T>& b)
        {
            assert(b.size() == (size_t)A.nrow());
            if(A.nrow()==A.ncol())
            {
                // Linear system is not over- or under- determined
                Matrix tmpA=A.clone();
                Vector<T> tmpb=b.clone();
                // LU factorization
                int *pivots=new int[A.nrow()];
                int info,n=A.nrow();
                LUSystemSolve(&n,tmpA.data(),pivots,tmpb.data(),&info);
                if (info) {
          std::cerr<<"Cannot solve linear system"<<std::endl;
                    tmpb.fill(T(0));
                    delete [] pivots;
                    return tmpb;
                    tmpb.fill(T(0));
                    std::cerr<<"Cannot solve linear system"<<std::endl;
                }
                delete[] pivots;
                return tmpb;
            } else {
                // Least-squares solution in the over-determined case, minimum norm solution in the under-determined one
                int info,m=A.nrow(),n=A.ncol(),o=std::max(m,n);
                Matrix tmpA=A.clone();
                Vector<T> tmpb(o);
                for (int i=0;i<m;i++) tmpb[i] = b[i];
                QRSystemSolve(&m,&n,tmpA.data(),tmpb.data(),&info);
                if (info) {
                    tmpb.fill(T(0));
                    std::cerr<<"Cannot solve linear system"<<std::endl;
                }
                return tmpb.getSubVect(0,A.ncol());
            }
        }
        /// Pseudo inverse.
        /// Pseudo-inverse using SVD
        /// \param A matrix
        /// \param tolrel relative tolerance (under which a sing. value is considered nul)
        /// \return pseudo-inverse
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline pseudo-inverse
        /// \until ...
        friend Matrix pseudoInverse(const Matrix& A,T tolrel=0) {
            int m=A.nrow(),n=A.ncol();
            if (n > m) 
                return transpose(pseudoInverse(transpose(A)));
            Matrix U,Vt;
            Vector<T> S;
            svd(A,U,S,Vt);
            if (tolrel==0) 
                tolrel=std::numeric_limits<T>::epsilon();
            T tol = S[0] * tolrel;
            for (int i=0;i<n;i++) {
                T s=(S[i]>tol)?T(1)/S[i]:T(0);
                for (int j=0;j<n;j++)
                    Vt(i,j)*=s;
            }
            return transpose(U.getColsRef(0,n)*Vt);
        }
        /// QR decomposition.
        /// QR decomposition. A is MxN with M>=N. A=QR where:
        /// \param A matrix
        /// \param Q,R: output
        /// \param all
        /// - false: Q is MxN with orthogonal columns and R is NxN upper triangular 
        /// - true: Q is MxM orthogonal and R is MxN with N first rows upper diagonal and M-N last rows nul.
        ///
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline QR decomposition
        /// \until ...
        friend bool QR(const Matrix& A,Matrix& Q, Matrix& R, bool all=false){
            assert(A.nrow()>=A.ncol());
            int info,m=A.nrow(),n=A.ncol(),qn=(all?m:n);
            if(all) {
                // Copy A in beginning of Q
                Q = Matrix(A.nrow(),A.nrow());
                equalize((int)A.totalSize(),A.data(),1,Q.data(),1);
        R=Matrix(A.nrow(),A.ncol());
        QRFactorization(&m,&qn,&n,Q.data(),R.data(),&info);
            } else
      {
                Q = A.clone();
        R=Matrix(A.ncol(),A.ncol());
        QRFactorization(&m,&qn,&n,Q.data(),R.data(),&info);
      }
            if(info!=1) {
                std::cerr << "Failed QR" << std::endl;
                return false;
            }
            return true;
        }
        /// Cholesky decomposition.
        /// Cholesky decomposition of symmetric positive-definite matrix.
        /// \param A matrix
        /// \param low Choose lower (default) or upper
        /// - true: A=L*L^T with L lower
        /// - false: A=U^T*U with U upper
        /// \return L or U
        ///
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline Cholesky decomposition
        /// \until ...
        friend Matrix cholesky(const Matrix& A,bool low=true)  {
            assert(A.nrow()==A.ncol());
            Matrix b=A.clone();
            int n=A.nrow(); 
            int info;
            choleskyDecomposition(low?"L":"U",&n,b.data(),&info);
            if (info) {
                std::cerr << "Bad cholesky" << std::endl;
                b.fill(T(0));
                return b;
            }
            if (low) {
                for (int j=1; j<n; j++) 
                    for (int i=0; i<j; i++) 
                        b(i,j)=0;
            } else {
                for (int j=1; j<n; j++) 
                    for (int i=0; i<j; i++) 
                        b(j,i)=0;
            }
            return b;
        }


        /// Determinant.
        /// Determinant. Uses LU decomposition.
        /// \param A matrix
        /// \return determinant
        ///
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline Determinant
        /// \until ...
        friend T det(const Matrix& A) {
            assert(A.nrow()==A.ncol());
            Matrix b=A.clone();
            // LU decomposition
            int info,m=A.nrow(),n=A.ncol();
            T d = determinant(&m,&n,b.data(),&info);
            if (info!=0) {
                std::cerr<<"Cannot compute LU decomposition"<<std::endl;
                return 0;
            }
            return d;
        }
        /// ASCII write.
        /// Writes to stream (size and values). Reimplemented from MultiArray: add newlines and iterates over j at fixed i (MultiArray would do the opposite).
        /// \param out output stream
        /// \param A matrix to write
        /// \return updated stream
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline ASCII write
        /// \until ...
        friend inline std::ostream& operator<<(std::ostream& out,const Matrix& A) {
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
        /// Reads from stream (size and values). Reimplemented from MultiArray: add newlines and iterates over j at fixed i (MultiArray would do the opposite).
        /// \param in input stream
        /// \param A matrix to write
        /// \return updated stream
        /// 
        /// \dontinclude LinAlg/test/test.cpp \skip matrices()
        /// \skipline ASCII read
        /// \until ...
        friend inline std::istream& operator>>(std::istream& in,Matrix& A) {
            int m,n;
            in>>m>>n;
            A.setSize(m,n);
            for (int i=0;i<A.nrow();i++)
                for (int j=0;j<A.ncol();j++)
                    in>>A(i,j);
            return in;
        }
    };

    /// Diagonal.
    /// Diagonal matrix
    /// \param d diagonal vector
    /// \return matrix
    /// 
    /// \dontinclude LinAlg/test/test.cpp \skip matrices()
    /// \skipline pre-allocated
    /// \skipline diagonal
    /// \until ...
    template <typename T>
    inline Matrix<T> Diagonal(const Vector<T>& d){
        int n=int(d.size());
        Matrix<T> D=Matrix<T>::Zero(n,n);
        for (int i=0;i<n;i++)
            D(i,i)=d[i];
        return D;
    }

    /// Outer product matrix.
    /// Vector outer product, i.e. the matrix given by v1 * v2^T
    /// \param v1,v2 arguments
    /// \return Result
    /// 
    /// \dontinclude LinAlg/test/test.cpp \skip vectors()
    /// \skipline outer product
    template <typename T>
    Matrix<T> outerProduct(const Vector<T>& v1,const Vector<T>& v2) {
        assert(v1.size()==v2.size());
        int n=(int)v1.size();
        Matrix<T> A(n,n);
        A.fill(T(0));
        matrixProduct(n,n,1,T(1),v1.data(),n,v2.data(),1,T(0),A.data(),'N','N');
        return A;
    }

    /// Inverse.
    /// Inverse of an FMatrix. If non invertible, ouptuts a message to \c cerr
    /// and returns a matrix with zeroed elements.
    /// This works for any FMatrix size, on the contrary to inverse(), the
    /// latter being limited to N<=3.
    /// \param A matrix to inverse
    /// \return the inverse matrix
    /// 
    /// \dontinclude LinAlg/test/test.cpp \skip fmatrices()
    /// \skipline A2=
    /// \skipline inverse
    /// \skipline A3=
    /// \skipline inverse
    template <typename T,int N>
    FMatrix<T,N,N> inverseFMatrix(const FMatrix<T,N,N>& A) {
        if (N<=3)
            return inverse(A); // Direct inversion
        FMatrix<T,N,N> invA(A);
        // LU
        int *pivots=new int[N];
        int info,n=N;
        // Inverse
        matrixInverse(&n,invA.data(),&n,pivots,&info);
        if (info) {
            std::cerr<<"Cannot invert matrix"<<std::endl;
            invA.fill(T(0));
        }
        delete[] pivots;
        return invA;
    }

    /// SVD.
    /// Singular value decomposition. A is MxN. S is of size min(M,N) with decreasing singular values. A=U*diag(S)*Vt where U (resp. Vt) is
    /// MxM (resp NxN) orthonormal, diag(S) is MxN with S as diagonal. If M<N (resp. M>N) then Vt (resp. U) is incompletely filled, expect all is true.
    /// \param A matrix
    /// \param U,S,Vt SVD output
    /// \param all complete U and V is true
    /// 
    /// \dontinclude LinAlg/test/test.cpp \skip fmatrices()
    /// \skipline Singular value decomposition
    /// \until ...
    template <typename T,int M,int N> 
    void svd(const FMatrix<T,M,N>& A, FMatrix<T,M,M> &U, FVector<T,M> &S, FMatrix<T,N,N> &Vt, bool all=false) {
        FMatrix<T,M,N> cpy(A);
        int nr=M,nc=N;
        int info;
        singularValuesDecomposition(all?"A":"S",&nr,&nc,cpy.data(),S.data(),U.data(),Vt.data(),&info);
        if (info) {
            std::cerr<<"Cannot compute SVD"<<std::endl;
            return;
        }
    }

    /// Eigenvalues calculation
    /// Given square matrix, only eigenvalues are obtained.
    /// \param A square matrix to decompose
    /// \param wr real parts of eigenvalues
    /// \param wi imaginary parts of eigenvalues
    template <typename T>
    void eigenvalues(const Matrix<T>& A, Vector<T>& wr, Vector<T>& wi)
    {
        assert(A.ncol()==A.nrow());
        Matrix<T> cpy = A.clone();
        wr = Vector<T>(A.nrow());
        wi = Vector<T>(A.nrow());

        int n = A.nrow();
        Vector<T> vl(A.nrow()), vr(A.nrow());
        int info;

        eigenValues(&n, cpy.data(), wr.data(), wi.data(), vr.data(), &info);
        if (info)
            std::cerr << "Cannot compute eigenvalues" << std::endl;
    }

    /// Linear system.
    /// Solve linear system. Returns x such that:
    /// - M=N, square system: Ax=b
    /// - M>N, over determined system: x=argmin_y|Ay-b|
    /// - M<N, under determined system: x=argmin_{y,Ay=b}|y|
    ///
    /// \param A matrix
    /// \param b right term
    /// \return solution (zeroed vector if no solution)
    /// 
    /// \dontinclude LinAlg/test/test.cpp \skip fmatrices()
    /// \skipline Linear solve
    /// \until ...
    template <typename T,int M,int N>
    FVector<T,N> linSolve(const FMatrix<T,M,N>& A,const FVector<T,M>& b)
    {
        if(M==N)
            {
                // Linear system is not over- or under- determined
                FMatrix<T,M,N> tmpA(A);
                FVector<T,M> tmpb(b);
                // LU factorization
                int *pivots=new int[M];
                int info,n=M;
                // Solve linear system using factorization
                int nrhs=1;
                LUSystemSolve(&n,tmpA.data(),pivots,tmpb.data(),&info);
                if (info) {
                    std::cerr<<"Cannot solve linear system"<<std::endl;
                    delete [] pivots;
                    return FVector<T,N>(T(0));
                    tmpb.fill(T(0));
                    std::cerr<<"Cannot solve linear system"<<std::endl;
                }
                delete[] pivots;
                return FVector<T,N>(tmpb.data()); //Safe since M==N but necessary for instantiation if M!=N
            }
        // Least-squares solution in the over-determined case, minimum norm solution in the under-determined one
        int info,m=M,n=N,o=std::max(m,n);
        int nrhs = 1;
        FMatrix<T,M,N> tmpA(A);
        if(M > N) { // Over-determined system: least squares solution
            FVector<T,M> tmpb;
            for (int i=0;i<m;i++) tmpb[i] = b[i];
            QRSystemSolve(&m,&n,tmpA.data(),tmpb.data(),&info);
            if (info) {
                tmpb.fill(T(0));
                std::cerr<<"Cannot solve linear system"<<std::endl;
            }
            return FVector<T,N>( tmpb.data() );
        }
        // Under-determined system (M<N): minimum norm solution
        FVector<T,N> tmpb;
        for (int i=0;i<m;i++) tmpb[i] = b[i];
        QRSystemSolve(&m,&n,tmpA.data(),tmpb.data(),&info);
        if (info) {
            tmpb.fill(T(0));
            std::cerr<<"Cannot solve linear system"<<std::endl;
        }
        return tmpb;
    }
    /// Pseudo inverse.
    /// Pseudo-inverse using SVD
    /// \param A matrix
    /// \param tolrel relative tolerance (under which a sing. value is considered nul)
    /// \return pseudo-inverse
    /// 
    /// \dontinclude LinAlg/test/test.cpp \skip fmatrices()
    /// \skipline B
    /// \skipline b,x
    /// \skipline C(
    /// \skipline D(
    /// \skipline d(
    /// \skipline Pseudo-inverse
    /// \until ...
    template <typename T,int M,int N>
    FMatrix<T,N,M> pseudoInverse(const FMatrix<T,M,N>& A,T tolrel=0) {
        if (N > M) 
            return transpose(pseudoInverse(transpose(A)));
        FMatrix<T,M,M> U; FMatrix<T,N,N> Vt;
        FVector<T,M> S;
        svd(A,U,S,Vt);
        if (tolrel==0) 
            tolrel=std::numeric_limits<T>::epsilon();
        T tol = S[0] * tolrel;
        for (int i=0;i<N;i++) {
            T s=(S[i]>tol)?T(1)/S[i]:T(0);
            for (int j=0;j<N;j++)
                Vt(i,j)*=s;
        }
        return transpose(FMatrix<T,M,N>(U.data())*Vt);
    }
    /// QR decomposition.
    /// QR decomposition. A is MxN with M>=N. A=QR where:
    /// - Q is MxN with orthogonal columns
    /// - R is NxN upper triangular
    /// \param A matrix
    /// \param Q,R: output
    ///
    /// \dontinclude LinAlg/test/test.cpp \skip fmatrices()
    /// \skipline QR decomposition
    /// \until ...
    template <typename T,int M,int N>
    bool QR(const FMatrix<T,M,N>& A,FMatrix<T,M,N>& Q, FMatrix<T,N,N>& R){
        assert(M>=N);
        int info,m=M,n=N;
        Q = A;
        QRFactorization(&m,&n,&n,Q.data(),R.data(),&info);
        if(info!=1) {
            std::cerr << "Failed QR" << std::endl;
            return false;
        }
        return true;
    }
    /// QR decomposition.
    /// QR decomposition. A is MxN with M>=N. A=QR where:
    /// - Q is MxM orthogonal
    /// - R is MxN with N first rows upper diagonal and M-N last rows nul.
    /// \param A matrix
    /// \param Q,R: output
    ///
    /// \dontinclude LinAlg/test/test.cpp \skip fmatrices()
    /// \skipline QR decomposition
    /// \until ...
    template <typename T,int M,int N>
    bool QRAll(const FMatrix<T,M,N>& A,FMatrix<T,M,M>& Q, FMatrix<T,M,N>& R){
        assert(M>=N);
        int info,m=M,n=N;
        equalize(M*N,A.data(),1,Q.data(),1);
        QRFactorization(&m,&m,&n,Q.data(),R.data(),&info);
        if(info!=1) {
            std::cerr << "Failed QR" << std::endl;
            return false;
        }
        return true;
    }
    /// Cholesky decomposition.
    /// Cholesky decomposition of symmetric positive-definite matrix.
    /// \param A matrix
    /// \param low Choose lower (default) or upper
    /// - true: A=L*L^T with L lower
    /// - false: A=U^T*U with U upper
    /// \return L or U
    ///
    /// \dontinclude LinAlg/test/test.cpp \skip fmatrices()
    /// \skipline Cholesky decomposition
    /// \until ...
    template <typename T,int N>
    FMatrix<T,N,N> cholesky(const FMatrix<T,N,N>& A,bool low=true) {
        FMatrix<T,N,N> b(A);
        int n=N;
        int info;
        choleskyDecomposition(low?"L":"U",&n,b.data(),&info);
        if (info) {
            std::cerr << "Bad cholesky" << std::endl;
            b.fill(T(0));
            return b;
        }
        if (low) {
            for (int j=1; j<n; j++) 
                for (int i=0; i<j; i++) 
                    b(i,j)=0;
        } else {
            for (int j=1; j<n; j++) 
                for (int i=0; i<j; i++) 
                    b(j,i)=0;
        }
        return b;
    }

    /// Determinant.
    /// Determinant. Try Cholesky decomposition just in case. If not sym def pos, uses SVD.
    /// \param A matrix
    /// \return determinant
    ///
    /// \dontinclude LinAlg/test/test.cpp \skip fmatrices()
    /// \skipline sym pos-def
    /// \skipline Determinant
    /// \until ...
    template <typename T,int N>
    T detFMatrix(const FMatrix<T,N,N>& A) {
        int n=N; 
        FMatrix<T,N,N> b(A);
        int info;
        // Try cholesky factorization -> only for positive matrices!
        choleskyDecomposition((char*)"L",&n,b.data(),&info);
        if (!info) {
            T d=T(1);
            for (int i=0; i<n; i++) d*=b(i,i); 
            return d*d;
        }
        // Try SVD
        FMatrix<T,N,N> U,V;
        FVector<T,N> s;
        svd(A,U,s,V);
        T d=T(1);
        for (int i=0; i<N; i++) d*=s[i]; 
        return d;
    }

    ///@}
}
