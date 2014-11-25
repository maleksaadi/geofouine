#!/usr/bin/env bash

gps_device=$1
gps_device=${gps_device:="/dev/ttyUSB0"}


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

while [ 1 ]
do
    # get GPS coordinates
    #gps_pos=$(get_gps)
    echo $(date +"%Y/%m/%d %H:%M:%S.%N") $(get_gps)
done
