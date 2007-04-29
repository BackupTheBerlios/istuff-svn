EHEAPSERVER=localhost
MACHINENAME=CurrentSlide
if [ $# -ge 1 ]
then
    EHEAPSERVER=$1;
fi
if [ $# -ge 2 ]
then 
    EHEAPSERVER=$1;
    MACHINENAME=$2;
fi
echo $EHEAPSERVER $MACHINENAME;
java -classpath ../../Lib/iROS.jar:. SlideController $EHEAPSERVER $MACHINENAME;
