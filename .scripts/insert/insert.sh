#!/bin/sh

while :; do
	export i=`expr 0`
	while [ $i -le 194 ] ; do
		osascript .scripts/insert/insert_$i.scpt
		export i=`expr $i + 1`
	done
done
