#!/bin/sh


while :; do
	export i=`expr 1`
	while [ $i -le 4 ] ; do
		osascript .scripts/back_put/back_put_$i.scpt
		export i=`expr $i + 1`
	done
done
