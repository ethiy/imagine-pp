/*! \page labo_usage Labo usage

  This page is dedicated to users who have access to Imagine++ SubVersion repository. It explains how to use Imagine++ libraries directly from a local copy of the repository, without installing them. 

  \section lu1 Using Imagine++ from SVN tree

  Follow this steps:
  - Checkout SVN repository <tt>svn+ssh://login\@imagine2.enpc.fr/svnroot/Programs/ImaginePlusPlus</tt>
  - Set an environment variable <tt>IMAGINEPP_SRC</tt> pointing to the downladed directory.
 	- Under Windows, this is in <tt>Computer/Properties/Advanced System Properties/Environment Variables</tt> 
	- Under linux, edit your Shell configuration file (see \ref install_linux)
  - Install third parties
 	- Under Windows, use the installer under <tt>www-labo</tt>
       		- Visual 2008 32bits: <tt>Imagine++-labo-3.2.2-win32_vc9.exe</tt>
       		- Visual 2008 64bits: <tt>Imagine++-labo-3.2.2-win64_vc9.exe</tt>
       		- Visual 2010 32bits: <tt>Imagine++-labo-3.2.2-win32_vc10.exe</tt>
       		- Visual 2010 64bits: <tt>Imagine++-labo-3.2.2-win64_vc10.exe</tt>
	- Under Linux, use scripts in <tt>Scripts-labo</tt> to make (i) third parties, (ii) doc and (iii) Imagine++. Install the resulting tarball somewhere and set an environment variable <tt>Imagine_DIR</tt> pointing to it.
  - You may now compile programs using the installed third parties and the <tt>%Imagine</tt> part if the SVN tree.
	- Directory <tt>FromSrcTest</tt> contains a sample. Look at its <tt>CMakeLists.txt</tt>: you just have add a <tt>SET(IMAGINE_FROM_SRC 1)</tt>compared to a standard \c CMakeLists.txt.
	- Note that each Imagine++ module you use will include its own tests and samples, since you might modify these modules for your own needs.

  \section lu2 Compiling third parties

  Well, if you're under linux, you've just done it. Under Windows, do the same: use scripts under \c Scripts-labo directory.

  \section lu3 Modifying public content

  Feel free to add functions, etc. but <b>each addition must be</b>:
  - used in the related test program
  - documented (doxygen style with an inclusion of the corresponding line in the test program)

  If your addition relies on a new file from a third party library (e.g. other MKL functions, ...), check that
  this file is installed in the public version of this library (see \c THIRDPARTY_FULL_INSTALL variable in third party \c CMakeLists.txt files)  

 \section lu4 Testing without installing

  - Compile third parties
  - Instead of making an installer with the \c makeImagine++ script, launch \c CMake on the \c Imagine++ main directory, setting \c LABO_VERSION to 1 in the main \c CMakeLists.txt file. 
  - You should now modify your environment to point to non installed third parties. To do so, in your build directory:
  	- Under Windows, run Visual indirectly with \c launch_visual.bat.
	- Under Linux, source \c devel_environment.(tc)sh before running make.

 \section lu5 Adding a new labo module

 Copy the way Features is added. Don't forget to add your module to <tt>Doc/Doxyfile-labo</tt>

 \section lu6 Turning a labo module into a public one

 Moving it from Imagine-labo to \c %Imagine should be enough. Please also update:
 - Doc/Doxyfile
 - your module specific \c .cmake file, that might contain some \c Imagine-labo here and then

 \section lu7 Changing Imagine++ version

 Use change-version.sh script. Rename SVN files in www and www-labo dirs. Rebuild doc (for links), sources, wizards, installers, ...

*/
