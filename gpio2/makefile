SUBDIRS = lib src
File= gpio
exe= server

all: $(SUBDIRS)

$(SUBDIRS):
		$(MAKE) -C $@

clean:
	
	rm ./lib/$(File).o ./lib/$(File).a ./bin/$(exe)

.PHONY: $(SUBDIRS)
