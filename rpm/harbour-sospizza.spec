Name:       harbour-sospizza
Summary:    A pizza dough calculator
Version:    0.1.0
Release:    1
License:    MIT
URL:        https://github.com/ilpianista/harbour-SOSPizza
Source0:    %{name}-%{version}.tar.bz2
Requires:   sailfishsilica-qt5 >= 0.10.9
BuildRequires:  pkgconfig(sailfishapp) >= 1.0.2
BuildRequires:  pkgconfig(Qt5Core)
BuildRequires:  pkgconfig(Qt5Qml)
BuildRequires:  pkgconfig(Qt5Quick)
BuildRequires:  desktop-file-utils

%description
A pizza dough calculator for Sailfish OS.

%if 0%{?_chum}
Title: SOSPizza
Type: desktop-application
DeveloperName: Andrea Scarpino
Categories:
 - Utility
Custom:
  Repo: https://github.com/ilpianista/harbour-SOSPizza
Icon: https://raw.githubusercontent.com/ilpianista/harbour-SOSPizza/master/icons/256x256/harbour-sospizza.png
Screenshots:
 - https://raw.githubusercontent.com/ilpianista/harbour-SOSPizza/master/screenshots/screenshot_1.png
 - https://raw.githubusercontent.com/ilpianista/harbour-SOSPizza/master/screenshots/screenshot_2.png
 - https://raw.githubusercontent.com/ilpianista/harbour-SOSPizza/master/screenshots/screenshot_3.png
Links:
  Homepage: https://github.com/ilpianista/harbour-SOSPizza
  Bugtracker: https://github.com/ilpianista/harbour-SOSPizza/issues
  Donation: https://liberapay.com/ilpianista
%endif


%prep
%setup -q -n %{name}-%{version}

%build
%qmake5
%make_build

%install
%qmake5_install

desktop-file-install --delete-original \
    --dir %{buildroot}%{_datadir}/applications \
    %{buildroot}%{_datadir}/applications/*.desktop

%files
%defattr(-,root,root,-)
%{_bindir}/%{name}
%{_datadir}/%{name}
%{_datadir}/applications/%{name}.desktop
%{_datadir}/icons/hicolor/*/apps/%{name}.png
