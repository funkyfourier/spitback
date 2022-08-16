## LibPD Makefile

To build LibPD with Spitback's externals statically linked, do this:

1. Clone libpd as described on libpd's github page.
2. Copy externals to libpd's root folder.
3. Replace LipPD's Makefile with the one from this directory.
4. Replace libpd/libpd_wrapper/z_libpd.c with the one from this directory.
5. Type make javalib and find jar-file in libpd/libs/.

