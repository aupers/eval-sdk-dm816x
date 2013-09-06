#$L$
# Copyright (C) 2013 Ridgerun (http://www.ridgerun.com). 
##$L$

include ../../../bsp/classes/rrsdk.defs
include $(CLASSES)/cmake.class

# This app can safely compile using the host's python, this simplifies some 
# python libraries dependencies which are easily resolved using the host's 
# apt-get
PYTHON_HOST_EXECUTABLE=/usr/bin/python

CMAKE_PARAMS= \
	-DBUILD_DOCS=off \
	-DBUILD_EXAMPLES=off \
	-DBUILD_PACKAGE=off \
	-DBUILD_PYTHON_SUPPORT=off \
	-DBUILD_NEW_PYTHON_SUPPORT=off \
	-DBUILD_SHARED_LIBS=on \
	-DBUILD_TESTS=off \
	-DCMAKE_SKIP_RPATH=off \
	-DENABLE_PROFILING=off \
	-DINSTALL_C_EXAMPLES=off \
	-DINSTALL_PYTHON_EXAMPLES=off \
	-DOPENCV_BUILD_3RDPARTY_LIBS=off \
	-DUSE_FAST_MATH=on \
	-DUSE_OMIT_FRAME_POINTER=on \
	-DUSE_PRECOMPILED_HEADERS=off \
	-DWITH_1394=off \
	-DWITH_CUDA=off \
	-DWITH_FFMPEG=off \
	-DWITH_GSTREAMER=off \
	-DWITH_GTK=off \
	-DWITH_IPP=off \
	-DWITH_JASPER=off \
	-DWITH_JPEG=off \
	-DWITH_OPENEXR=off \
	-DWITH_OPENNI=off \
	-DWITH_PNG=off \
	-DWITH_PVAPI=off \
	-DWITH_QT=off \
	-DWITH_QT_OPENGL=off \
	-DWITH_TBB=off \
	-DWITH_TIFF=off \
	-DWITH_UNICAP=off \
	-DWITH_V4L=off \
	-DWITH_XIMEA=off \
	-DWITH_XINE=off \
	-DPYTHON_EXECUTABLE=$(PYTHON_HOST_EXECUTABLE)

PKG_URL=http://sourceforge.net/projects/opencvlibrary/files/opencv-unix/2.3.1/
PKG_TARBALL=OpenCV-2.3.1a.tar.bz2
PKG_SHA1SUM=9784e6824c5f677fac82ae83a2f366743adb3299

LIBRARIES=  /usr/lib/libopencv_calib3d.so.2.3.1 \
            /usr/lib/libopencv_contrib.so.2.3.1 \
            /usr/lib/libopencv_core.so.2.3.1 \
            /usr/lib/libopencv_features2d.so.2.3.1 \
            /usr/lib/libopencv_flann.so.2.3.1 \
            /usr/lib/libopencv_gpu.so.2.3.1 \
            /usr/lib/libopencv_highgui.so.2.3.1 \
            /usr/lib/libopencv_imgproc.so.2.3.1 \
            /usr/lib/libopencv_legacy.so.2.3.1 \
            /usr/lib/libopencv_ml.so.2.3.1 \
            /usr/lib/libopencv_objdetect.so.2.3.1 \
            /usr/lib/libopencv_video.so.2.3.1

