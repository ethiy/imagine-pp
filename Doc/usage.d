/*! \page usage Usage

  \section us1 Using CMake

  CMake philosophy is the following:
  - your sources are in a directory containing a platform independent \c CMakeLists.txt configuration file describing your programs, the files from which they are built and the libraries they rely on (the source directory).
  - from this file, CMake creates, in some build directory you specify, all the files needed by your own system and your own development environment to compile your programs.
  - you can generate projects for Visual Studio on Windows, XCode on MacOS, Code::Blocks on all platforms... Some development environments, such as Kdevelop (Linux) and QtCreator (all platforms) know natively CMake, and you do not need to launch the cmake progam before.
  - it is a good idea to have separate source and build directories: you do not pollute your source directory with numerous temporary files needed for build.
  - this process is done once and for all. Even further modifications of \c CMakeLists.txt are handled automatically by the build process.

  The <tt>'test'</tt> sub-directory of the Imagine++ installation directory contains useful examples of such files. As an example, let's compile the Graphics tests.

The \c CMakeLists.txt (\c \<Imagine_DIR\>/test/Graphics/CMakeLists.txt) file of the Graphics test is simple, and your own should follow this model:

\dontinclude Graphics/test/CMakeLists.txt
\skipline project
\until ImagineGraphicsTest Graphics

Two executables are defined, \c ImagineGraphicsExample and \c ImagineGraphicsTest, built respectively from \c example.cpp and \c tesp.cpp, each of them using the Graphics module. The first few lines are mandatory for any Imagine++ project: they check the \c Imagine_DIR environment variable, which is mandatory to use Imagine++ (see \ref ev1).

Finally, if an executable depends on more than one C++ source, just add them as arguments to \c add_executable separated by whitespace. See other tests and refer to CMake own manual for further information.

  \section us2 QtCreator (all platforms)
QtCreator works on all platforms
    - launch \c QtCreator. Under Windows, it may complain about some problem related to OpenGL. It is happens, launch from a terminal:
    \code
      c:\Qt\Tools\QtCreator\bin\qtcreator.exe -noload Welcome
    \endcode
    - launch menu <tt>File/Open file or project...</tt>. Choose the file <tt>\<Imagine_DIR\>/test/Graphics/CMakeLists.txt</tt>
    \image html qtcreator1.png "Choose your build directory, click \c Next"
    \image html qtcreator2.png "Set arguments as above to be able to debug the programs. Click button 'Run CMake', then \c Finish.
    \image html qtcreator3.png "Build (hammer button), select program to launch (button \c all) and launch (green arrow)"
    \image html qtcreator4.png "The text output of the program is displayed in QtCreator"
    \image html qtcreator5.png "To launch from a terminal instead, go to \c Projects, select \c Run and click 'Run in terminal'. You must do that if your program expects user text input."
    \image html qtcreator6.png "The green button with a ladybug launches the debugger. Set breakpoints , run line by line, observe variables..."

  \section us3 Visual Studio (Windows)
To use under Windows:
    - launch \c cmake-gui from the menus
    - choose <tt>'C:/Program Files/Imagine++/test/Graphics'</tt> (or equivalent) as the source code directory
    - choose <tt>'C:/Users/</tt>\em login<tt>/Desktop/test'</tt> or any temporary directory as the build directory
    - generate. When asked, choose <tt>'Visual Studio 2013'</tt> as build system.
    \image html usage1.png "When the indicated build directory does not exist, the 'Configure' button proposes to create it."
    \image html usage2.png "Choose the correct generator for your project, here Visual 2013 in 32 bits."
    \image html usage3.png "A correct configuration after clicking 'Generate'"
    - you may now run Visual on the \c ImagineGraphicsTests.sln solution freshly created in your build directory
    \image html usage4.png "The solution file is created in the build directory. After that, Cmake can be closed."
    - note that several entries are defined under your Visual solution (\c ALL_BUILD, \c INSTALL, ...). These are for advanced usage. Don't forget to right-click on your own executable and 'Set as StartUp Project'
    \image html usage5.png "Define your execution project through a right-click on the project"
    \image html usage6.png "Running the project 'ImagineGraphicsTest' (key F5)"

    \section us4 From a terminal (all platforms)
    - run CMake GUI, and select a generator, 'Unix makefiles' for Linux and MacOS, 'MinGW Makefiles' for Windows. To install cmake-gui under Debian or derivative:
    \code
    sudo apt-get install cmake-qt-gui
    \endcode
    Notice it is in the Universe part of Ubuntu, which may not be activated by default.
    - you may now run <tt>make</tt> (Linux/Mac) or <tt>mingw32-make</tt> (Windows) in your build directory to compile your project.
    - under Mac, it may complain about not finding Qt. This is fixed by the command
\code
PATH=$HOME/Qt/5.3/clang_64/bin:$PATH
\endcode
    - important notes:
        - while being under cmake-gui, you may change build type to \c Debug (for use with a debugger) or \c Release to generate optmized programs (default is neither \c Release nor \c Debug). <b>For some applications, the Release executable can be much faster.</b>
        - you can use \c cmake instead of \c cmake-gui as a command line version. Try also ccmake (non graphic version under Linux/Mac) to change build type:
        \code
        cmake /path/to/source
        ccmake .
        [change CMAKE_BUILD_TYPE to Release, press [g], quit [q]]
        make
        \endcode

*/
