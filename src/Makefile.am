pkgconfdir = $(libdir)/pkgconfig

if WITH_LIBWPG_STREAM
LIBWPG_STREAM_PC = libwpg-stream-@WPG_MAJOR_VERSION@.@WPG_MINOR_VERSION@.pc
endif

pkgconf_DATA = libwpg-@WPG_MAJOR_VERSION@.@WPG_MINOR_VERSION@.pc $(LIBWPG_STREAM_PC)

SUBDIRS = src build docs

EXTRA_DIST = \
	AUTHORS \
	COPYING \
	ChangeLog \
	README \
	autogen.sh \
	libwpg-@WPG_MAJOR_VERSION@.@WPG_MINOR_VERSION@.pc.in \
	libwpg-stream-@WPG_MAJOR_VERSION@.@WPG_MINOR_VERSION@.pc.in \
	libwpg-zip.in \
	libwpg.spec \
	libwpg.spec.in

distclean-local:
	rm -rf *.cache *~

rpm: dist
	rpmbuild -ta $(PACKAGE)-$(VERSION).tar.gz
	@rm -f $(PACKAGE)-$(VERSION).tar.gz

zip: all install
	sh libwpg-zip 


