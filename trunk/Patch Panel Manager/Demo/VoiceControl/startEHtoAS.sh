#Cannot deal with space character in bash so i created this extra script just to start the applescript proxy
EHEAPNAME=$1
MACHINENAME=$2
cd ../../Software\ Proxies/EHtoAppleScript/
java -classpath ../../Lib/iROS.jar:. EHtoAppleScript $EHEAPNAME $MACHINENAME &
