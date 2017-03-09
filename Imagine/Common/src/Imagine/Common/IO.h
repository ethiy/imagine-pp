// ===========================================================================
// Imagine++ Libraries
// Copyright (C) Imagine
// For detailed information: http://imagine.enpc.fr/software
// ===========================================================================

namespace Imagine {
    /// \addtogroup Common
    /// @{

    /// Pause in program execution until key press.
    /// \param message the message to display: (use "") to display nothing
    inline void waitKey(const char* message="Press <enter> to continue...") {
        std::cout << message << std::flush;
        std::getchar();
    }

    /// Object loading.
    /// Loads an object from a given file in ASCII format (operator>>() must be implemented)
    /// \param obj object to load
    /// \param filename file name
    /// \return false if failed
    ///
    /// \dontinclude Common/test/test.cpp \skip io()
    /// \skipline object to save
    /// \until load object (binary)
    template <typename T>
    bool loadText(T& obj, std::string filename) {
        std::ifstream in(filename.c_str(), std::ios::in);
        if (!in.is_open())  {
            std::cerr << "Error: failed to open file '" << filename << "' for reading" << std::endl;
            return false;
        }
        in >> obj;
        return (!in.fail());
    }
    /// Object loading.
    /// Loads an object from a given file in binary format (read() must be implemented)
    /// \param obj object to load
    /// \param filename file name
    /// \return false if failed
    ///
    /// \dontinclude Common/test/test.cpp \skip io()
    /// \skipline object to save
    /// \until load object (binary)
    template <typename T>
    bool loadBinary(T& obj, std::string filename) {
        std::ifstream in(filename.c_str(), std::ios::in|std::ios::binary);
        if (!in.is_open())  {
            std::cerr << "Error: failed to open file '" << filename << "' for reading" << std::endl;
            return false;
        }
        read(in,obj);
        return (!in.fail());
    }
    /// Object saving.
    /// Saves an object from a given file in ASCII format (operator<<() must be implemented)
    /// \param obj object to save
    /// \param filename file name
    /// \param precision for ASCII output
    /// \return false if failed
    ///
    /// \dontinclude Common/test/test.cpp \skip io()
    /// \skipline object to save
    /// \until load object (binary)
    template <typename T>
    bool saveText(const T& obj, std::string filename, int precision=-1) {
        std::ofstream out(filename.c_str(), std::ios::out);
        if (!out.is_open()) {
            std::cerr << "Error: failed to open file '" << filename << "' for writing" << std::endl;
            return false;
        }
        if (precision>=0)
            out.precision(precision);
        out << obj;
        return (!out.fail());
    }
    /// Object saving.
    /// Saves an object from a given file in binary format (write must be implemented)
    /// \param obj object to save
    /// \param filename file name
    /// \return false if failed
    ///
    /// \dontinclude Common/test/test.cpp \skip io()
    /// \skipline object to save
    /// \until load object (binary)
    template <typename T>
    bool saveBinary(const T& obj, std::string filename) {
        std::ofstream out(filename.c_str(), std::ios::out|std::ios::binary);
        if (!out.is_open()) {
            std::cerr << "Error: failed to open file '" << filename << "' for writing" << std::endl;
            return false;
        }
        write(out,obj);
        return (!out.fail());
    }

    ///@}
}
