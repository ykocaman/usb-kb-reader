This program for hooking inputs of [USB Barcode Readers](https://www.google.com.tr/search?q=usb+barcode+reader&tbm=isch) which sends scanned data as keyboard input in ubuntu.

**Compile:**
```
make
```

**Install:**
```
make install
```

**Usage:**
```
sudo usb-kb-reader /dev/input/event14
```

**Available keyboard inputs:**
```
grep -E 'Name|Handlers|EV' /proc/bus/input/devices | grep 'EV=120013' -B2 
```
[Why EV=120013?](http://unix.stackexchange.com/questions/74903/explain-ev-in-proc-bus-input-devices-data)

**Output can be:**
>N: Name="Digital Media Keyboard"  
>H: Handlers=sysrq kbd **event5**  
>B: EV=120013 
>
>N: Name="USB Reader With Keyboard USB Reader With Keyboard"  
>H: Handlers=sysrq kbd **event14**  
>B: EV=120013  


**Example dynamic usage of "USB Reader With Keyboard USB Reader With Keyboard":**
```
usb-kb-reader /dev/input/\
	$(
		grep -E 'Name|Handlers|EV' /proc/bus/input/devices |\
		grep 'EV=120013' -B2 |\
		grep 'USB Reader*' -A2 |\
		grep -Eo 'event[0-9]+'\
	) 
```
