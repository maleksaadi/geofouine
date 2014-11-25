#!/usr/bin/env bash

gps_device=$1
gps_device=${gps_device:="/dev/ttyACM0"}


########################################
function get_gps()
{   
    # no do...while loops, so 
    # while with a break
    while [ 1 ]
    do
        read this_line <&4
        if [[ "$this_line" =~ "GPRMC" ]]
        then
            # when the GPS is syncing, you should
            # have no position reading. Normally
            # it should not last more than a few
            # seconds.
            #
            if [[ $(echo $this_line | cut -d, -f 4-7 ) != ",,," ]]
            then
                # ok, we have a minimal position
                #
                break
            else
                # maybe the GPS is still computing
                # its initial position
                #
                echo "waiting for sync..." $this_line 1>&2
            fi
        fi
    done

    # constructs a list with leading zeroes
    # removed
    # 
    gps_pos=($(echo $this_line | \
        cut -d, -f 4-7 | \
        tr , ' ' | \
        sed 's/\(^0*\)\|\(\b0*\)//g'))

    gps_pos[0]=$(echo scale=6\;${gps_pos[0]}/100 | bc)
    gps_pos[2]=$(echo scale=6\;${gps_pos[2]}/100 | bc)

    echo ${gps_pos[@]}
 }


########################################


# 38400 8n1 with modem/device flow control (settings
# for the columbus v800
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
#  200 ms = $PMTK220,200*2C
#  100 ms = $PMTK220,100*2F


echo \$PMTK220,200\*2C$'\r' >&5

while [ 1 ]
do
    # get GPS coordinates
    #gps_pos=$(get_gps)
    echo $(date +"%Y/%m/%d %H:%M:%S.%N") $(get_gps)
done
