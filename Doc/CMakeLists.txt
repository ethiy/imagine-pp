# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

cmake_minimum_required(VERSION 2.6)

project(Doc)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in
                   ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/mainpage.d.in
                   ${CMAKE_CURRENT_BINARY_DIR}/mainpage.d @ONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/installLinux.d.in
                   ${CMAKE_CURRENT_BINARY_DIR}/installLinux.d @ONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/installMacOS.d.in
                   ${CMAKE_CURRENT_BINARY_DIR}/installMacOS.d @ONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/installWindows.d.in
                   ${CMAKE_CURRENT_BINARY_DIR}/installWindows.d @ONLY)
    add_custom_target(doc
                      ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                      COMMENT "Generating API doc with Doxygen" VERBATIM)
    # Find qhelpgenerator
    find_program(QHELPGENERATOR qhelpgenerator)
    if(QHELPGENERATOR)
        set(qch_file "html/Imagine.qch")
        add_custom_target(doc-qt
                          COMMAND
                              ${QHELPGENERATOR} html/index.qhp -o "${qch_file}"
                          DEPENDS doc COMMENT "Creating Qt compressed help")
    endif()
endif()

if(IMAGINE_INSTALL)
    file(GLOB alldoc ${Doc_BINARY_DIR}/html/*)
    install(FILES ${alldoc} DESTINATION doc/html)
endif()
