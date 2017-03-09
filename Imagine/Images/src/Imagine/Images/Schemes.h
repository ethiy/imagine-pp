// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

namespace Imagine {
    /// \addtogroup Images
    /// @{

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    const double IMAGE_SCHEME_EPS = 1e-6;
#endif

    /// Offsets to neighbours.
    /// PDE schemes. Offsets to neighbours of p in each direction. Set to 0 when it would lead outside of the image. <b>Warning: dm is positive</b>, thus -dm should be applied to get backward neighbour.
    /// \param u image
    /// \param p position
    /// \param dp offsets to forward neighbors (dp[i] for i<sup>th</sup> dim)
    /// \param dm offsets to backward neighbors (dm[i] for i<sup>th</sup> dim)
    ///
    /// \dontinclude Images/test/test.cpp \skip schemes()
    /// \skipline neighb offsets
    template <typename T,int dim>
    void neighbourOffsets(const Image<T,dim>& u, const Coords<dim>& p, FVector<size_t,dim>& dp,FVector<size_t,dim>& dm) {
        for( int i = 0 ; i < dim ; i++) {
            dm[i] = (p[i] > 0) ? u.stride(i) : 0;
            dp[i] = (p[i] < u.size(i)-1) ? u.stride(i) : 0;
        }
    }
    /// Coordinates of neighbours.
    /// PDE schemes. Coordinates of neighbours of p in each direction. Set to p[i] when it would lead outside of the image.
    /// \param u image
    /// \param p position
    /// \param pp coordinates of forward neighbours (change p[i] into pp[i] to get i<sup>th</sup> forward neighbour)
    /// \param pm coordinates of backward neighbours (change p[i] into pm[i] to get i<sup>th</sup> backward neighbour)
    ///
    /// \dontinclude Images/test/test.cpp \skip schemes()
    /// \skipline neighb coords
    template <typename T,int dim>
    void neighbourCoords(const Image<T,dim>& u, const Coords<dim>& p, Coords<dim>& pp, Coords<dim>& pm) {
        for( int i = 0 ; i < dim ; i++) {
            pm[i] = (p[i] > 0) ? p[i]-1 : p[i];
            pp[i] = (p[i] < u.size(i)-1) ? p[i]+1 : p[i];
        }
    }
    /// Derivative.
    /// PDE schemes. Derivative.
    /// \param u image
    /// \param p position
    /// \param d direction
    /// \return derivative
    ///
    /// \dontinclude Images/test/test.cpp \skip schemes()
    /// \skipline Derivatives at p
    /// \until ...
    template <typename T, int dim>
    T derivative(const Image<T,dim>& u, const Coords<dim>& p, int d) {
        Coords<dim> np(p), pp(p);
        typename Image<T,dim>::scalar_type h(2);
        if (np[d]>0) np[d]--; else h--;
        if (pp[d]<u.size(d)-1) pp[d]++; else h--; 
        return ( u(pp) - u(np) ) / h;
    }
    /// Laplacian.
    /// PDE schemes. Laplacian.
    /// \param u image
    /// \param p position
    /// \return Laplacian
    ///
    /// \dontinclude Images/test/test.cpp \skip schemes()
    /// \skipline Laplacian at p
    template <typename T, int dim>
    T laplacian(const Image<T,dim>& u, const Coords<dim>& p) {
        const size_t o = u.offset(p);
        const T u0 = u[o];
        T l = -typename Image<T,dim>::scalar_type(2*dim)*u0;
        for (int i=0;i<dim;i++) {
            l += ( ( p[i] < u.size(i)-1 ) ? u[ o + u.stride(i) ] : u0 ) + ( ( p[i] > 0 ) ? u[ o - u.stride(i) ] : u0 ) ; 
        }
        return l;
    }
    /// Mean curvature (3D).
    /// PDE schemes. Mean curvature of iso level at p.
    /// \param u image
    /// \param p position
    /// \return mean curvature
    ///
    /// \dontinclude Images/test/test.cpp \skip schemes()
    /// \skipline Mean curvature of iso level at p
    template <typename T>
    T meanCurvature(const Image<T,3>& u, const Coords<3>& p) {
        const size_t o = u.offset(p);
        const T u0 = u[o];
        FVector<size_t,3> dp,dm;
        neighbourOffsets(u,p,dp,dm);

        const T upx  = u[o+dp[0]];
        const T umx  = u[o-dm[0]];
        const T upy  = u[o+dp[1]];
        const T umy  = u[o-dm[1]];
        const T upz  = u[o+dp[2]];
        const T umz  = u[o-dm[2]];

        const T umxmy = u[o-dm[0]-dm[1]];
        const T upxmy = u[o+dp[0]-dm[1]];
        const T umxpy = u[o-dm[0]+dp[1]];
        const T upxpy = u[o+dp[0]+dp[1]];
        const T umymz = u[o-dm[1]-dm[2]];
        const T upymz = u[o+dp[1]-dm[2]];
        const T umypz = u[o-dm[1]+dp[2]];
        const T upypz = u[o+dp[1]+dp[2]];
        const T umzmx = u[o-dm[2]-dm[0]];
        const T upzmx = u[o+dp[2]-dm[0]];
        const T umzpx = u[o-dm[2]+dp[0]];
        const T upzpx = u[o+dp[2]+dp[0]];

        const T ux  = ( upx - umx ) / 2;
        const T uy  = ( upy - umy ) / 2;
        const T uz  = ( upz - umz ) / 2;

        const T uxx = upx - 2 * u0 + umx;
        const T uyy = upy - 2 * u0 + umy;
        const T uzz = upz - 2 * u0 + umz;
        const T uxy = (upxpy + umxmy - upxmy - umxpy) / 4;
        const T uyz = (upypz + umymz - upymz - umypz) / 4;
        const T uzx = (upzpx + umzmx - upzmx - umzpx) / 4;

        const T ux2 = ux * ux;
        const T uy2 = uy * uy;
        const T uz2 = uz * uz;
        const T grad = ux2 + uy2 + uz2;

        if (grad < T(IMAGE_SCHEME_EPS)) return 0;

        return (   (uyy+uzz) * ux2
            + (uxx+uzz) * uy2
            + (uxx+uyy) * uz2
            - 2*ux*uy*uxy
            - 2*uz*ux*uzx
            - 2*uy*uz*uyz ) / grad / std::sqrt(grad) / T(2);
    }
    /// Level set Mean curvature motion (3D).
    /// PDE schemes. Level set Mean curvature motion at p
    /// \param u image
    /// \param p position
    /// \return mean curvature motion
    ///
    /// \dontinclude Images/test/test.cpp \skip schemes()
    /// \skipline Level set Mean curvature motion at p
    template <typename T>
    T meanCurvatureMotion(const Image<T,3>& u, const Coords<3>& p) {
        const size_t o = u.offset(p);
        const T u0 = u[o];
        FVector<size_t,3> dp,dm;
        neighbourOffsets(u,p,dp,dm);

        const T upx  = u[o+dp[0]];
        const T umx  = u[o-dm[0]];
        const T upy  = u[o+dp[1]];
        const T umy  = u[o-dm[1]];
        const T upz  = u[o+dp[2]];
        const T umz  = u[o-dm[2]];

        const T umxmy = u[o-dm[0]-dm[1]];
        const T upxmy = u[o+dp[0]-dm[1]];
        const T umxpy = u[o-dm[0]+dp[1]];
        const T upxpy = u[o+dp[0]+dp[1]];
        const T umymz = u[o-dm[1]-dm[2]];
        const T upymz = u[o+dp[1]-dm[2]];
        const T umypz = u[o-dm[1]+dp[2]];
        const T upypz = u[o+dp[1]+dp[2]];
        const T umzmx = u[o-dm[2]-dm[0]];
        const T upzmx = u[o+dp[2]-dm[0]];
        const T umzpx = u[o-dm[2]+dp[0]];
        const T upzpx = u[o+dp[2]+dp[0]];

        const T ux  = ( upx - umx ) / 2;
        const T uy  = ( upy - umy ) / 2;
        const T uz  = ( upz - umz ) / 2;

        const T uxx = upx - 2 * u0 + umx;
        const T uyy = upy - 2 * u0 + umy;
        const T uzz = upz - 2 * u0 + umz;
        const T uxy = (upxpy + umxmy - upxmy - umxpy) / 4;
        const T uyz = (upypz + umymz - upymz - umypz) / 4;
        const T uzx = (upzpx + umzmx - upzmx - umzpx) / 4;

        const T ux2 = ux * ux;
        const T uy2 = uy * uy;
        const T uz2 = uz * uz;
        const T grad = ux2 + uy2 + uz2;

        if (grad < T(IMAGE_SCHEME_EPS)) return 0;

        return (   (uyy+uzz) * ux2
            + (uxx+uzz) * uy2
            + (uxx+uyy) * uz2
            - 2*ux*uy*uxy
            - 2*uz*ux*uzx
            - 2*uy*uz*uyz ) / grad / T(2);
    }
    /// Mean curvature (2D).
    template <typename T>
    T meanCurvature(const Image<T,2>& u, const Coords<2>& p) {
        const size_t o = u.offset(p);
        const T u0 = u[o];
        FVector<size_t,2> dp,dm;
        neighbourOffsets(u,p,dp,dm);

        const T upx  = u[o+dp[0]];
        const T umx  = u[o-dm[0]];
        const T upy  = u[o+dp[1]];
        const T umy  = u[o-dm[1]];

        const T umxmy = u[o-dm[0]-dm[1]];
        const T upxmy = u[o+dp[0]-dm[1]];
        const T umxpy = u[o-dm[0]+dp[1]];
        const T upxpy = u[o+dp[0]+dp[1]];

        const T ux = ( upx - umx ) / 2;
        const T uy = ( upy - umy ) / 2;

        const T uxx = upx - 2 * u0 + umx;
        const T uyy = upy - 2 * u0 + umy;
        const T uxy = (upxpy + umxmy - upxmy - umxpy) / 4;

        const T ux2 = ux * ux;
        const T uy2 = uy * uy;
        const T grad = ux2 + uy2;

        if (grad < T(IMAGE_SCHEME_EPS)) return 0;

        return (uyy * ux2 - 2 * ux * uy * uxy + uxx * uy2) / grad / std::sqrt(grad);
    }
    /// Level set Mean curvature motion (2D).
    template <typename T>
    T meanCurvatureMotion(const Image<T,2>& u, const Coords<2>& p) {
        const size_t o = u.offset(p);
        const T u0 = u[o];
        FVector<size_t,2> dp,dm;
        neighbourOffsets(u,p,dp,dm);

        const T upx  = u[o+dp[0]];
        const T umx  = u[o-dm[0]];
        const T upy  = u[o+dp[1]];
        const T umy  = u[o-dm[1]];

        const T umxmy = u[o-dm[0]-dm[1]];
        const T upxmy = u[o+dp[0]-dm[1]];
        const T umxpy = u[o-dm[0]+dp[1]];
        const T upxpy = u[o+dp[0]+dp[1]];

        const T ux = ( upx - umx ) / 2;
        const T uy = ( upy - umy ) / 2;

        const T uxx = upx - 2 * u0 + umx;
        const T uyy = upy - 2 * u0 + umy;
        const T uxy = (upxpy + umxmy - upxmy - umxpy) / 4;

        const T ux2 = ux * ux;
        const T uy2 = uy * uy;
        const T grad = ux2 + uy2;

        if (grad < T(IMAGE_SCHEME_EPS)) return 0;

        return (uyy * ux2 - 2 * ux * uy * uxy + uxx * uy2) / grad;
    }
    /// Gaussian curvature of iso level (3D).
    /// PDE schemes. Gaussian curvature of iso level at p
    /// \param u image
    /// \param p position
    /// \return Gaussian curvature of iso level
    ///
    /// \dontinclude Images/test/test.cpp \skip schemes()
    /// \skipline Gaussian curvature of iso level at p
    template <typename T>
    T gaussianCurvature(const Image<T,3>& u, const Coords<3>& p) {
        const size_t o = u.offset(p);
        const T u0 = u[o];
        FVector<size_t,3> dp,dm;
        neighbourOffsets(u,p,dp,dm);

        const T upx  = u[o+dp[0]];
        const T umx  = u[o-dm[0]];
        const T upy  = u[o+dp[1]];
        const T umy  = u[o-dm[1]];
        const T upz  = u[o+dp[2]];
        const T umz  = u[o-dm[2]];

        const T umxmy = u[o-dm[0]-dm[1]];
        const T upxmy = u[o+dp[0]-dm[1]];
        const T umxpy = u[o-dm[0]+dp[1]];
        const T upxpy = u[o+dp[0]+dp[1]];
        const T umymz = u[o-dm[1]-dm[2]];
        const T upymz = u[o+dp[1]-dm[2]];
        const T umypz = u[o-dm[1]+dp[2]];
        const T upypz = u[o+dp[1]+dp[2]];
        const T umzmx = u[o-dm[2]-dm[0]];
        const T upzmx = u[o+dp[2]-dm[0]];
        const T umzpx = u[o-dm[2]+dp[0]];
        const T upzpx = u[o+dp[2]+dp[0]];

        const T ux  = ( upx - umx ) / 2;
        const T uy  = ( upy - umy ) / 2;
        const T uz  = ( upz - umz ) / 2;

        const T uxx = upx - 2 * u0 + umx;
        const T uyy = upy - 2 * u0 + umy;
        const T uzz = upz - 2 * u0 + umz;
        const T uxy = (upxpy + umxmy - upxmy - umxpy) / 4;
        const T uyz = (upypz + umymz - upymz - umypz) / 4;
        const T uzx = (upzpx + umzmx - upzmx - umzpx) / 4;

        const T ux2 = ux * ux;
        const T uy2 = uy * uy;
        const T uz2 = uz * uz;
        const T grad = ux2 + uy2 + uz2;

        if (grad < T(IMAGE_SCHEME_EPS)) return 0;

        return ( ux2 * (uyy*uzz - uyz*uyz) + uy2 * (uxx*uzz - uzx*uzx) + uz2 * (uxx*uyy - uxy*uxy)
            + 2 * ( ux*uy * (uzx*uyz - uxy*uzz) + uy*uz * (uxy*uzx - uyz*uxx) + ux*uz * (uxy*uyz - uzx*uyy) ) ) / (grad*grad);
    }
    /// Unit normal of iso level.
    /// PDE schemes. Unit normal of iso level at p
    /// \param u image
    /// \param p position
    /// \return n normal
    ///
    /// \dontinclude Images/test/test.cpp \skip schemes()
    /// \skipline Gradient and unit normal
    template <typename T, int dim>
    FVector<T,dim> normal(const Image<T,dim>& u, const Coords<dim>& p) {
        FVector<T,dim> n = gradient(u,p);
        T nn = norm(n);
        if (nn < T(IMAGE_SCHEME_EPS)) nn = T(IMAGE_SCHEME_EPS);
        n /= nn;
        return n;
    }
    /// Gradient.
    /// PDE schemes. Gradient at p
    /// \param u image
    /// \param p position
    /// \return gradient
    ///
    /// \dontinclude Images/test/test.cpp \skip schemes()
    /// \skipline Gradient and unit normal
    template <typename T, int dim>
    FVector<T,dim> gradient(const Image<T,dim> &u, const Coords<dim>& p) {
        const size_t o = u.offset(p);
        const T u0 = u[o];
        FVector<T,dim> g;
        for (int i=0;i<dim;i++) {
            g[i] = ( ( ( p[i] < u.size(i)-1 ) ? u[ o + u.stride(i) ] : u0 ) - ( ( p[i] > 0 ) ? u[ o - u.stride(i) ] : u0 ) ) / T(2); 
        }
        return g;
    }

    ///@}
}
