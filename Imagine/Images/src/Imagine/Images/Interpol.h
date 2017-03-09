// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

// Interpolation

#ifndef DOXYGEN_SHOULD_SKIP_THIS

namespace Imagine {


    template <typename T, int dim> class Image;
    template <typename T> class PixelTraits;

    // Linear Interpolation
    // Return type is the same as image type (a Image<int,dim> will not return a real)
    template <typename T, int dim, typename U> inline typename PixelTraits<T>::template CastPixel<U>::value_type interpolate(const Image<T,dim> &I, FVector<U,dim> x)
    {
        for (int i=0;i<dim;i++) {
            if (x[i]<0) x[i] = U(0);
            else if (x[i] > I.size(i)-1) x[i] = U(I.size(i)-1);
        }

        FVector<U,dim> a; // partie decimale
        Coords<dim> c; // partie entiere
        for (int i=0;i<dim;i++) {
            c[i]=int(x[i]);
            a[i]=x[i]-U(c[i]);
        }

        typedef typename PixelTraits<T>::template CastPixel<U>::value_type return_type;
        return_type val(U(0));
        for (CoordsIterator<dim> p(c,c+Coords<dim>(1)) ; p != CoordsIterator<dim>() ; ++p) {
            U f=1;
            for (int i=0;i<dim;i++)
                f*=((*p)[i]==c[i])?(U(1)-a[i]):a[i];
            if (f==0)
                continue;
            val=val+return_type(I(*p))*f;
        }
        return val;
    }


}

#endif
