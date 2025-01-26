CFLAGS =-Wall -g
PREFIX = /usr/local

all: clean src\/dayfromdate.c

src\/dayfromdate.c:
	gcc src/dayfromdate.c -o bin/dayfromdate
clean:
	rm -f bin/dayfromdate

install: bin/dayfromdate
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f bin/dayfromdate $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/dayfromdate

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/dayfromdate
