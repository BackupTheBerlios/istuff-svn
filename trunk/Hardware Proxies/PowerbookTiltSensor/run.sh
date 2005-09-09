EHEAPSERVER=localhost
if [ $# -ge 1 ]
then 
    EHEAPSERVER=$1
fi
./amstracker -u 0.2 | java -cp "../../Lib/iROS.jar":. amsProxy $EHEAPSERVER
# -u = update rate, update every 0.2 seconds
