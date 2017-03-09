// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

namespace Imagine {
    /// \addtogroup Images
    /// @{

    // ===============================================
    // Scalings 

    /// Up scaling: fast naive version.
    /// Scales image up. Fast naive version with no interpolation: each original pixel becomes a big constant one.
    /// \param I image to scale
    /// \param fact up scaling factor.
    /// \return a larger image.
    /// 
    /// \dontinclude Images/test/test.cpp \skip algos()
    /// \skipline scale up
    template <typename T, int dim>
    Image<T,dim> scaleUp(const Image<T,dim>&I,int fact) 
    {
        Image<T,dim> I1(I.sizes() * fact);
        // coordinates aware iterator
        for (CoordsIterator<dim> r = I.coordsBegin() ; r != I.coordsEnd() ; ++r) {
            Coords<dim> o=*r;
            T b=I(o);
            for (CoordsIterator<dim> zr(o * fact, o * fact + Coords<dim>(fact-1));zr!=I.coordsEnd();++zr){
                I1(*zr)=b;
            }
        }
        return I1;
    }
    /// Down scaling: fast naive version.
    /// Scales image down. Fast naive version with no anti-aliasing: each pixel is assigneg with the value of one corresponding pixel in the original image.
    /// \param I image to scale
    /// \param fact down scaling factor.
    /// \return a smaller image.
    /// 
    /// \dontinclude Images/test/test.cpp \skip algos()
    /// \skipline scale down
    template <typename T, int dim>
    Image<T,dim> scaleDown(const Image<T,dim>&I,int fact) 
    {
        Image<T,dim> I1(I.sizes()/fact);
        // coordinates aware iterator
        for (CoordsIterator<dim> r = I1.coordsBegin() ; r != I1.coordsEnd() ; ++r)
            I1(*r)=I((*r)*fact);
        return I1;
    }
    /// Reduce image (integer factor).
    /// Reduces image by an integer factor. Each pixel is assigned with the mean of the corresponding original pixels.
    /// \param I image to scale
    /// \param fact divider coefficient.
    /// \return a smaller image.
    /// 
    /// \dontinclude Images/test/test.cpp \skip algos()
    /// \skipline reduction (integer factor)
    template <typename T, int dim>
    Image<T,dim> reduce(const Image<T,dim>&I, int fact)  
    {
        typedef typename PixelTraits<T>::template CastPixel<double>::value_type doubleT;
        Coords<dim> d=I.sizes()/fact;
        double nb=pow(double(fact),dim);
        Image<T,dim> Ir(d);
        for (CoordsIterator<dim> r = Ir.coordsBegin() ; r != Ir.coordsEnd() ; ++r) {
            doubleT p(0.);
            for (CoordsIterator<dim> r2((*r)*fact,((*r)*fact+Coords<dim>(fact-1))); r2!=CoordsIterator<dim>(); ++r2) {
                p+=doubleT(I(*r2));
            }
            Ir(*r)=T(p/nb);
        }
        return Ir;
    }
    /// Reduce image (given dimensions).
    /// Reduces image to given dimensions. Anti aliasing is performed. If ratio is kept, extra parts of the reduced image are filled with the max value of the original one.
    /// \param I image to scale
    /// \param nd reduced dimensions.
    /// \param keepRatio keeps aspect ratio or not?
    /// \return a smaller image.
    /// 
    /// \dontinclude Images/test/test.cpp \skip algos()
    /// \skipline reduction (dimensions)
    /// \until ...
    template <typename T, int dim>
    Image<T,dim> reduce(const Image<T,dim>&I,Coords<dim> nd,bool keepRatio=false)  
    {
        typedef typename PixelTraits<T>::template CastPixel<double>::value_type doubleT;
        Image<doubleT,dim> oI(I);
        Coords<dim> od=I.sizes();
        FVector<double,dim> f=div(FVector<double,dim>(od),FVector<double,dim>(nd));
        std::pair<double,double> mM = range(f);
        assert(mM.first>=1);
        if (keepRatio) {
            f.fill(mM.second);
            nd=Coords<dim>(FVector<double,dim>(od)/mM.second);
        }
        inPlaceBlur(oI,1.5*(sqrt(f)-.99)); // Todo: better filtering
        Image<T,dim> nI(nd);
        for (CoordsIterator<dim> r = nI.coordsBegin() ; r != nI.coordsEnd() ; ++r) {
            FVector<double,dim> x=mult(FVector<double,dim>(*r),f);
            nI(*r)=T(oI.interpolate(x));
        }
        return nI;
    }
    /// Reduce image (given dimensions), 2D alias.
    template <typename T> Image<T,2> inline reduce(const Image<T,2>&I,int w,int h,bool keepRatio=false) { return reduce(I,Coords<2>(w,h),keepRatio); }  // Reduce image (given dimensions), 3D alias.
    /// Reduce image (given dimensions), 3D alias.
    template <typename T> Image<T,3> inline reduce(const Image<T,3>&I,int w,int h,int d,bool keepRatio=false) { return reduce(I,Coords<3>(w,h,d),keepRatio); }  
    /// Reduce image (double factor).
    /// Reduces image by a given fcator. Anti aliasing is performed.
    /// \param I image to scale
    /// \param fact reduction factor.
    /// \return a smaller image.
    /// 
    /// \dontinclude Images/test/test.cpp \skip algos()
    /// \skipline reduction (double factor)
    template <typename T,int dim>
    inline Image<T,dim> reduce(const Image<T,dim>&I,double fact)  
    {
        Coords<dim> nd=Coords<dim>(FVector<double,dim>(I.sizes())/fact);
        return reduce(I,nd);
    }
    /// Enlarge image (given dimensions).
    /// Enlarges image to given dimensions. Interpolation is performed. If ratio is kept, extra parts of the reduced image are filled with the max value of the original one.
    /// \param I image to scale
    /// \param nd enlarged dimensions.
    /// \param keepRatio keeps aspect ratio or not?
    /// \return a larger image.
    /// 
    /// \dontinclude Images/test/test.cpp \skip algos()
    /// \skipline enlargement (dimensions)
    /// \until ...
    template <typename T,int dim>
    Image<T,dim> enlarge(const Image<T,dim>&I,Coords<dim> nd,bool keepRatio=false)  
    {
        typedef typename PixelTraits<T>::template CastPixel<double> doubleT;
        Coords<dim> od=I.sizes();
        FVector<double,dim> f=div(FVector<double,dim>(od),FVector<double,dim>(nd));
        std::pair<double,double> mM = range(f);
        assert(mM.second<=1);
        if (keepRatio) {
            f.fill(mM.second);
            nd=Coords<dim>(FVector<double,dim>(od)/mM.second);
        }
        Image<T,dim> nI(nd);
        for (CoordsIterator<dim> r = nI.coordsBegin() ; r != nI.coordsEnd() ; ++r) {
            FVector<double,dim> x=mult(FVector<double,dim>(*r),f);
            nI(*r)=T(I.interpolate(x));
        }
        return nI;
    }
    /// Enlarge image (given dimensions), 2D alias.
    template <typename T> Image<T,2> inline enlarge(const Image<T,2>&I,int w,int h,bool keepRatio=false) { return enlarge(I,Coords<2>(w,h),keepRatio); }  
    /// Enlarge image (given dimensions), 3D alias.
    template <typename T> Image<T,3> inline enlarge(const Image<T,3>&I,int w,int h,int d,bool keepRatio=false) { return enlarge(I,Coords<3>(w,h,d),keepRatio); }  
    /// Enlarge image (given factor).
    /// Enlarges image by a given factor. Interpolation is performed. 
    /// \param I image to scale
    /// \param fact enlargement factor.
    /// \return a larger image.
    /// 
    /// \dontinclude Images/test/test.cpp \skip algos()
    /// \skipline enlargement (factor)
    template <typename T,int dim>
    inline Image<T,dim> enlarge(const Image<T,dim>&I,double fact)  
    {
        Coords<dim> nd=Coords<dim>(FVector<double,dim>(I.sizes())*fact);
        return enlarge(I,nd);
    }

