if BUILD_TOOLS

bin_PROGRAMS = wpg2svg

AM_CXXFLAGS = \
	-I$(top_srcdir)/inc \
	$(REVENGE_CFLAGS) \
	$(REVENGE_STREAM_CFLAGS) \
	$(DEBUG_CXXFLAGS)

wpg2svg_DEPENDENCIES = @WPG2SVG_WIN32_RESOURCE@

wpg2svg_LDADD = \
	../../lib/libwpg-@WPG_MAJOR_VERSION@.@WPG_MINOR_VERSION@.la	\
	$(REVENGE_LIBS) \
	$(REVENGE_STREAM_LIBS) \
	@WPG2SVG_WIN32_RESOURCE@ 

wpg2svg_SOURCES = \
	wpg2svg.cpp

if OS_WIN32

@WPG2SVG_WIN32_RESOURCE@ : wpg2svg.rc $(wpg2svg_OBJECTS)
	chmod +x $(top_srcdir)/build/win32/*compile-resource
	WINDRES=@WINDRES@ $(top_srcdir)/build/win32/lt-compile-resource wpg2svg.rc @WPG2SVG_WIN32_RESOURCE@
endif

EXTRA_DIST = \
	$(wpg2svg_SOURCES) \
	wpg2svg.rc.in \
	wpg2svgbatch.pl

# These may be in the builddir too
BUILD_EXTRA_DIST = \
	wpg2svg.rc

bin_SCRIPTS = wpg2svgbatch.pl

endif
