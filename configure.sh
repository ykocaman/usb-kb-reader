#!/bin/bash

device="USB Reader With Keyboard USB Reader With Keyboard";
event_file=`grep -E 'Name|Handlers|EV' /proc/bus/input/devices | grep 'EV=120013' -B2 | grep "$device" -A1 | grep -oE 'event[0-9]+'`;

cp config.ini.example config.ini;

sed -i "s/^Name.*/Name\t\t=\t$device;/" config.ini;
sed -i "s/^EventFile.*/EventFile\t=\t\/dev\/input\/$event_file;/" config.ini;

user=`whoami`;
sed -i "s/sudo -u user/sudo -u $user/" config.ini;

mac=`ifconfig | grep eth0 | awk '{print $NF}'`;
sed -i "s/card_id=%s/card_id=%s\\\\\&mac=$mac/" config.ini;
