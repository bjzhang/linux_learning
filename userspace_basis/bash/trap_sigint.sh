#!/bin/bash

sig_int_handle()
{
	sig_int_triggerd=1
}


trap sig_int_handle SIGINT
sig_int_triggerd=0
while true; do
	if [ "$sig_int_triggerd" = "1" ]; then
		echo "exit..."
		break;
	fi
	date;
	sleep 1;
done

