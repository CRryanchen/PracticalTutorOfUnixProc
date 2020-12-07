#!/bin/bash
#
# atm.s  - a wrapper for two programs
#
while true
do
    do_a_transcation            # run a program
    if play_again               # run our program
    then
        continue                # if 'y' loop back
    fi
    break                       # if 'n' break
done