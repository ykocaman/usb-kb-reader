CC = gcc

all: usb-kb-reader clean

usb-kb-reader: usb-kb-reader.c
	$(CC) -o  usb-kb-reader usb-kb-reader.c

clean:
	rm -f *.o

install: all
	mv ./usb-kb-reader /usr/bin/usb-kb-reader