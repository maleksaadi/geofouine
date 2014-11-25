#!/usr/bin/env bash

gps_device=$1
gps_device=${gps_device:="/dev/ttyACM0"}


########################################
#
# 4800 8n1 with modem/device flow control (settings
# for the colombus v800
#
echo gps device=$gps_device
stty \
    -F $gps_device \
    raw \
    38400 \
    cs8 \
    clocal \
    cs8 \
    -parenb \
    crtscts \
    -cstopb


exec 4<$gps_device # gps read-stream
exec 5>$gps_device # gps write-stream

# configure GPS options

# with the help of : http://www.hhhh.org/wiml/proj/nmeaxor.html
#
# 2000 ms = $PMTK220,2000*1C
# 1500 ms = $PMTK220,1500*1A
# 1000 ms = $PMTK220,1000*1F
#  750 ms = $PMTK220,750*2C
#  500 ms = $PMTK220,500*2B
#  250 ms = $PMTK220,250*29
#  200 ms = $PMTK220,200*2Ct
#  100 ms = $PMTK220,100*2F


echo \$PMTK220,1000\*1F$'\r' >&5


read this_line <&4 # each first line (oft. garbage)

while [ 1 ]
do
    read this_line 
    
    this_line=$( echo $this_line | sed s/$'\r'//g )

    ts=$(date +"%Y/%m/%d %H:%M:%S.%N")

    echo $ts $this_line >> full-log.txt

    if [[ "$this_line" =~ "GPRMC" ]]
    then
        # ok, it looks like a GPS reading (may be void)
        if [[ $(echo $this_line | cut -d, -f 4-6) != ",,," ]]
        then
            gps_pos=($(echo $this_line | \
                cut -d, -f 3-7 | \
                tr , ' ' | \
                sed 's/\(^0*\)\|\(\b0*\)//g'))

            #gps_pos[1]=$(echo scale=6\;${gps_pos[1]}/100 | bc)
            #gps_pos[3]=$(echo scale=6\;${gps_pos[3]}/100 | bc)

            echo $ts ${gps_pos[@]}
        fi
    fi
done <&4
