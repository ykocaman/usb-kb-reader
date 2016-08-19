This program for hooking inputs of [USB Barcode Readers](https://www.google.com.tr/search?q=usb+barcode+reader&tbm=isch) which sends scanned data as keyboard input in ubuntu.

**Configure:**
```
make configure
```

**Compile:**
```
make
```


**Config File:**  
- Move config.ini.example file as config.ini.  
- Edit config file and write device handler and command will be executed.  


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

**Usage:**
```
sudo usb-kb-reader
```