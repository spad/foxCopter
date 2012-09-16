#!/bin/bash

LOC="$1"
EXE="foxCopter"
echo $1


G20IP="10.0.1.158"
GDPPORT="8000"
G20PATH="/media/data/test"
RSAKEY="$LOC/.sync/mac_ubuntu"

#echo "Transfer executable..."
scp -i "$RSAKEY" "$LOC/Debug/$EXE.elf" root@"$G20IP":"$G20PATH"
#echo "make it exec..."
ssh -i "$RSAKEY" root@"$G20IP" "chmod +x $G20PATH/$EXE.elf"
#echo "running gdbserver"
ssh -i "$RSAKEY" root@"$G20IP" "gdbserver $G20IP:$GDPPORT $G20PATH/$EXE.elf " &

