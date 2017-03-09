// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

#include <stdarg.h>

// SPECIAL MACRO.
// The graphics thread has to be the main thread on some platforms (eg MacOS).
// Therefore, we have to play tricks to let the user believe it is in the main
// function, while her instructions are __main, running in a secondary thread.
// argc >= 1 & argv[0] = relative .exe path.
// __VA_ARGS__ catches ... (variadic macro).
int __main(int argc, char** argv);

#define main(...)                                          \
    main(int argc, char** argv) {                          \
        return Imagine::GraphicsThread(argc, argv).exec(); \
    }                                                      \
    int __main(int argc, char** argv)

namespace Imagine {
    /// \addtogroup Graphics
    /// @{

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    class GraphicsApplication; // Opaque class the user does not need to know
    class GraphicsThread { // Encapsulate the global application instance

    public:
        GraphicsThread(int& argc, char** argv);
        ~GraphicsThread();
        int exec();
    private:
        GraphicsApplication* app;
    };
#endif
    /// Terminate graphics application.
    /// If there is an open window, it waits for a mouse click before exiting.
    void endGraphics();
    /// @}
}
