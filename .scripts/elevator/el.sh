#!/bin/sh
while :; do
	export i=`expr 0`
	while [ $i -le 23 ]; do
		osascript .scripts/elevator/ele_$i.scpt
		export i=`expr $i + 1`
	done
done

