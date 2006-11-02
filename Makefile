all:
	+$(MAKE) -C contrib/fastdep-0.15
	$(MAKE) -C source
	+$(MAKE) -C Application

install:
	$(MAKE) -C source install

clean:
	$(MAKE) -C source clean
	$(MAKE) -C Application clean
	
distclean: clean
	$(MAKE) -C contrib/fastdep-0.15 distclean
