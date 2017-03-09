/*! \page trouble Troubleshooting

  \section ts1 Installation

  - <b>The doc directory is not included in the archive Imagine++-...tar.gz even though I built the doc explicitly.</b> This happens on Windows. In the build directory, remove the folder _CPack_Packages and the file CPackConfig.cmake. Go back to cmake to regenerate the project (in the same build directory). In Visual, rebuild the doc (right-clicking on the doc project in the 'Solution Explorer' window). Rebuild the package (project 'PACKAGE'). The doc directory and its content should now be in the archive.

  - <b>When building from source Imagine++, <tt>make doc-qt</tt> results in an error.</b> This the case with Ubuntu 14.04 and Qt5. The bug is caused by the Qt5 package not providing <tt>qhelpgenerator</tt>. A correction:
  \code
  sudo apt-get install qt4-dev-tools
  cd /usr/lib/x86_64-linux-gnu/
  sudo ln -s /usr/lib/x86_64-linux-gnu/qt4/bin/qhelpgenerator qt5/bin/
  \endcode

  - <b>Under MacOS, CMake complains it does not find the compiler, even though XCode is installed.</b> The gcc compiler is not in the standard path. To remedy this, enter the following in a terminal:
  \code
  sudo /usr/bin/xcode-select -switch /Applications/Xcode.app/Contents/Developer
  \endcode 

  \section ts2 Compilation

  - <b>On Windows, Qt Creator signals an error "The C compiler is not able to compile a simple test program"</b>. It you get something like:
  \image html qtbugfrench.png
you are hit by a bug where Qt Creator in French chooses a build directory containing an accent (<tt>D&eacute;faut</tt>) and then has some encoding problem, as seen in the image above. The solution is to change the build directory to a name containing no special character, like simply <tt>build</tt> (configurable in mode <tt>Projets</tt>). 

  - <b>Cmake signals an error 'Could not find module FindImagine.cmake or a configuration file for package %Imagine'.</b> It is due to a missing or erroneous Imagine_DIR environment variable. This should be set to the installation path of Imagine++ (it is <b>not</b> the source directory of Imagine++, if you have it). For example, here is a good configuration under Windows:
  \image html env.png "A correct configuration of Imagine_DIR under Windows"

  - <b>Cmake complains with the following message</b>
\code
CMake Warning at ThirdParty/Qt5/CMakeLists.txt:6 (FIND_PACKAGE):
  By not providing "FindQt5Core.cmake" in CMAKE_MODULE_PATH this project has
  asked CMake to find a package configuration file provided by "Qt5Core", but
  CMake did not find one.
\endcode
CMake does not find Qt. To fix it, you can set the environment variable CMAKE_PREFIX_PATH to a correct path, like (under Mac):
\code
env CMAKE_PREFIX_PATH=/Users/pascal/Qt/5.3/clang_64/lib/cmake cmake .
\endcode
and reboot.

  \section ts3 Usage

  - <b>The build of my program went well but when I execute it, it complains about something related to Qt.</b> This happens on Windows in Release mode. First, the location of Qt's dynamic libraries (where the dll files are stored) must be in the 'path' environment variable.
  \image html conflictqt.png "Error related to Qt at execution time."
  However, the final 'path' environment variable is a concatenation of the system variable and the user variable (unlike regular environment variables, for which the user variable overrides the system variable). In the image above, the path to Qt is in the user variable. However, some Qt libraries are used by MiKTeX (Latex program) and the path to MiKTeX is in the system variable. As witnessed by Visual's output, this is the problem:
  \image html conflictqt2.png "Conflicting Qt dynamic libraries"
  When it looks for QtOpenGL4.dll, it is present only in the correct location, so it finds it there as it should. However, the required QtGui4.dll is also present in MiKTeX's directory, and built from another minor version of Qt. The solution is to prevent it from looking in the MiKTeX directory:
       - A permanent solution is to add the Qt path in the system 'path' variable, before MiKTeX. However, you need administrator rights to do that.
       - Alternatively, you can copy the correct Qt dll files in the Release directory of your build (where your exe file is located). You have to do that for every Imagine++ program that you want to run in Release mode.
       - The least convenient solution is to launch the program from a terminal window where you have modified the 'path' environment variable. This only affects the current terminal.

  - <b>My program using the Graphics module complains with my main function 'int main(int argc, char** argv)'.</b> This definition of the main function is correct in C++, though perhaps less frequent than the also correct 'int main()'. The idea is to get arguments of the program at execution, if any. You are using an outdated version of Imagine++, you need to upgrade to a more recent version to fix this problem.

*/
