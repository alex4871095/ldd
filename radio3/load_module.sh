#!/bin/bash

MAJOR_NUMBER="$1" 

#if ( cat /proc/devices | awk '{print $1}' | grep $MAJOR_NUMBER > 0 ); then

if ( cat /proc/devices | grep $MAJOR_NUMBER > 0 ); then
	echo "This major_number is already in use, exiting"
	exit -1
else
	echo "Creating device file"
	mknod /dev/radio c $MAJOR_NUMBER 1
	echo "Loading module"
	insmod ./radio.ko radio_major=$MAJOR_NUMBER
	cat /dev/radio
fi

