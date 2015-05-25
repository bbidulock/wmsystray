prefix=/usr
bindir = ${prefix}/bin
mandir = ${prefix}/share/man
INSTALL = /bin/install
INSTALLPROG = ${INSTALL} -m 0755
INSTALLMAN = ${INSTALL} -m 0644

all:
	make -C xembed xembed.o
	make -C wmsystray

clean:
	make -C xembed clean
	make -C wmsystray clean
	rm -f wmsystray.deb

install: wmsystray/wmsystray
	mkdir -p ${bindir}
	mkdir -p ${mandir}/man1
	${INSTALLPROG} wmsystray/wmsystray ${bindir}/wmsystray
	${INSTALLMAN} doc/wmsystray.1 ${mandir}/man1/wmsystray.1

deb: wmsystray/wmsystray
	echo 2.0 > debian-binary
	mkdir -p usr/bin
	mkdir -p usr/share/man/man1
	make prefix=usr install
	md5sum `find usr -type f` > debian/md5sums
	cd debian ; tar -zcf ../control.tar.gz *
	tar -zcf data.tar.gz usr
	ar -r wmsystray.deb debian-binary control.tar.gz data.tar.gz
	rm -rf debian/md5sums usr debian-binary control.tar.gz data.tar.gz
