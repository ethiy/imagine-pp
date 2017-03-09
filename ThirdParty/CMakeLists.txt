# Imagine++ Libraries
# Copyright (C) Imagine
# For detailed information: http://imagine.enpc.fr/software

ImagineAddSubDirectory(Eigen)
ImagineAddSubDirectory(OpenGL)

if(NOT IMAGINE_FORCE_QT4)
	ImagineAddSubDirectory(Qt5)
else()
	ImagineAddSubDirectory(Qt4)
endif()
