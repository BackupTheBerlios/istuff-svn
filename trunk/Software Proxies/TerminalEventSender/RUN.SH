EHEAPSERVER=localhost
EVENTTYPE=myEventType
if [ $# -ge 1 ]
then
    EHEAPSERVER=$1;
fi
if [ $# -ge 2 ]
then 
    EHEAPSERVER=$1;
    EVENTTYPE=$2;
fi
echo $EHEAPSERVER $EVENTTYPE;
java -classpath ../../Lib/iROS.jar:. TerminalEventSender $EHEAPSERVER $EVENTTYPE $3 $4 $5 $6 $7 $8 $9;
