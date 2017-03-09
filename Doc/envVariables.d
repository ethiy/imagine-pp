/*! \page envVar Environment variables

  \section ev1 Introduction

  Environment variables are variables of the system, whose values are character strings. They are used mostly to indicate paths or preferences. In particular, the variable <tt>PATH</tt> indicates where to look when you launch an application from the command line (and also to find dynamic libraries, files with extension .dll, under Windows). <tt>PATH</tt> is thus a list of folders.

The other important variable concerning Imagine++ is <tt>Imagine_DIR</tt>, indicating the full path of the Imagine++ installation folder. Unless you choose a non-standard install location, this variable is not necessary under MacOS.

  The variables relevant to Imagine++ are:
  - <tt>Imagine_DIR</tt>, where you should set the folder where you installed Imagine++ (automatically set by the Windows intaller, not necessary under MacOS if you installed in the proposed location)
  - <tt>CMAKE_PREFIX_PATH</tt> The location where to find Qt5. This is a folder ending in <tt>.../lib/cmake</tt>, such as <tt>/Users/pascal/Qt/5.7/clang64/lib/cmake</tt>. Inside QtCreator, you should not need this variable.
  - <tt>PATH</tt>, where you should set the <tt>bin</tt> folder of Qt. If the variable already had a value, separate with a semicolon (;).

A portable way to deal with environment variables from QtCreator is the following:
  \image html qtcreatorSetenv.png "From the \"Projects\" tab on the left, you can view/change/add the environment variables.

However, this is only valid for the project at hand, to make it permanent, read on.

  \section ev2 Setting variables under Linux and MacOS

  In a terminal, the command <tt>env</tt> lists all known environment variables. To see the value of a variable, use <tt>echo $Imagine_DIR</tt>. If nothing is written, that means the variable <tt>Imagine_DIR</tt> is not set.

  To set <em>temporarily</em> a variable, use the command
\code
export Imagine_DIR=/usr/share/Imagine++
\endcode
This value will be valid only for programs launched from this terminal. Other terminals will ignore it, as well as programs launched from the graphical environment.
    - Linux:
To set it <em>permanently</em> starting from next login, write the file <tt>~/.pam_environment</tt>:
\code
echo "Imagine_DIR DEFAULT=/usr/share/Imagine++" >> $HOME/.pam_environment
\endcode
  This will suffice for all programs launched from the graphical environment after next login.
    - MacOS:
There is no reliable way to set the variables permanently across all OS versions, but the following works until you log out or reboot:
\code
launchctl setenv CMAKE_PREFIX_PATH /Users/pascal/Qt/5.7/clang64/lib/cmake
\endcode
(useful if CMake complains about finding Qt5)

  \section ev3 Setting variables under Windows

  In the Windows menu, right click on 'Computer' and select 'Properties' from the menu. In the left pane, click 'Advanced system settings' and press the button 'Environment Variables' in the new window. In the dialog, there are 'User variables', which you can set at will, and 'System variables' reserved for administrator.
  \image html envVar.png "Editing an environment variable"

  You can check the values by opening a command window (<tt>cmd.exe</tt>) and launching the command <tt>set</tt>.

*/
