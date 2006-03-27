EHEAPSERVER=localhost
if [ $# -ge 2 ]
then 
    EHEAPSERVER=$1
    PROXYID=$2
fi
echo $EHEAPSERVER $PROXYID
cd classes
java -classpath ../../../Lib/iROS.jar:. TextEventEngine $EHEAPSERVER $PROXYID
cd ..

