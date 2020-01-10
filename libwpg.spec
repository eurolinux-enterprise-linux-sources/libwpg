%global apiversion 0.2

Name:           libwpg
Version:        0.2.2
Release:        2%{?dist}
Summary:        Library for reading WordPerfect Graphics images

Group:          System Environment/Libraries
License:        LGPLv2+ or MPLv2.0
URL:            http://libwpg.sourceforge.net/
Source0:        http://download.sourceforge.net/libwpg/%{name}-%{version}.tar.xz

BuildRequires:  libwpd-devel
BuildRequires:  doxygen

%description
Libwpg project is a library and to work with graphics in WPG
(WordPerfect Graphics) format. WPG is the format used among others
in Corel software, such as WordPerfect and Presentations.


%package devel
Summary:        Development files for %{name}
Group:          Development/Libraries
Requires:       %{name}%{?_isa} = %{version}-%{release}

%description devel
The %{name}-devel package contains libraries and header files for
developing applications that use %{name}.


%package tools
Summary:        Tools to convert WordPerfect Graphics images
Group:          Applications/Multimedia
# wpg2svgbatch.pl says "GPL", without specifying version, and points to
# http://www.gnu.org/copyleft/gpl.html . I assume this means "any
# version".
License:        (LGPLv2+ or MPLv2.0) and GPL+
Requires:       %{name}%{?_isa} = %{version}-%{release}

%description tools
This package contains tools to work with graphics in WPG (WordPerfect
Graphics) format. WPG is the format used among others in Corel software,
such as WordPerfect and Presentations.


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


%install
# Documentation is intentionally not installed here,
# it is included as -devel %%doc
make SUBDIRS="" install DESTDIR=$RPM_BUILD_ROOT
make -C src install DESTDIR=$RPM_BUILD_ROOT
find $RPM_BUILD_ROOT -name '*.la' -exec rm -f {} ';'


%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig


%files
%doc AUTHORS ChangeLog COPYING.LGPL COPYING.MPL
%{_libdir}/%{name}-%{apiversion}.so.*


%files devel
%doc docs/doxygen/html
%{_includedir}/%{name}-%{apiversion}
%{_libdir}/%{name}-%{apiversion}.so
%{_libdir}/pkgconfig/%{name}-%{apiversion}.pc


%files tools
%doc COPYING.LGPL COPYING.MPL
%{_bindir}/wpg2raw
%{_bindir}/wpg2svg
%{_bindir}/wpg2svgbatch.pl


%changelog
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
