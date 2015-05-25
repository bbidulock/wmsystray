Summary: Window Maker system tray dock applet
Name: wmsystray
Version: 0.1.1
Release: 1
License: GPL
Group: User Interface/Desktops
URL: http://kai.vm.bytemark.co.uk/~arashi/wmsystray/
Packager: Matthew Reppert <arashi@kai.vm.bytemark.co.uk>
Source: %{name}-%{version}.tar.gz
BuildRoot: %{_tmppath}/%{name}-root

%description
System tray dock applet for Window Maker.
Provides a freedesktop.org-compliant system tray area in a Window Maker dock
applet.

%prep
%setup -q

%build
make

%install
rm -rf $RPM_BUILD_ROOT
make prefix=$RPM_BUILD_ROOT/usr install

%clean
rm -rf %{buildroot}

%files
%attr(0755, root, bin) /usr/bin/wmsystray
%attr(0644, root, bin) /usr/share/man/man1/wmsystray.1