    // ===============================================
    // Deriche 

    /// In place Deriche filter.
    /// In place Deriche filter 
    /// \param I input/output image.
    /// \param sigma smoothing parameter 
    /// \param order order of derivation (between 0 and 2)
    /// \param d dimension of derivation
    /// \param neumann Neumann border condition (default=true)
    /// 
    /// \dontinclude Images/test/test.cpp \skip algos()
    /// \skipline in place Deriche
    /// \until ...
    template <typename T,int dim>
    void inPlaceDeriche(Image<T,dim>&I,typename PixelTraits<T>::scalar_type sigma, int order, int d, bool neumann = true) {
        // Checks parameter values
        assert(sigma>0 && order>=0 && order<3 && d>=0 && d<dim);

        // Computes coefficients of the recursive filter
        const typename PixelTraits<T>::scalar_type
            alpha = 1.695f/sigma,
            ea = std::exp(alpha),
            ema = std::exp(-alpha),
            em2a = ema*ema,
            b1 = 2*ema,
            b2 = -em2a;

        typename PixelTraits<T>::scalar_type ek,ekn,parity,a1,a2,a3,a4,g0,sumg1,sumg0;

        switch(order) {

            // first-order derivative
                case 1:                 
                    ek = -(1-ema)*(1-ema)*(1-ema)/(2*(ema+1)*ema);
                    a1 = a4 = 0;
                    a2 = ek*ema;
                    a3 = -ek*ema;
                    parity = -1;
                    if (neumann) {
                        sumg1 = (ek*ea) / ((ea-1)*(ea-1));
                        g0 = 0;
                        sumg0 = g0 + sumg1;
                    }
                    else
                        g0 = sumg0 = sumg1 = 0;
                    break;

                    // second-order derivative
                case 2:               
                    ekn = ( -2*(-1+3*ea-3*ea*ea+ea*ea*ea)/(3*ea+1+3*ea*ea+ea*ea*ea) );
                    ek = -(em2a-1)/(2*alpha*ema);
                    a1 = ekn;
                    a2 = -ekn*(1+ek*alpha)*ema;
                    a3 = ekn*(1-ek*alpha)*ema;
                    a4 = -ekn*em2a;
                    parity = 1;
                    if (neumann) {
                        sumg1 = ekn/2;
                        g0 = ekn;
                        sumg0 = g0 + sumg1;
                    }
                    else
                        g0 = sumg0 = sumg1 = 0;
                    break;

                    // smoothing
                default:
                    ek = (1-ema)*(1-ema) / (1+2*alpha*ema - em2a);
                    a1 = ek;
                    a2 = ek*ema*(alpha-1);
                    a3 = ek*ema*(alpha+1);
                    a4 = -ek*em2a;
                    parity = 1;
                    if (neumann) {
                        sumg1 = ek*(alpha*ea+ea-1) / ((ea-1)*(ea-1));
                        g0 = ek;
                        sumg0 = g0 + sumg1;
                    }
                    else
                        g0 = sumg0 = sumg1 = 0;
                    break;
        }

        // filter init
        T *Y = new T[I.size(d)];
        const size_t offset = I.stride(d);
        const size_t nb = I.size(d);

        // Iterates on dimensions other than d
        Coords<dim> beg(0), end = I.sizes() - Coords<dim>(1);
        end[d]=0;
        for (CoordsIterator<dim> p(beg,end); p != CoordsIterator<dim>(); ++p) {
            T *ima = &(I(*p));
            T I2 = *ima; ima += offset;
            T I1 = *ima; ima += offset;
            T Y2 = *(Y++) = sumg0*I2;
            T Y1 = *(Y++) = g0*I1 + sumg1*I2;
            for (size_t i=2; i<nb; i++) {
                I1 = *ima; ima+=offset;
                T Y0 = *(Y++) = a1*I1 + a2*I2 + b1*Y1 + b2*Y2;
                I2=I1; Y2=Y1; Y1=Y0;
            }
            ima -= offset;
            I2 = *ima;
            Y2 = Y1 = (parity*sumg1)*I2;
            *ima = *(--Y)+Y2;
            ima-=offset;
            I1 = *ima;
            *ima = *(--Y)+Y1;
            for (size_t i=nb-3; ; i--) {
                T Y0 = a3*I1+a4*I2+b1*Y1+b2*Y2;
                ima-=offset;
                I2=I1;
                I1=*ima;
                *ima=*(--Y)+Y0;
                Y2=Y1;
                Y1=Y0;
                if (i==0)
                    break;
            } 
        }
        delete [] Y;

    }
    /// Deriche filter.
    /// Deriche filter 
    /// \param I input image.
    /// \param sigma smoothing parameter 
    /// \param order order of derivation (between 0 and 2)
    /// \param d dimension of derivation
    /// \param neumann Neumann border condition (default=true)
    /// \return filtered image
    /// 
    /// \dontinclude Images/test/test.cpp \skip algos()
    /// \skipline Deriche
    /// \until ...
    template <typename T,int dim>
    Image<T,dim> deriche(const Image<T,dim>&I,typename PixelTraits<T>::scalar_type sigma, int order, int d, bool neumann = true) {
        Image<T,dim> J=I.clone();
        inPlaceDeriche(J,sigma,order,d,neumann);
        return J;
    }
    /// In Place Blur (anisotropic).
    /// In place anisotropic blur using Deriche 
    /// \param I input/output image.
    /// \param sigmas smoothing parameters (sigmas[i] for dimension i) 
    /// \param neumann Neumann border condition (default=true)
    /// 
    /// \dontinclude Images/test/test.cpp \skip algos()
    /// \skipline in place anisotropic blur
    template <typename T,int dim>
    void inPlaceBlur(Image<T,dim>&I,const FVector<typename PixelTraits<T>::scalar_type,dim>& sigmas, bool neumann = true) {
        for (int i=0;i<dim;i++) {
            inPlaceDeriche(I,sigmas[i], 0, i, neumann);
        }
    }
    /// In Place Blur.
    /// In place blur using Deriche 
    /// \param I input/output image.
    /// \param sigma smoothing parameter 
    /// \param neumann Neumann border condition (default=true)
    /// 
    /// \dontinclude Images/test/test.cpp \skip algos()
    /// \skipline in place blur
    template <typename T,int dim>
    void inPlaceBlur(Image<T,dim>&I,typename PixelTraits<T>::scalar_type sigma, bool neumann = true) {
        inPlaceBlur(I,FVector<typename PixelTraits<T>::scalar_type,dim>(sigma),neumann);
    }
    /// Blur.
    /// Blur using Deriche 
    /// \param I input image.
    /// \param sigma smoothing parameter 
    /// \param neumann Neumann border condition (default=true)
    /// \return blurred image
    /// 
    /// \dontinclude Images/test/test.cpp \skip algos()
    /// \skipline blur
    template <typename T,int dim>
    Image<T,dim> blur(const Image<T,dim>&I,typename PixelTraits<T>::scalar_type sigma, bool neumann = true) {
        Image<T,dim> J=I.clone();
        inPlaceBlur(J,sigma,neumann);
        return J;
    }
    /// Blur (anisotropic).
    /// Anisotropic blur using Deriche 
    /// \param I input image.
    /// \param sigmas smoothing parameters (sigmas[i] in dimension i) 
    /// \param neumann Neumann border condition (default=true)
    /// \return blurred image
    /// 
    /// \dontinclude Images/test/test.cpp \skip algos()
    /// \skipline anisotropic blur
    template <typename T,int dim>
    Image<T,dim> blur(const Image<T,dim>&I,const FVector<typename PixelTraits<T>::scalar_type,dim>& sigmas, bool neumann = true) {
        Image<T,dim> J=I.clone();
        inPlaceBlur(J,sigmas,neumann);
        return J;
    }

    ///@}
}
