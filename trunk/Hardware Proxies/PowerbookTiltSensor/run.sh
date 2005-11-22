EHEAPSERVER=localhost
if [ $# -ge 1 ]
then 
    EHEAPSERVER=$1
fi
echo $EHEAPSERVER
./motion/motion powerbook | java -cp "../../Lib/iROS.jar":. motionProxy $EHEAPSERVER
