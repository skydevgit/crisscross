# CrissCross makefile

include common.mk

all: main

main:
	+$(MAKE) -C source precomp
	+$(MAKE) -C source
	
example:
	+$(MAKE) -C examples

testsuite: main
	+$(MAKE) -C TestSuite precomp
	+$(MAKE) -C TestSuite

test: testsuite
	cd TestSuite; LD_LIBRARY_PATH="../source" ./crisscross-test;

memcheck: testsuite
	$(MAKE) -C TestSuite memcheck

install:
	$(MAKE) -C source install

clean:
	$(MAKE) -C source clean
	$(MAKE) -C examples clean
	$(MAKE) -C TestSuite clean

distclean: clean
