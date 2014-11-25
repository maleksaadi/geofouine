#!/usr/bin/env bash

gps_device=$1
gps_device=${gps_device:="/dev/ttyUSB0"}


########################################
#
# 4800 8n1 with modem/device flow control (settings
# for the BU-353
#
echo gps device=$gps_device
stty \
    -F $gps_device \
    raw \
    4800 \
    cs8 \
    clocal \
    cs8 \
    -parenb \
    crtscts \
    -cstopb

# open the GPS as a file
exec 4<$gps_device



read this_line <&4 # each first line (oft. garbage)

while [ 1 ]
do
    read this_line 
    
    this_line=$( echo $this_line | sed s/$'\r'//g )

    ts=$(date +"%Y/%m/%d %H:%M:%S.%N")

    echo $ts $this_line >> full-log.txt

    if [[ "${this_line}" =~ GPRMC ]]
    then
        # echo $this_line
        # ok, it looks like a GPS reading (may be void)
        if [[ $(echo $this_line | cut -d, -f 3) == "A" ]]
        then
            gps_pos=($(echo $this_line | \
                cut -d, -f 4-7 | \
                tr , ' ' | \
                sed 's/\(^0*\)\|\(\b0*\)//g'))

            gps_pos[0]=$(echo scale=6\;${gps_pos[0]}/100 | bc)
            gps_pos[2]=$(echo scale=6\;${gps_pos[2]}/100 | bc)

            echo $ts ${gps_pos[@]}
        fi
    fi
done <&4
