EHEAPSERVER=localhost
if [ $# -ge 1 ]
then 
    EHEAPSERVER=$1
fi
echo $EHEAPSERVER
java -classpath ../../../Lib/iROS.jar:..:. RFIDproxyMod $EHEAPSERVER
