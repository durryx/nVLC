#!/bin/bash
counter=0
(
# set infinite while loop
while :
do
cat <<EOF
XXX
$counter
Extracting images from test.mp4 ($counter%):
XXX
EOF
# increase counter by 10
(( counter+=1))
[ $counter -eq 100 ] && break
# delay it a specified amount of time
sleep 0.1
done
) |
dialog --title "Processing" --gauge "Please wait" 7 70 0
clear
