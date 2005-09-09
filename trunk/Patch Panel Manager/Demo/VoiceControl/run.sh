#exit 0 if not enough arguments
if [ $# -lt 2 ]
then
	echo
	echo Usage: run.sh EVENTHEAP_NAME MACHINE_NAME
	echo MACHINE_NAME is where the AppleScriptProxy shall be running
	echo Beware that MACHINE_NAME should correspond to the global variable "currentHostName" of the Speech.pps- pacth panel script
	echo
	exit 1
fi
EHEAPNAME=$1
MACHINENAME=$2

LIBPATH=../../../Lib
#if [ -e GlobalVariables.jph ]
#then  rm *.jph
#fi
rm *.jph

echo
echo Start Apple Script Server
osascript ../dummy.pps
./startEHtoAS.sh $EHEAPNAME $MACHINENAME
echo
echo Start pacth panel
java -server -Djava.library.path=./lib -classpath $LIBPATH/iROS.jar:$LIBPATH/jph.jar iwork.patchpanel.Intermediary $EHEAPNAME &
echo
echo Start speechserver
../../../Software\ Proxies/SpeechRecognition/Mac\ OS\ X/SpeechServer/build/SpeechServer.app/Contents/MacOS/SpeechServer $EHEAPNAME &
echo
echo Load patch script
java -cp $LIBPATH/iROS.jar:$LIBPATH/jph.jar iwork.patchpanel.manager.PPManager -s Speech.pps $EHEAPNAME &

