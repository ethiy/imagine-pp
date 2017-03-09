# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

if(NOT Imagine_FOUND)

set(Imagine_FOUND true)

cmake_policy(VERSION 2.8.11)

# Path
macro(AddCMakePath _dir)
    file(TO_CMAKE_PATH "$ENV{IMAGINEPP_SRC}" c)
    set(p "${c}/${_dir}" ${CMAKE_MODULE_PATH})
    list(REMOVE_DUPLICATES p)
    set(CMAKE_MODULE_PATH ${p})
endmacro()

# Setting an env. variable ((i) in batch files (ii) into CMake (iii) into installer)
macro(SetEnv _var _dir _sub _inst)
	if(${_inst}) 
		if(WIN32)
			if("${_sub}" STREQUAL "") 
				set(_nsub "")
			else() 
				string(REPLACE "/" "\\\\" _nsub /${_sub})
			endif() 
			file(APPEND ${CMAKE_BINARY_DIR}/extra_install.nsi "
				Push ${_var}
				Push \\\"$INSTDIR${_nsub}\\\"
				Call AddEnvVar
			")
			file(APPEND ${CMAKE_BINARY_DIR}/extra_uninstall.nsi "
				Push ${_var}
				Call un.DeleteEnvVar
			")
		else()
			if(NOT ${_var} STREQUAL Imagine_DIR)
				ExportVar(usr_environment ${_var} \$Imagine_DIR/${_sub})
			endif()
		endif()
	endif() 

	set(ENV{${_var}} ${_dir}/${_sub})
	if(WIN32)
		file(TO_NATIVE_PATH "${_dir}/${_sub}" _fd)
		file(APPEND ${CMAKE_BINARY_DIR}/devel_env.bat "set ${_var}=${_fd}\n")
	else()
		ExportVar(devel_environment ${_var} ${_dir}/${_sub})
	endif()
endmacro()

# Visual defs
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_DEPRECATE
                    -D_SCL_SECURE_NO_WARNINGS
		    -DNOMINMAX)
endif()

# Properties
macro(ImagineAppendProperty _targ _prop _val)
	get_target_property(tmp ${_targ} ${_prop})
	if(tmp)
		set_target_properties(${_targ} PROPERTIES ${_prop} "${tmp} ${_val}")
	else()
		set_target_properties(${_targ} PROPERTIES ${_prop} "${_val}")
	endif()
endmacro()

macro(ImagineAddLinkFlag _proj _f)
	if(MSVC)
		ImagineAppendProperty(${_proj} LINK_FLAGS /LIBPATH:"${_f}")
	else()
		ImagineAppendProperty(${_proj} LINK_FLAGS -L"${_f}")
	endif()
endmacro()

macro(ImagineAddLinkPath _proj _path)
	foreach(_dir ${_path})
		ImagineAddLinkFlag(${_proj} "${_dir}")
	endforeach()
endmacro()

# Batches to be called before running Visual
if(WIN32)
	file(WRITE ${CMAKE_BINARY_DIR}/launch_visual.bat
"@echo off
IF EXIST \"devel_env.bat\" GOTO ok
echo Use this launcher only when a devel_env.bat file has been created
pause
goto done
:ok
call devel_env.bat
IF EXIST \"%VS120COMNTOOLS%\\..\\IDE\\WDExpress.exe\" GOTO vcexpress12
IF EXIST \"%VS100COMNTOOLS%\\..\\IDE\\devenv.exe\" GOTO visual10
IF EXIST \"%VS100COMNTOOLS%\\..\\IDE\\vcexpress.exe\" GOTO vcexpress10
IF EXIST \"%VS90COMNTOOLS%\\..\\IDE\\devenv.exe\" GOTO visual9
IF EXIST \"%VS90COMNTOOLS%\\..\\IDE\\vcexpress.exe\" GOTO vcexpress9
IF EXIST \"%VS80COMNTOOLS%\\..\\IDE\\devenv.exe\" GOTO visual8
IF EXIST \"%VS80COMNTOOLS%\\..\\IDE\\vcexpress.exe\" GOTO vcexpress8
echo Cannot find visual
pause
goto done
:vcexpress8
\"%VS80COMNTOOLS%\\..\\IDE\\vcexpress\" ${PROJECT_NAME}.sln
goto done
:visual8
\"%VS80COMNTOOLS%\\..\\IDE\\devenv\" ${PROJECT_NAME}.sln
goto done
:vcexpress9
\"%VS90COMNTOOLS%\\..\\IDE\\vcexpress\" ${PROJECT_NAME}.sln
goto done
:visual9
\"%VS90COMNTOOLS%\\..\\IDE\\devenv\" ${PROJECT_NAME}.sln
goto done
:vcexpress10
\"%VS100COMNTOOLS%\\..\\IDE\\vcexpress\" ${PROJECT_NAME}.sln
goto done
:visual10
\"%VS100COMNTOOLS%\\..\\IDE\\devenv\" ${PROJECT_NAME}.sln
goto done
:visual12
\"%VS120COMNTOOLS%\\..\\IDE\\WDExpress\" ${PROJECT_NAME}.sln
goto done
:done
	")
	file(REMOVE ${CMAKE_BINARY_DIR}/devel_env.bat )
	file(REMOVE ${CMAKE_BINARY_DIR}/extra_install.nsi )
	file(REMOVE ${CMAKE_BINARY_DIR}/extra_uninstall.nsi )
else()
	file(REMOVE ${CMAKE_BINARY_DIR}/devel_environment.sh)
	file(WRITE ${CMAKE_BINARY_DIR}/devel_environment.tcsh "if ( ! $?LD_LIBRARY_PATH ) then\nsetenv LD_LIBRARY_PATH \"\"\nendif\n")
	file(REMOVE ${CMAKE_BINARY_DIR}/usr_environment.sh)
	file(WRITE ${CMAKE_BINARY_DIR}/usr_environment.tcsh "if ( ! $?LD_LIBRARY_PATH ) then\nsetenv LD_LIBRARY_PATH \"\"\nendif\n")
	macro(ExportVar _file _var _val)
		file(APPEND ${CMAKE_BINARY_DIR}/${_file}.sh "export ${_var}=${_val}\n")
		file(APPEND ${CMAKE_BINARY_DIR}/${_file}.tcsh "setenv ${_var} ${_val}\n")
	endmacro()
	macro(ExportPath _file _dir _mode)
		if(${_mode} MATCHES "^RUN")
			set(ENV{CMAKE_PROGRAM_PATH} "${_dir}" $ENV{CMAKE_PROGRAM_PATH})
			file(APPEND ${CMAKE_BINARY_DIR}/${_file}.sh "export PATH=${_dir}:\$PATH\n")
			file(APPEND ${CMAKE_BINARY_DIR}/${_file}.tcsh "set path = ( ${_dir} \$path )\n")
		endif()
		if(${_mode} MATCHES "LD$")
			if(APPLE)
				file(APPEND ${CMAKE_BINARY_DIR}/${_file}.sh "export DYLD_LIBRARY_PATH=${_dir}:\$DYLD_LIBRARY_PATH\n")
				file(APPEND ${CMAKE_BINARY_DIR}/${_file}.tcsh "setenv DYLD_LIBRARY_PATH ${_dir}:\$DYLD_LIBRARY_PATH\n")
			else()
				file(APPEND ${CMAKE_BINARY_DIR}/${_file}.sh "export LD_LIBRARY_PATH=${_dir}:\$LD_LIBRARY_PATH\n")
				file(APPEND ${CMAKE_BINARY_DIR}/${_file}.tcsh "setenv LD_LIBRARY_PATH ${_dir}:\$LD_LIBRARY_PATH\n")
			endif()
		endif()
	endmacro()
endif()

# Setting path ((i) in batch files (ii) into installer)
# _mode is "RUN" (exe) "LD" (dll) or "RUNLD" (both)
macro(SetPath _dir _sub _inst _mode)
	if(${_inst}) 
		if(WIN32)
				if("${_sub}" STREQUAL "") 
					set(_nsub "")
				else() 
					string(REPLACE "/" "\\\\" _nsub /${_sub})
				endif() 
				file(APPEND ${CMAKE_BINARY_DIR}/extra_install.nsi "
					Push \\\"$INSTDIR${_nsub}\\\"
					Call AddToPath
				")
				file(APPEND ${CMAKE_BINARY_DIR}/extra_uninstall.nsi "
					Push \\\"$INSTDIR${_nsub}\\\"
					Call un.RemoveFromPath
				")
		else()
			ExportPath(usr_environment \$Imagine_DIR/${_sub} ${_mode})
		endif()
	endif() 
	if(WIN32)
		file(TO_NATIVE_PATH "${_dir}/${_sub}" _fd)
		file(APPEND ${CMAKE_BINARY_DIR}/devel_env.bat "set path=${_fd};%path%\n")
	else()
		ExportPath(devel_environment ${_dir}/${_sub} ${_mode})
	endif()
endmacro()

### Main
#UseImagine
macro(ImagineAddSubDirectory _dir)
	get_property(already_included GLOBAL PROPERTY _IMAGINE_${_dir}_INCLUDED)
	if(NOT already_included)
		set_property(GLOBAL PROPERTY  _IMAGINE_${_dir}_INCLUDED 1)
		add_subdirectory(${_dir})
	endif()
endmacro()
macro(ImagineAddAbsDirectory _abs _dir)
	set(already_included "")
	get_property(already_included GLOBAL PROPERTY _IMAGINE_${_dir}_INCLUDED)
	if (NOT already_included)
		set_property(GLOBAL PROPERTY  _IMAGINE_${_dir}_INCLUDED 1)
		add_subdirectory("${_abs}" ${_dir})
	endif()
endmacro()

macro(ImagineSetModuleOption _proj _mod _opt)
	set(${_proj}_${_mod}_${_opt} true)
endmacro(ImagineSetModuleOption)

macro(ImagineAddModule _category _pkg)
    if(NOT EXISTS "$ENV{IMAGINEPP_SRC}")
		message(FATAL_ERROR "Set IMAGINEPP_SRC env. variable to use Imagine++ sources!")
	endif()
	if(EXISTS "$ENV{IMAGINEPP_SRC}/${_category}/${_pkg}/CMake")
		AddCMakePath("${_category}/${_pkg}/CMake")
		ImagineAddAbsDirectory("$ENV{IMAGINEPP_SRC}/${_category}/${_pkg}" ${_pkg})
	endif()
endmacro()

macro(ImagineUseModules _proj)
	foreach(_pkg ${ARGN})
		if(THIRDPARTY_FROM_SRC)
			ImagineAddModule(ThirdParty ${_pkg})
			ImagineAddModule(ThirdParty-labo ${_pkg})
		endif()
		if(IMAGINE_FROM_SRC)
			ImagineAddModule(Imagine ${_pkg})
			ImagineAddModule(Imagine-labo ${_pkg})
		endif()
		set(${_pkg}_Proj ${_proj} CACHE INTERNAL "") 
		include(UseImagine${_pkg})
	endforeach()
endmacro()

macro(ImaginePreLoadModules)
	ImagineUseModules("_PRELOAD_" ${ARGN})
endmacro()

# For backward compatibility, use rather ADD_EXECUTABLE directly
macro(ImagineAddExecutable _proj)
	add_executable(${_proj} ${ARGN})
endmacro()

if(EXISTS "$ENV{IMAGINEPP_SRC}")
    AddCMakePath("CMake")
endif()

if(NOT DEFINED ENV{Imagine_DIR})
    get_filename_component(p "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
    set(ENV{Imagine_DIR} "${p}")
    message(STATUS "Setting Imagine_DIR=" "$ENV{Imagine_DIR}")
endif()
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}")

endif()
