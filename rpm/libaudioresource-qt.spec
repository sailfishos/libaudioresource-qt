Name: libaudioresource-qt
Version: 2.0.0
Release: 1
Summary: Nemo Mobile Audio Resource API (Qt bindings)
Group: Development/Libraries
License: LGPL
URL: http://github.com/nemomobile
Source: %{name}-%{version}.tar.bz2
BuildRequires: pkgconfig(Qt5Core)
BuildRequires: pkgconfig(Qt5Multimedia)
BuildRequires: pkgconfig(audioresource)
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description
This library provides a way to acquire audio resources for playback on Nemo
Mobile and Sailfish, as well as a way to get notified when audio resources
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
make install INSTALL_ROOT=%{buildroot}

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
