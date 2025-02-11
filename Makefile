CFLAGS =-Wall -g
PREFIX = /usr/local

all: clean src\/dayfromdate.c src\/generateday.c

src\/dayfromdate.c:
	gcc src/dayfromdate.c -o bin/dayfromdate

src\/generateday.c:
	gcc src/generateday.c -o bin/generateday

clean:
	rm -f bin/dayfromdate bin/generateday

install: bin/dayfromdate bin/generateday
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp -f bin/dayfromdate $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/dayfromdate
	cp -f bin/generateday $(DESTDIR)$(PREFIX)/bin
	chmod 755 $(DESTDIR)$(PREFIX)/bin/generateday

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/dayfromdate
	rm -f $(DESTDIR)$(PREFIX)/bin/generateday
