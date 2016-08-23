CC      ?= gcc
CFLAGS  = -g -Iiniparser/src
LFLAGS  = -Liniparser -liniparser
RM      ?= rm -f
SRC 	= src
DST		= /opt/usb-kb-reader

all: usb-kb-reader clean run


usb-kb-reader: $(SRC)/*.*
	$(CC) $(CFLAGS) -o usb-kb-reader $(SRC)/*.c $(LFLAGS) 

run:
	@(sudo ./usb-kb-reader)

configure:
	@(./configure.sh)
	@(cd iniparser ; $(MAKE))

clean:
	$(RM) $(SRC)/*.o

install:
	@(mkdir $(DST))
	mv usb-kb-reader $(DST)/usb-kb-reader
	mv config.ini $(DST)/config.ini
	mv supervisor.conf /etc/supervisor/conf.d/usb-kb-reader.conf

uninstall:
	$(RM) -r $(DST)