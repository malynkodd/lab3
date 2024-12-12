AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = my_program
my_program_SOURCES = main.cpp FuncA.cpp FuncA.h HTTP_Server.cpp
dist_man_MANS=Funk.1
dist_pkgdata_DATA=data.txt

CTRLF_DIR=$(CURDIR)/deb/DEBIAN
CTRLF_NAME=$(CTRLF_DIR)/control

SUBDIRS = tests

.PHONY: deb
deb:
	mkdir -p $(CTRLF_DIR)
	echo Package: $(PACKAGE) > $(CTRLF_NAME)
	echo Version: $(VERSION) >> $(CTRLF_NAME)
	echo Architecture: all >> $(CTRLF_NAME)
	echo Maintainer: $(PACKAGE_BUGREPORT) >> $(CTRLF_NAME)
	echo -n "Description:" >> $(CTRLF_NAME)
	cat Funk.1 >> $(CTRLF_NAME)  
	make DESTDIR=$(CURDIR)/deb install


