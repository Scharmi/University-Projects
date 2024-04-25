cd /
patch -p1 < ms440004.patch
cd /usr/src/minix
make && make install
cd usr/src/lib/libc
make && make install
cd /usr/src/releasetools; make hdboot
