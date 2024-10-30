#!/bin/bash

echo "Unloading module"
rmmod ./radio.ko
echo "Deleting device file"
rm -rf /dev/radio
dmesg | tail -5
