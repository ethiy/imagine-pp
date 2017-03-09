// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

namespace Imagine {
    /// \addtogroup Common
    /// @{


    /// Init with seed.
    /// Init with given seed (to obtain the same sequence)
    /// \param s seed
    /// 
    /// \dontinclude Common/test/test.cpp \skip rands()
    /// \skipline Init with given seed
    inline void initRandom(unsigned int s)
    {
        std::srand(s);
        std::rand();        // The first one is strange (Visual 2003)
    }
    /// Init.
    /// Init. Uses a time-dependent seed.
    /// 
    /// \dontinclude Common/test/test.cpp \skip rands()
    /// \skipline Init with time dependent seed
    inline void initRandom()
    {
        initRandom((unsigned int)std::time(0));
    }
    /// Uniform double.
    /// Uniform double in [0;1]
    /// \return random value
    ///
    /// \dontinclude Common/test/test.cpp \skip rands()
    /// \skipline double in [0;1]
    inline double doubleRandom()
    {
#if (RAND_MAX==0x7fff) // 15 bits? This is really too small!!
        int a = std::rand()<<15;
        int b = std::rand();
        return double(a|b)/((RAND_MAX<<15)|RAND_MAX);
#else
        return double(std::rand())/RAND_MAX;
#endif
    }
    /// Uniform int.
    /// Uniform int between to numbers a and b (included)
    /// \param a,b bounds
    /// \return random value
    ///
    /// \dontinclude Common/test/test.cpp \skip rands()
    /// \skipline int in [a;b]
    inline int intRandom(int a,int b)
    {
        return int(a+(b-a+.999)*doubleRandom());
    }
    /// Uniform unsigned int.
    /// Uniform int between  0 and a (included)
    /// \param a bound
    /// \return random value
    ///
    /// \dontinclude Common/test/test.cpp \skip rands()
    /// \skipline unsigned int in [0;a]
    inline unsigned int uintRandom(unsigned int a)
    {
        return (unsigned int)((a+.999)*doubleRandom());
    }
    /// Uniform size_t.
    /// Uniform size_t between 0 and a (included)
    /// \param a bound
    /// \return random value
    ///
    /// \dontinclude Common/test/test.cpp \skip rands()
    /// \skipline size_t in [0;a]
    inline size_t size_tRandom(size_t a)
    {
        return (size_t)((a+.999)*doubleRandom());
    }
    /// Normal law.
    /// Normal Gaussian
    /// \return random value
    ///
    /// \dontinclude Common/test/test.cpp \skip rands()
    /// \skipline double following a normal Gaussian law
    inline double gaussianRandom()
    {
        double x; // 1st draw
        do 
        x=doubleRandom();
        while (x==0);
#ifdef M_PI
        double pi=M_PI;
#else
        double pi=3.1415926535897932384626433832795;
#endif
        return double(std::sqrt(-2*std::log(x))*std::cos(2*pi*doubleRandom()));
    }


    ///@}
}
