Name:       TCapp2ext
Summary:    Test suite for APP2EXT 
Version:    0.5
Release:    1
Group:      TO_BE/FILLED_IN
License:    Apache2.0
Source0:    %{name}-%{version}.tar.gz

Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig
BuildRequires:  pkgconfig(app2sd)
BuildRequires:  pkgconfig(aul)
BuildRequires:  cmake

%description
Test suite for App2Ext

%prep
%setup -q

%build
cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix}

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%{_bindir}/TCapp2ext



