# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

set(ImagineImages_MainHead Imagine/Images.h) 
set(ImagineImages_Headers 
    Imagine/Images/Border.h
    Imagine/Images/PixelTraits.h
    Imagine/Images/Interpol.h
    Imagine/Images/Image.h
    Imagine/Images/IO.h
    Imagine/Images/Algos.h
    Imagine/Images/Buffer.h
    Imagine/Images/AnalyzeHeader.h
    Imagine/Images/Analyze.h
    Imagine/Images/Schemes.h
   )
if(IMAGINE_INSTALL)
  install(FILES ${ImagineImages_MainHead} DESTINATION include/Imagine)
  install(FILES ${ImagineImages_Headers} DESTINATION include/Imagine/Images)
endif()
