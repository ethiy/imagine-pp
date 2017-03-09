// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

// pixel scalar types used in interpolate... No doc.

#ifndef DOXYGEN_SHOULD_SKIP_THIS

namespace Imagine {



    template <typename T> class PixelTraits {
    public:
        typedef T scalar_type;

        template <typename U>
        struct CastPixel
        {
            typedef U value_type;
        };
    };

    template <typename T, int dim> class PixelTraits< FVector<T,dim> > {
    public:
        typedef T scalar_type;

        template <typename U>
        struct CastPixel
        {
            typedef FVector<U,dim> value_type;
        };
    };

    template <typename T> class PixelTraits< RGB<T> > {
    public:
        typedef T scalar_type;

        template <typename U>
        struct CastPixel
        {
            typedef RGB<U> value_type;
        };
    };

    template <typename T> class PixelTraits< RGBA<T> > {
    public:
        typedef T scalar_type;

        template <typename U>
        struct CastPixel
        {
            typedef RGBA<U> value_type;
        };
    };

}

#endif
