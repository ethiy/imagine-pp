# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

cmake_minimum_required(VERSION 2.6)

set(IMAGINEPP_VERSION "4.3.1")

# Do not uncomment unless manual build (set from scripts)
# set(LABO_VERSION 1)

if(LABO_VERSION)
	project(Imagine++-labo)
else()
	project(Imagine++)
endif()

include(CMake/ImagineConfig.cmake)

SetEnv(Imagine_DIR   ${CMAKE_CURRENT_SOURCE_DIR} "" 1)
SetEnv(IMAGINEPP_SRC ${CMAKE_CURRENT_SOURCE_DIR} "" 0)

if(LABO_VERSION)
	set(THIRDPARTY_FULL_INSTALL 1)
	set(IMAGINE_INSTALL 0)
else()
	set(THIRDPARTY_FULL_INSTALL 0)
	set(IMAGINE_INSTALL 1)
endif()

set(IMAGINE_FROM_SRC 1)
set(THIRDPARTY_FROM_SRC 1)

# Using Qt 5.7 requires a C++11 compiler
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR
   CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "-std=c++11")
endif()

# Options
set(IMAGINE_FORCE_QT4 OFF CACHE BOOL
    "Check this if you want to use Qt4 even though Qt5 is installed")
set(IMAGINE_OPENGL ON CACHE BOOL "Enable 3D support.")

# The modules
add_subdirectory(ThirdParty)
add_subdirectory(Imagine)
if(LABO_VERSION)
	add_subdirectory(ThirdParty-labo)
	add_subdirectory(Imagine-labo)
endif()
add_subdirectory(Doc)

# Package
install(FILES CMake/ImagineConfig.cmake DESTINATION CMake)
install(FILES Test/CMakeLists.txt DESTINATION test)
if(CMAKE_HOST_APPLE)
	install(FILES CMake/mkFramework.sh DESTINATION .)
endif()

# CPACK Macro
macro(SetPack _name _ver _legal)
	# For "make package_source", ignore binary dir if inside source tree
	set(CPACK_SOURCE_IGNORE_FILES "/.svn/;.*~")
	if(NOT CMAKE_BINARY_DIR STREQUAL ${CMAKE_SOURCE_DIR})
		list(APPEND CPACK_SOURCE_IGNORE_FILES "${CMAKE_BINARY_DIR}/*")
	endif()
	set(CPACK_MONOLITHIC_INSTALL 1)
	set(CPACK_RESOURCE_FILE_LICENSE "${_legal}/license.txt")
	set(CPACK_PACKAGE_VENDOR "Imagine")
	set(CPACK_PACKAGE_VERSION ${_ver})
	if(${ARGC} EQUAL 4)
		# Force user to choose install dir 
		set(CPACK_PACKAGE_INSTALL_DIRECTORY "")
	else()
		set(CPACK_PACKAGE_INSTALL_DIRECTORY ${_name})
	endif()
	set(CPACK_PROJECT_CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/CMake/CPackOptions.cmake")
	if(WIN32)
		set(_syst win)
		if(CMAKE_CL_64)
			set(_syst ${_syst}_x64)
		else()
			set(_syst ${_syst}_x86)
		endif()
		# Checks compiler
		if(MSVC70)
			set(_syst ${_syst}_msvc2002)
		elseif(MSVC71)
			set(_syst ${_syst}_msvc2003)
		elseif(MSVC80)
			set(_syst ${_syst}_msvc2005)
		elseif(MSVC90)
			set(_syst ${_syst}_msvc2008)
		elseif(MSVC10)
			set(_syst ${_syst}_msvc2010)
		elseif(MSVC11)
			set(_syst ${_syst}_msvc2012)
		elseif(MSVC12)
			set(_syst ${_syst}_msvc2013)
		elseif(MSVC14)
			set(_syst ${_syst}_msvc2015)
		else()
			set(_syst ${_syst}_minGW)
		endif()
	else()
		set(_syst ${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR})
	endif()
	set(CPACK_PACKAGE_FILE_NAME "${_name}-${_ver}-${_syst}")
	set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Imagine++ libraries")

	set(CPACK_PACKAGE_ICON ${_legal}\\\\Imagine.bmp)
	if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
		list(APPEND CPACK_GENERATOR "DEB")
	endif()
	if(WIN32)
		set(CPACK_GENERATOR "ZIP")
        list(APPEND CPACK_GENERATOR "NSIS")
		set(CPACK_NSIS_MUI_ICON ${_legal}/Install.ico)
		set(CPACK_NSIS_MUI_UNIICON ${_legal}/Install.ico)
		set(CPACK_NSIS_MODIFY_PATH "OFF")
		set(CPACK_NSIS_COMPRESSOR "/FINAL /SOLID zlib") # Fast
		if(EXISTS ${CMAKE_BINARY_DIR}/extra_install.nsi)
			file(READ ${CMAKE_BINARY_DIR}/extra_install.nsi CPACK_NSIS_EXTRA_INSTALL_COMMANDS)
			file(READ ${CMAKE_BINARY_DIR}/extra_uninstall.nsi CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS)
		endif()
	endif()
	include(CPack)
endmacro()

set(CPACK_GENERATOR "TGZ")
set(CPACK_SOURCE_GENERATOR "TGZ")
SetPack(${CMAKE_PROJECT_NAME} ${IMAGINEPP_VERSION}
        "${CMAKE_CURRENT_SOURCE_DIR}/Legal")

# **Architecture for a module:**
# For a module of name Module:
# 1. Put in folder ThirdParty, Imagine, ThirdParty-labo or Imagine-labo a
# subfolder of name Module. Update the CMakeLists.txt.
# 2. Directory tree:
# Module/
#  |- CMakeLists.txt
#  |- CMake/
#  |   |- UseImagineModule.cmake
#  |- src/
#  |   |- CMakeLists.txt
#  |   |- *.cpp, *.h (private interface)
#  |   |- Imagine/
#  |   |   |- Module.h
#  |   |   |- Module/
#  |   |   |   |- *.h (public interface)
#  |- test/
#  |   |- CMakeLists.txt
#  |   |- *.cpp, data...
