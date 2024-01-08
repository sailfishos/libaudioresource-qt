Name: libaudioresource-qt
Version: 2.0.2
Release: 1
Summary: Sailfish OS Audio Resource API (Qt bindings)
License: LGPL
URL: https://git.sailfishos.org/mer-core/libaudioresource-qt
Source: %{name}-%{version}.tar.bz2
BuildRequires: pkgconfig(Qt5Core)
BuildRequires: pkgconfig(Qt5Multimedia)
BuildRequires: pkgconfig(audioresource)
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description
This library provides a way to acquire audio resources for playback on
Sailfish OS, as well as a way to get notified when audio resources
have been released, in which case audio playback must be stopped.

This package contains the Qt bindings for libaudioresource.

%package devel
Summary: Development library for %{name}
Requires: %{name} = %{version}

%description devel
This package contains the development library for %{name}.

%package example
Summary: Example application for %{name}
Requires: %{name} = %{version}

%description example
This package contains a simple example using %{name}.

%prep
%setup -q

%build
%qmake5
make

%install
%qmake5_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%{_libdir}/%{name}.so.*

%files devel
%defattr(-,root,root,-)
%doc README COPYING.LGPL
%{_libdir}/%{name}.so
%{_libdir}/pkgconfig/audioresource-qt.pc
%{_includedir}/audioresource-qt/audioresource-qt.h
%{_includedir}/audioresource-qt/AudioResourceQt

%files example
%defattr(-,root,root,-)
%doc README COPYING.LGPL
%{_bindir}/audioresource-qt-example
