EHEAPSERVER=localhost
EVENTTYPE=KEYBOARD
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
#Type hello 
#java -classpath ../../Lib/iROS.jar:../../Software\ Proxies/TerminalEventSender/ TerminalEventSender $EHEAPSERVER $EVENTTYPE TimeToLive:2000 Target:sth level:2 size:11 code1:4 action1:pr code2:14 action2:pr code3:37 action3:pr code4:37 action4:pr code5:31 action5:pr code6:49 action6:pr code7:13 action7:pr code8:31 action8:pr code9:15 action9:pr code10:37 action10:pr code11:2 action11:pr


#New doc combination,  META + N
# Using the code version
#java -classpath ../../Lib/iROS.jar:../../Software\ Proxies/TerminalEventSender/ TerminalEventSender $EHEAPSERVER $EVENTTYPE TimeToLive:2000 Target:sth level:2 size:4 code1:55 action1:p code2:45 action2:p code3:45 action3:r code4:55 action4:r

#Using the key version
java -classpath ../../Lib/iROS.jar:../../Software\ Proxies/TerminalEventSender/ TerminalEventSender $EHEAPSERVER $EVENTTYPE TimeToLive:2000 Target:sth level:2 size:4 key1:cmd action1:p key2:n action2:p key3:n action3:r key4:cmd action4:r

#Cast a ls command
#java -classpath ../../Lib/iROS.jar:../../Software\ Proxies/TerminalEventSender/ TerminalEventSender $EHEAPSERVER $EVENTTYPE TimeToLive:2000 Target:sth level:2 size:3 key1:l action1:pr key2:s action2:pr key3:ret action3:pr
