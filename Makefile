CC      ?= gcc
CFLAGS  = -g -Iiniparser/src
LFLAGS  = -Liniparser -liniparser
RM      ?= rm -f
SRC 	= src

all: usb-kb-reader clean run


usb-kb-reader: $(SRC)/usb-kb-reader.c
	$(CC) $(CFLAGS) -o usb-kb-reader $(SRC)/*.c $(LFLAGS) 

run:
	@(sudo ./usb-kb-reader)

configure:
	@(cd iniparser ; $(MAKE))

clean:
	$(RM) $(SRC)/*.o

install: all
	mv ./usb-kb-reader /usr/bin/usb-kb-reader

uninstall:
	$(RM) /usr/bin/usb-kb-reader

