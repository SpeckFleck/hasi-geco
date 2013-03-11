.PHONY: all clean

all: src_dir test_dir

src_dir:
	$(MAKE) -C src/

test_dir:
	$(MAKE) -C test/

clean:
	$(MAKE) -C src/ clean
	$(MAKE) -C test/ clean

