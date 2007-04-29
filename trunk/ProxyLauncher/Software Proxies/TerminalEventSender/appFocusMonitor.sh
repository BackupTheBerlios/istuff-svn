#!/bin/bash
EHEAPSERVER=$1
MACHINENAME=$2
OLD='null'
#X=1
#while [ $X -ge 0 ]
while [ 1 -eq 1 ]
do
	E=`osascript getFrontNameScript`
	if [ $OLD != $E ];
	then
		java -classpath ../../Lib/iROS.jar:. TerminalEventSender $EHEAPSERVER appChangedEvent machine:$MACHINENAME application:$E level:0;
		OLD=$E
	fi
#	echo $E
#	echo $X
#	X=$((X+1))
done
