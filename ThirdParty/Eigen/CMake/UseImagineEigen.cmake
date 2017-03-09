# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

if(NOT ImagineEigen_FOUND)
    set(ImagineEigen_FOUND true)
    file(TO_CMAKE_PATH "$ENV{Imagine_DIR}" d)
    include_directories("${d}/ThirdParty/Eigen")
endif()
