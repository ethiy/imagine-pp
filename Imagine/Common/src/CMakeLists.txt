# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

configure_file(Imagine/Common/Base.h.in
               ${CMAKE_CURRENT_SOURCE_DIR}/Imagine/Common/Base.h @ONLY)

if(IMAGINE_INSTALL)
    install(FILES Imagine/Common.h DESTINATION include/Imagine)
    install(FILES
            Imagine/Common/FArray.h
            Imagine/Common/FVector.h
            Imagine/Common/FMatrix.h
            Imagine/Common/Base.h
            Imagine/Common/Coords.h
            Imagine/Common/Array.h
            Imagine/Common/MultiArray.h
            Imagine/Common/Color.h
            Imagine/Common/Random.h
            Imagine/Common/IO.h
            Imagine/Common/Timer.h
            DESTINATION include/Imagine/Common)
endif()
