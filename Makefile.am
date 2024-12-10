AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = my_program
my_program_SOURCES = main.cpp FuncA.cpp FuncA.h
dist_man_MANS=Funk.1
dist_pkgdata_DATA=data.txt
.PHONY: deb

deb:
	make DESTDIR=$(CURDIR)/deb install


