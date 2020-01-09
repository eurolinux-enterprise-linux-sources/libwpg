if PLATFORM_WIN32
no_undefined = -no-undefined
version_info = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) -avoid-version
else
no_undefined =
version_info = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)
endif

if OS_WIN32
install-libtool-import-lib:
	$(INSTALL) @WPG_OBJDIR@/libwpg-@WPG_MAJOR_VERSION@.@WPG_MINOR_VERSION@.dll.a $(DESTDIR)$(libdir)
	$(INSTALL) @WPG_OBJDIR@/libwpg-stream-@WPG_MAJOR_VERSION@.@WPG_MINOR_VERSION@.dll.a $(DESTDIR)$(libdir)

uninstall-libtool-import-lib:
	-rm $(DESTDIR)$(libdir)/libwpg-@WPG_MAJOR_VERSION@.@WPG_MINOR_VERSION@.dll.a
	-rm $(DESTDIR)$(libdir)/libwpg-stream-@WPG_MAJOR_VERSION@.@WPG_MINOR_VERSION@.dll.a

else
install-libtool-import-lib:
uninstall-libtool-import-lib:
endif

if WITH_LIBWPG_STREAM
target_libwpg_stream = libwpg-stream-@WPG_MAJOR_VERSION@.@WPG_MINOR_VERSION@.la
else
target_libwpg_stream =
endif

lib_LTLIBRARIES = libwpg-@WPG_MAJOR_VERSION@.@WPG_MINOR_VERSION@.la $(target_libwpg_stream)
libwpg_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_includedir = $(includedir)/libwpg-@WPG_MAJOR_VERSION@.@WPG_MINOR_VERSION@/libwpg
libwpg_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_include_HEADERS = \
	libwpg.h \
	WPGraphics.h \
	WPGColor.h \
	WPGPen.h \
	WPGBrush.h \
	WPGGradient.h \
	WPGPoint.h \
	WPGRect.h \
	WPGPath.h \
	WPGString.h \
	WPGBitmap.h \
	WPGBinaryData.h \
	WPGPaintInterface.h

AM_CXXFLAGS = $(LIBWPG_CXXFLAGS) $(DEBUG_CXXFLAGS)

libwpg_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_la_LIBADD  = @LIBWPG_WIN32_RESOURCE@
libwpg_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_la_DEPENDENCIES = @LIBWPG_WIN32_RESOURCE@
libwpg_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_la_LDFLAGS = $(version_info) -export-dynamic $(no_undefined)
libwpg_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_la_SOURCES = \
	WPGraphics.cpp \
	WPGBrush.cpp \
	WPGPen.cpp \
	WPGColor.cpp \
	WPGGradient.cpp \
	WPGPoint.cpp \
	WPGPath.cpp \
	WPGRect.cpp \
	WPGHeader.cpp \
	WPGSVGGenerator.cpp \
	WPGXParser.cpp \
	WPG1Parser.cpp \
	WPG2Parser.cpp \
	WPGBitmap.cpp \
	WPGBinaryData.cpp \
	WPGInternalStream.cpp \
	WPGString.cpp \
	libwpg.h \
	libwpg_utils.h \
	WPGColor.h \
	WPGPen.h \
	WPGBrush.h \
	WPGPath.h \
	WPGGradient.h \
	WPGHeader.h \
	WPGSVGGenerator.h \
	WPGXParser.h \
	WPG1Parser.h \
	WPG2Parser.h \
	WPGBitmap.h \
	WPGInternalStream.h\
	WPGPaintInterface.h

libwpg_stream_headers = WPGStreamImplementation.h
libwpg_stream_sources = \
	WPGOLEStream.cpp \
	WPGStreamImplementation.cpp \
	WPGOLEStream.h

if WITH_LIBWPG_STREAM

libwpg_stream_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_includedir = $(includedir)/libwpg-@WPG_MAJOR_VERSION@.@WPG_MINOR_VERSION@/libwpg
libwpg_stream_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_include_HEADERS = $(libwpg_stream_headers)

libwpg_stream_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_la_LIBADD  = @LIBWPG_STREAM_WIN32_RESOURCE@
libwpg_stream_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_la_DEPENDENCIES = @LIBWPG_STREAM_WIN32_RESOURCE@
libwpg_stream_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_la_LDFLAGS = $(version_info) -export-dynamic $(no_undefined)
libwpg_stream_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_la_SOURCES = $(libwpg_stream_sources)

endif


if OS_WIN32

@LIBWPG_WIN32_RESOURCE@ : libwpg.rc $(libwpg_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_la_OBJECTS)
	chmod +x $(top_srcdir)/build/win32/*compile-resource
	WINDRES=@WINDRES@ $(top_srcdir)/build/win32/lt-compile-resource libwpg.rc @LIBWPG_WIN32_RESOURCE@

if WITH_LIBWPG_STREAM

@LIBWPG_STREAM_WIN32_RESOURCE@ : libwpg-stream.rc $(libwpg_stream_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_la_OBJECTS)
	chmod +x $(top_srcdir)/build/win32/*compile-resource
	WINDRES=@WINDRES@ $(top_srcdir)/build/win32/lt-compile-resource libwpg-stream.rc @LIBWPG_STREAM_WIN32_RESOURCE@

endif

endif


install-data-local: install-libtool-import-lib

uninstall-local: uninstall-libtool-import-lib

EXTRA_DIST = \
	$(libwpg_stream_sources) \
	$(libwpg_stream_headers) \
	libwpg.h.in \
	libwpg.rc.in \
	libwpg-stream.rc.in \
	makefile.mk

# These may be in the builddir too
BUILD_EXTRA_DIST = \
	libwpg.rc \
	libwpg-stream.rc
