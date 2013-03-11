.NOTPARALLEL: src/mcchd_wl_bulk src/mcchd_wl_plane src/mcchd_wl_line src/mcchd_wl_point

all: test/test src/mcchd_wl_bulk src/mcchd_wl_plane src/mcchd_wl_line src/mcchd_wl_point

src/mcchd_wl_bulk src/mcchd_wl_plane src/mcchd_wl_line src/mcchd_wl_point:
	$(MAKE) -C src/

test/test:
	$(MAKE) -C test/

clean:
	$(MAKE) -C src/ clean
	$(MAKE) -C test/ clean

