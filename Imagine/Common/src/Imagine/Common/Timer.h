// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

namespace Imagine {
    /// \addtogroup Common
    /// @{


    /// \headerfile Imagine/Common.h "Imagine/Common.h"
    /// Timers.
    /// Small timer class
    class Timer {
    private:
        double _start;
        static double time() {
#if _WIN32
            return double(std::clock())/CLOCKS_PER_SEC;
#else
            struct tms b;
            times(&b);
            return double(b.tms_utime)/sysconf(_SC_CLK_TCK);
#endif
        }
    public:
        /// Constructor.
        /// Constructs and start a timer
        /// 
        /// \dontinclude Common/test/test.cpp \skip timers()
        /// \skipline construct
        Timer() {
            reset();
        }
        /// Lap.
        /// Seconds since construction of latest reset()
        /// \return seconds
        ///
        /// \dontinclude Common/test/test.cpp \skip timers()
        /// \skipline construct
        /// \until seconds for code 3
        double lap() const {
            return Timer::time() - _start;
        }
        /// Reset.
        /// Reset timer
        ///
        /// \dontinclude Common/test/test.cpp \skip timers()
        /// \skipline reset
        void reset() {
            _start = Timer::time();
        }
    };

    ///@}
}
