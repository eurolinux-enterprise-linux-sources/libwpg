if PLATFORM_WIN32
version_info = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE) -avoid-version
else
version_info = -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)
endif

lib_LTLIBRARIES = libwpg-@WPG_MAJOR_VERSION@.@WPG_MINOR_VERSION@.la
libwpg_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_includedir = $(includedir)/libwpg-@WPG_MAJOR_VERSION@.@WPG_MINOR_VERSION@/libwpg
libwpg_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_include_HEADERS = \
	$(top_srcdir)/inc/libwpg/libwpg.h \
	$(top_srcdir)/inc/libwpg/WPGraphics.h

AM_CXXFLAGS = -I$(top_srcdir)/inc $(REVENGE_CFLAGS) $(WPD_CFLAGS) $(DEBUG_CXXFLAGS) -DLIBWPG_BUILD=1

libwpg_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_la_LIBADD  = $(WPD_LIBS) $(REVENGE_LIBS) @LIBWPG_WIN32_RESOURCE@
libwpg_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_la_DEPENDENCIES = @LIBWPG_WIN32_RESOURCE@
libwpg_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_la_LDFLAGS = $(version_info) -export-dynamic -no-undefined
libwpg_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_la_SOURCES = \
	WPGraphics.cpp \
	WPGDashArray.cpp \
	WPGColor.cpp \
	WPGHeader.cpp \
	WPGXParser.cpp \
	WPG1Parser.cpp \
	WPG2Parser.cpp \
	WPGBitmap.cpp \
	libwpg_utils.h \
	WPGColor.h \
	WPGDashArray.h \
	WPGHeader.h \
	WPGXParser.h \
	WPG1Parser.h \
	WPG2Parser.h \
	WPGBitmap.h

if OS_WIN32

@LIBWPG_WIN32_RESOURCE@ : libwpg.rc $(libwpg_@WPG_MAJOR_VERSION@_@WPG_MINOR_VERSION@_la_OBJECTS)
	chmod +x $(top_srcdir)/build/win32/*compile-resource
	WINDRES=@WINDRES@ $(top_srcdir)/build/win32/lt-compile-resource libwpg.rc @LIBWPG_WIN32_RESOURCE@

endif


EXTRA_DIST = \
	libwpg.rc.in

# These may be in the builddir too
BUILD_EXTRA_DIST = \
	libwpg.rc
