%global apiversion 0.3

Name:           libwpg
Version:        0.3.0
Release:        1%{?dist}
Summary:        A library for import of WordPerfect Graphics images

License:        LGPLv2+ or MPLv2.0
URL:            http://libwpg.sourceforge.net/
Source0:        http://download.sourceforge.net/libwpg/%{name}-%{version}.tar.xz

BuildRequires:  doxygen
BuildRequires:  help2man
BuildRequires:  perl(Getopt::Std)
BuildRequires:  pkgconfig(librevenge-0.0)
BuildRequires:  pkgconfig(libwpd-0.10)

%description
%{name} is a library for import of images in WPG
(WordPerfect Graphics) format. WPG is the format used among others in
Corel software, such as WordPerfect and Presentations.

%package devel
Summary:        Development files for %{name}
Requires:       %{name}%{?_isa} = %{version}-%{release}

%description devel
The %{name}-devel package contains libraries and header files for
developing applications that use %{name}.

%package doc
Summary: Documentation of %{name} API
BuildArch: noarch

%description doc
The %{name}-doc package contains API documentation for %{name}.

%package tools
Summary:        Tools to convert WordPerfect Graphics images to other formats
# wpg2svgbatch.pl says "GPL", without specifying version, and points to
# http://www.gnu.org/copyleft/gpl.html . I assume this means "any
# version".
License:        (LGPLv2+ or MPLv2.0) and GPL+
Requires:       %{name}%{?_isa} = %{version}-%{release}

%description tools
Tools to convert WordPerfect Graphics images to other formats. Supported
are: SVG, raw.

%prep
%setup -q

%build
%configure --disable-static --disable-werror
sed -i \
    -e 's|^hardcode_libdir_flag_spec=.*|hardcode_libdir_flag_spec=""|g' \
    -e 's|^runpath_var=LD_RUN_PATH|runpath_var=DIE_RPATH_DIE|g' \
    libtool
make %{?_smp_mflags} V=1
sed 's/\r//' -i ChangeLog
find docs/doxygen/html |xargs touch -r docs/doxygen/doxygen.cfg

export LD_LIBRARY_PATH=`pwd`/src/lib/.libs${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
help2man -N -n 'debug the conversion library' -o wpg2raw.1 ./src/conv/raw/.libs/wpg2raw
help2man -N -n 'convert WordPerfect Graphics into SVG' -o wpg2svg.1 ./src/conv/svg/.libs/wpg2svg
help2man -N -n 'batch convert WordPerfect Graphics files into SVG' \
    --help-option=-h --no-discard-stderr \
    -o wpg2svgbatch.pl.1 ./src/conv/svg/wpg2svgbatch.pl

%install
make install DESTDIR=%{buildroot}
find %{buildroot} -name '*.la' -exec rm -f {} ';'
# we install API docs directly from build
rm -rf %{buildroot}/%{_docdir}/%{name}

install -m 0755 -d %{buildroot}/%{_mandir}/man1
install -m 0644 wpg2*.1 %{buildroot}/%{_mandir}/man1

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%files
%doc AUTHORS ChangeLog COPYING.LGPL COPYING.MPL
%{_libdir}/%{name}-%{apiversion}.so.*

%files devel
%{_includedir}/%{name}-%{apiversion}
%{_libdir}/%{name}-%{apiversion}.so
%{_libdir}/pkgconfig/%{name}-%{apiversion}.pc

%files doc
%doc COPYING.LGPL COPYING.MPL
%doc docs/doxygen/html

%files tools
%{_bindir}/wpg2raw
%{_bindir}/wpg2svg
%{_bindir}/wpg2svgbatch.pl
%{_mandir}/man1/wpg2raw.1*
%{_mandir}/man1/wpg2svg.1*
%{_mandir}/man1/wpg2svgbatch.pl.1*

%changelog
* Fri Apr 17 2015 David Tardon <dtardon@redhat.com> - 0.3.0-1
- Resolves: rhbz#1207767 rebase to 0.3.0

* Fri Jan 24 2014 Daniel Mach <dmach@redhat.com> - 0.2.2-4
- Mass rebuild 2014-01-24

* Fri Dec 27 2013 Daniel Mach <dmach@redhat.com> - 0.2.2-3
- Mass rebuild 2013-12-27

* Tue Jun 25 2013 David Tardon <dtardon@redhat.com> - 0.2.2-2
- bump release

* Thu Apr 18 2013 David Tardon <dtardon@redhat.com> - 0.2.2-1
- new release

* Thu Feb 14 2013 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.2.1-2
- Rebuilt for https://fedoraproject.org/wiki/Fedora_19_Mass_Rebuild

* Thu Nov 29 2012 David Tardon <dtardon@redhat.com> - 0.2.1-1
- new upstream release

* Thu Jul 19 2012 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.2.0-5
- Rebuilt for https://fedoraproject.org/wiki/Fedora_18_Mass_Rebuild

* Tue Feb 28 2012 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.2.0-4
- Rebuilt for c++ ABI breakage

* Fri Jan 13 2012 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.2.0-3
- Rebuilt for https://fedoraproject.org/wiki/Fedora_17_Mass_Rebuild

* Tue Feb 08 2011 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.2.0-2
- Rebuilt for https://fedoraproject.org/wiki/Fedora_15_Mass_Rebuild

* Sun Dec 05 2010 Caolán McNamara <caolanm@redhat.com> - 0.2.0-1
- latest version

* Tue Jul 28 2009 Lubomir Rintel <lkundrak@v3.sk> - 0.1.3-4
- Fix multilib problem with doxygen documentation (#508940)

* Sat Jul 25 2009 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.1.3-3
- Rebuilt for https://fedoraproject.org/wiki/Fedora_12_Mass_Rebuild

* Wed Feb 25 2009 Fedora Release Engineering <rel-eng@lists.fedoraproject.org> - 0.1.3-2
- Rebuilt for https://fedoraproject.org/wiki/Fedora_11_Mass_Rebuild

* Tue Jan 6 2009 Lubomir Rintel <lkundrak@v3.sk> - 0.1.3-1
- Initial packaging
