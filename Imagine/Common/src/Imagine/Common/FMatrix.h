// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

namespace Imagine {
    /// \addtogroup Common
    /// @{


    /// \headerfile Imagine/Common.h "Imagine/Common.h"
    /// %Matrix of fixed dimension.
    /// Fixed size vectors.
    /// \param T value type
    /// \param M,N dimensions (M=rows N=columns)
    template <typename T,int M,int N> class FMatrix {
    protected:
        /// internal storage.
        T _data[M*N];
    public:
        /// Empty constructor.
        /// Constructs an uninitialized MxN matrix of elements of type T
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline uninitialized
        FMatrix(){}
        /// Constructor with constant value.
        /// Constructs an MxN matrix of elements of type T, each initialized to v
        /// \param v value used for initialization
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline filled with constant value
        explicit FMatrix(const T& v) {
            fill(v);
        }
        /// Constructor from C array.
        /// Constructs an MxN matrix of elements of type T, and copies values to it.  t contains elements (0,0), (1,0), ...
        /// \param t C array used for initialization
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline filled from C array 
        /// \until copying
        FMatrix(const T t[M*N]){
            for (int k=0;k<M*N;k++)
                _data[k] = t[k];
        }
        /// Constructor from bidim C array.
        /// Constructs an MxN matrix of elements of type T, and copies values to it
        /// \param t C bidimensional array used for initialization
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline filled from bidim C array 
        /// \until copying
        FMatrix(const T t[M][N]){
            for (int j=0;j<N;j++) for (int i=0;i<M;i++)
                (*this)(i,j) = t[i][j];
        }
        /// Copy constructor
        /// Constructs from another FMatrix (with a possibly different type)
        /// \param A FMatrix to be copied (has to be of the same dimension)
        /// \tparam T2 value type of A
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline copy constructor
        /// \until copy from different type
        template <typename T2> FMatrix(const FMatrix<T2,M,N>& A) {
            for (int k=0;k<M*N;k++)
                _data[k] = T(A[k]);
        }
        /// Filling.
        /// Fills with constant value
        /// \param v value to be copied to each element
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline Fills with constant value
        FMatrix& fill(const T& v) {
            for (int k=0;k<M*N;k++)
                _data[k] = v;
            return *this;
        }
        /// Zero matrix
        /// Matrix with constant 0 value
        /// \return matrix
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline Matrix with constant 0 value
        static FMatrix Zero() {
            FMatrix Z;
            std::memset(Z._data,0,M*N*sizeof(T));
            return Z;
        }
        /// Assignment.
        /// Assigns from another FMatrix (of possibly different type but same dimension)
        /// \param B Source FVector
        /// \tparam T2 value type of B
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline assignment 
        /// \until assignment from different type
        template <typename T2> 
        FMatrix& operator = (const FMatrix<T2,M,N>& B) {
            for (int k=0;k<M*N;k++)
                _data[k] = T(B[k]);
            return *this;
        }
        /// Size.
        /// Total dimension
        /// \return M*N
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline size
        int size() const { return M*N; }
        /// Number of rows.
        /// Number of rows
        /// \return M
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline number of rows
        int nrow() const { return M; }
        /// Number of columns.
        /// Number of columns
        /// \return N
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline number of columns
        int ncol() const { return N; }
        /// Read access.
        /// Reads element (i,j)
        /// \param i row index
        /// \param j column index
        /// \return const reference to element (i,j)
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline read access
        const T& operator () (int i, int j) const {
            assert(i>=0 && i<M && j>=0 && j<N);
            return (*this)[i+M*j];
        }
        /// Write access.
        /// Writes element (i,j)
        /// \param i row index
        /// \param j column index
        /// \return Reference to element (i,j)
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline write access
        T& operator () (int i, int j) {
            assert(i>=0 && i<M && j>=0 && j<N);
            return (*this)[i+M*j];
        }
        /// 1D read access.
        /// Reads element at position k. Element (i,j) is at position i+M*j
        /// \param k element index
        /// \return const ref to element at position k
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline 1D read access []
        const T& operator [] (int k) const {
            assert(k>=0 && k<M*N);
            return _data[k];
        }
        /// 1D write access.
        /// Writes element at position k. Element (i,j) is at position i+M*j
        /// \param k element index
        /// \return Reference to element at position k
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline 1D write access []
        T& operator [] (int k) {
            assert(k>=0 && k<M*N);
            return _data[k];
        }
        /// Data pointer (read).
        /// Pointer to data for reading
        /// \return const pointer to FMatrix elements. Element (i,j) is in position i+M*j.
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline data pointer (read)
        const T* data() const { return _data; }
        /// Data pointer (write).
        /// Pointer to data for writing
        /// \return Pointer to FMatrix elements.  Element (i,j) is in position i+M*j.
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline data pointer (write)
        T* data() { return _data; }
        /// Identity.
        /// Identify Matrix
        /// \return identity
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline identity
        /// \until ...
        static FMatrix Identity() {
            assert(M==N);
            FMatrix I(T(0));
            for (int i=0;i<M;i++)
                I(i,i) = T(1);
            return I;
        }
        /// Cross product matrix.
        /// Matrix corresponding to a 3D cross product, i.e. such that for all vector w, P*w gives v^w
        /// \param v The vector.
        /// \return matrix
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline cross product matrix
        /// \until ...
        static FMatrix CrossProd(const FVector<T,3>& v) {
            assert(M==N && M==3);
            FMatrix P(T(0));
            P(1,0) = v.z();
            P(0,1) = - v.z();
            P(2,0) = - v.y();
            P(0,2) = v.y();
            P(2,1) = v.x();
            P(1,2) = - v.x();
            return P;
        }       
        /// Equality test.
        /// Equality test (component wise)
        /// \param B FMatrix for comparison (should be of same dims)
        /// \return true if *this equals B
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline ==
        bool operator == (const FMatrix& B) const {
            for (int k=0;k<M*N;k++)
                if ((*this)[k] != B[k]) return false;
            return true;
        }
        /// Inequality test.
        /// Inequality test (component wise)
        /// \param B FMatrix for comparison (should be of same dims)
        /// \return true if *this does not equal B
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline !=
        bool operator != (const FMatrix& B) const {
            return !(*this == B);
        }
        /// Addition.
        /// Addition of two FMatrix
        /// \param B FMatrix to be added to myself
        /// \return sum 
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline +
        FMatrix operator + (const FMatrix& B) const {
            FMatrix C;
            for (int k=0;k<M*N;k++) C[k] = _data[k] + B[k];
            return C;
        }
        /// Substraction.
        /// Substraction of two FMatrix
        /// \param B FMatrix to be substracted from myself
        /// \return difference 
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline -
        FMatrix operator - (const FMatrix& B) const {
            FMatrix C;
            for (int k=0;k<M*N;k++) C[k] = _data[k] - B[k];
            return C;
        }
        /// In place Addition.
        /// In place Addition of FMatrix
        /// \param B FMatrix to be added to myself
        /// \return self reference 
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline +=
        FMatrix& operator += (const FMatrix& B) {
            for (int k=0;k<M*N;k++) _data[k] += B[k];
            return *this;
        }
        /// In place Substraction.
        /// In place Substraction of FMatrix
        /// \param B FMatrix to be substracted from myself
        /// \return self reference 
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline -=
        FMatrix& operator -= (const FMatrix& B) {
            for (int k=0;k<M*N;k++) _data[k] -= B[k];
            return *this;
        }
        /// Scalar Addition.
        /// Adds a scalar to each element
        /// \param s Scalar to be added to myself
        /// \return sum
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline + scalar
        FMatrix operator + (T s) const {
            FMatrix C;
            for (int k=0;k<M*N;k++) C[k] = _data[k] + s;
            return C;
        }
        /// Scalar Substraction.
        /// Substracts a scalar to each element
        /// \param s Scalar to be substracted from myself
        /// \return difference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline - scalar
        FMatrix operator - (T s) const {
            FMatrix C;
            for (int k=0;k<M*N;k++) C[k] = _data[k] - s;
            return C;
        }
        /// Scalar in place Addition.
        /// Adds a scalar to each own element
        /// \param s Scalar to be added to myself
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline += scalar
        FMatrix& operator += (T s) {
            for (int k=0;k<M*N;k++) _data[k] += s;
            return *this;
        }
        /// Scalar in place substractrion.
        /// Subtracts a scalar to each own element
        /// \param s Scalar to be substracted from myself
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline -= scalar
        FMatrix& operator -= (T s) {
            for (int k=0;k<M*N;k++) _data[k] -= s;
            return *this;
        }
        /// Opposite.
        /// Opposite of a FMatrix
        /// \return Opposite
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline unary -
        FMatrix operator - () const {
            FMatrix C;
            for (int k=0;k<M*N;k++) C[k] = -_data[k];
            return C;
        }
        /// Scalar multiplication.
        /// Multiplies each element by a scalar
        /// \param s The scalar
        /// \return Result
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline * scalar
        FMatrix operator * (T s) const {
            FMatrix C;
            for (int k=0;k<M*N;k++) C[k] = _data[k] * s;
            return C;
        }
        /// Scalar division.
        /// Divides each element by a scalar
        /// \param s The scalar
        /// \return Result
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline / scalar
        FMatrix operator / (T s) const {
            FMatrix C;
            for (int k=0;k<M*N;k++) C[k] = _data[k] / s;
            return C;
        }
        /// Scalar in place multiplication.
        /// Multiplies each element by a scalar
        /// \param s The scalar
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline *= scalar
        FMatrix& operator *= (T s) {
            for (int k=0;k<M*N;k++) _data[k] *= s;
            return *this;
        }
        /// Scalar in place division.
        /// Divides each element by a scalar
        /// \param s The scalar
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline /= scalar
        FMatrix& operator /= (T s) {
            for (int k=0;k<M*N;k++) _data[k] /= s;
            return *this;
        }
        /// Product.
        /// Matrix matrix product
        /// \param B right operand
        /// \return *this * B
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline matrix * matrix
        template <int O>
        FMatrix<T,M,O> operator * (const FMatrix<T,N,O>& B) const {
            FMatrix<T,M,O> C(T(0));
            for (int j=0;j<O;j++) for (int i=0;i<M;i++) {
                for (int k=0;k<N;k++) C(i,j) += (*this)(i,k) * B(k,j);
            }
            return C;
        }
        /// Product with vector.
        /// Matrix vector product
        /// \param v right operand
        /// \return (*this)* v
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline matrix * vector
        FVector<T,M> operator * (const FVector<T,N>& v) const {
            FVector<T,M> w(T(0));
            for (int j=0;j<N;j++)
                for (int i=0;i<M;i++) w[i] += (*this)(i,j) * v[j];
            return w;
        }
        /// Get column.
        /// Returns column of index j
        /// \param j column index
        /// \return column vector
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline Get column
        FVector<T,M> getCol(int j) const {
            assert(j>=0 && j<N);
            FVector<T,M> v;
            for (int i=0;i<M;i++) v[i] = (*this)(i,j);
            return v;
        }
        /// Set column.
        /// Sets column of index j
        /// \param j column index
        /// \param v column
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline Set column
        FMatrix& setCol(int j, const FVector<T,M>& v) {
            assert(j>=0 && j<N);
            for (int i=0;i<M;i++) (*this)(i,j) = v[i];
            return *this;
        }
        /// Get row.
        /// Returns row of index i
        /// \param i row index
        /// \return row vector
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline Get row
        FVector<T,N> getRow(int i) const {
            assert(i>=0 && i<M);
            FVector<T,N> v;
            for (int j=0;j<N;j++) v[j] = (*this)(i,j);
            return v;
        }
        /// Set row.
        /// Sets row of index i
        /// \param i row index
        /// \param v row
        /// \return self reference
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline Set row
        FMatrix& setRow(int i, const FVector<T,N>& v) {
            assert(i>=0 && i<M);
            for (int j=0;j<N;j++) (*this)(i,j) = v[j];
            return *this;
        }
        /// Squared Frobenius norm.
        /// Squared Frobenius norm
        /// \param A argument
        /// \return squared norm
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline Squared Frobenius norm
        friend T norm2(const FMatrix& A) {
            T n = 0;
            for (int k=0;k<M*N;k++) n += A._data[k] * A._data[k];
            return n;
        }
        /// Frobenius norm.
        /// Frobenius norm (provided sqrt is available for T)
        /// \param A argument
        /// \return norm
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline Frobenius norm
        friend inline T norm(const FMatrix& A) {
            assert( !std::numeric_limits<T>::is_integer );
            return ::sqrt(norm2(A));
        }
        /// Binary write.
        /// Writes FMatrix to binary stream
        /// \param out output stream
        /// \param A FMatrix to write
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline binary write
        /// \until ...
        friend void write(std::ostream& out, const FMatrix& A) {
            out.write((const char*)A.data(),std::streamsize(M*N*sizeof(T)));
        }
        /// Binary read.
        /// Reads FMatrix from binary stream
        /// \param in input stream
        /// \param A FMatrix to read
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline binary read
        /// \until ...
        friend void read(std::istream& in, FMatrix& A) {
            in.read((char*)A.data(),std::streamsize(M*N*sizeof(T)));
        }
        /// ASCII write.
        /// Writes FMatrix to stream
        /// \param out output stream
        /// \param A FMatrix to write
        /// \return updated stream
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline ASCII write
        /// \until ...
        friend std::ostream& operator<<(std::ostream& out, const FMatrix& A) {
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
        /// Reads FMatrix from stream
        /// \param in input stream
        /// \param A FMatrix to read
        /// \return updated stream
        /// 
        /// \dontinclude Common/test/test.cpp \skip fMatrices()
        /// \skipline ASCII read
        /// \until ...
        friend std::istream& operator>>(std::istream& in, FMatrix& A) {
            for (int i=0;i<M;i++)
                for (int j=0;j<N;j++)
                    in>>A(i,j);
            return in;
        }

    };

    /// Transpose.
    /// Transposed FMatrix
    /// \param A matrix to transpose
    /// \return Transposed matrix
    /// 
    /// \dontinclude Common/test/test.cpp \skip fMatrices()
    /// \skipline transpose
    template <typename T,int M,int N>
    FMatrix<T,N,M> transpose(const FMatrix<T,M,N>&A) {
        FMatrix<T,N,M> C;
        for (int j=0;j<N;j++) for (int i=0;i<M;i++) C(j,i) = A(i,j);
        return C;
    }

    /// Scalar multiplication.
    /// Multiplies each element by a scalar
    /// \param s The scalar
    /// \param A The FMatrix
    /// \return The result
    /// 
    /// \dontinclude Common/test/test.cpp \skip fMatrices()
    /// \skipline scalar * FMatrix
    template <typename T,int M,int N>
    FMatrix<T,M,N> operator*(T s,const FMatrix<T,M,N>& A) {
        return A*s;
    }
    /// Scalar addition.
    /// Adds a scalar to each element
    /// \param s The scalar
    /// \param A The FMatrix
    /// \return The result
    /// 
    /// \dontinclude Common/test/test.cpp \skip fMatrices()
    /// \skipline scalar + FMatrix
    template <typename T,int M,int N>
    FMatrix<T,M,N> operator+(T s,const FMatrix<T,M,N>& A) {
        return A+s;
    }
    /// Scalar substraction.
    /// Substract each element to a scalar
    /// \param s The scalar
    /// \param A The FMatrix
    /// \return The result
    /// 
    /// \dontinclude Common/test/test.cpp \skip fMatrices()
    /// \skipline scalar - FMatrix
    template <typename T,int M,int N>
    FMatrix<T,M,N> operator-(T s,const FMatrix<T,M,N>& A) {
        return (-A)+s;
    }
    /// Product.
    /// Matrix matrix product (variant)
    /// \param A left operand
    /// \param B right operand
    /// \return transpose(A) * B
    /// 
    /// \dontinclude Common/test/test.cpp \skip fMatrices()
    /// \skipline matrix^T * matrix
    template <typename T,int M,int N,int O>
    FMatrix<T,N,O> tmult(const FMatrix<T,M,N>&A,const FMatrix<T,M,O>& B)  {
        FMatrix<T,N,O> C(T(0));
        for (int j=0;j<O;j++) for (int i=0;i<N;i++)
            for (int k=0;k<M;k++) C(i,j) += A(k,i) * B(k,j);
        return C;
    }
    /// Product.
    /// Matrix matrix product (variant)
    /// \param A left operand
    /// \param B right operand
    /// \return A * transpose(B)
    /// 
    /// \dontinclude Common/test/test.cpp \skip fMatrices()
    /// \skipline matrix * matrix^T
    template <typename T,int M,int N,int O>
    FMatrix<T,M,O> multt(const FMatrix<T,M,N>&A,const FMatrix<T,O,N>& B)  {
        FMatrix<T,M,O> C(T(0));
        for (int j=0;j<O;j++) for (int i=0;i<M;i++)
            for (int k=0;k<N;k++) C(i,j) += A(i,k) * B(j,k); 
        return C;
    }
    /// Product.
    /// Matrix matrix product (variant)
    /// \param A left operand
    /// \param B right operand
    /// \return transpose(A) * transpose(B)
    /// 
    /// \dontinclude Common/test/test.cpp \skip fMatrices()
    /// \skipline matrix^T * matrix^T
    template <typename T,int M,int N,int O>
    FMatrix<T,N,O> tmultt(const FMatrix<T,M,N>&A,const FMatrix<T,O,M>& B)  {
        FMatrix<T,N,O> C(T(0));
        for (int j=0;j<O;j++) for (int i=0;i<N;i++)
            for (int k=0;k<M;k++) C(i,j) += A(k,i) * B(j,k);
        return C;
    }
    /// Product with vector.
    /// Matrix vector product (variant)
    /// \param A left operand
    /// \param v right operand
    /// \return transpose(A)* v
    /// 
    /// \dontinclude Common/test/test.cpp \skip fMatrices()
    /// \skipline matrix^T * vector
    template <typename T,int M,int N>
    FVector<T,N> tmult(const FMatrix<T,M,N>& A,const FVector<T,M>& v) {
        FVector<T,N> w(T(0));
        for (int j=0;j<N;j++)
            for (int i=0;i<M;i++) w[j] += A(i,j) * v[i];
        return w;
    }
    /// Inverse.
    /// Inverse matrix. If non invertible, ouptuts a message to \c cerr and
    /// returns a matrix with zeroed elements.
    /// Available for M = N <= 3 only. For larger matrices, use inverseFMatrix()
    /// in \ref LinAlg.
    /// \param A FMatrix to invert
    /// \return Inverse
    /// 
    /// \dontinclude Common/test/test.cpp \skip fMatrices()
    /// \skipline 1x1 inverse
    /// \until 3x3 inverse
    template <typename T,int M>
    FMatrix<T,M,M> inverse(const FMatrix<T,M,M>& A) {
        FMatrix<T,M,M> I(0.);
        if (M<=3){
            const T _det=det(A);
            if (_det==0) {
                std::cerr << "Non invertible matrix" << std::endl;
            } else {
                if (M==1) {
                    I(0,0)=1/_det;
                } else if (M==2) {
                    I(0,0)=A(1,1)/_det;
                    I(1,1)=A(0,0)/_det;
                    I(0,1)=-A(0,1)/_det;
                    I(1,0)=-A(1,0)/_det;
                } else if (M==3) {
                    // could be made faster with direct formula 
                    for (int i=0;i<3;i++) for (int j=0;j<3;j++) {
                        const int ia = (i+1)%3;
                        const int ib = (i+2)%3;
                        const int ja = (j+1)%3;
                        const int jb = (j+2)%3;
                        I(j,i) = ( A(ia,ja) * A(ib,jb) - A(ib,ja) * A(ia,jb) ) / _det;
                    }
                }
            }
        } else {
            std::cerr << "Code for inverting matrices of size " << M << "*" << M << " is not available" << std::endl;
            std::cerr << "Consider using inverseFMatrix" << std::endl;
        }
        return I;
    }
    /// Determinant.
    /// Determinant. Available for M = N <= 3 only. For larger matrices, consider using Matrix class.
    /// \param A argument
    /// \return determinant
    /// 
    /// \dontinclude Common/test/test.cpp \skip fMatrices()
    /// \skipline Determinant
    template <typename T,int M>
    T det(const FMatrix<T,M,M>& A) {
        if (M==1)
            return A(0,0);
        if(M==2){
            return A(0,0)*A(1,1)-A(0,1)*A(1,0);
        }
        if (M==3) {
            return
                A(0,0) * (A(1,1) * A(2,2) - A(1,2) * A(2,1))
                - A(1,0) * (A(0,1) * A(2,2) - A(2,1) * A(0,2))
                + A(2,0) * (A(0,1) * A(1,2) - A(1,1) * A(0,2));
        }
        std::cerr << "Code for determinant of matrices of size " << M << "*" << M << " is not available" << std::endl;
        std::cerr << "Consider using Matrix class instead of FMatrix" << std::endl;
        return T(0);
    }

    /// Diagonal.
    /// Diagonal matrix
    /// \param d diagonal vector
    /// \return matrix
    /// 
    /// \dontinclude Common/test/test.cpp \skip fMatrices()
    /// \skipline diagonal
    /// \until ...
    template <typename T,int M>
    FMatrix<T,M,M> Diagonal(const FVector<T,M>& d){
        FMatrix<T,M,M> D=FMatrix<T,M,M>::Zero();
        for (int i=0;i<M;i++)
            D(i,i)=d[i];
        return D;
    }

    ///@}
}
