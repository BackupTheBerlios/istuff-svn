echo usage: reloadScript EHeapname [ScriptName]
SCRIPTNAME=Speech.pps
if [ $# -ge 2 ]; then
  SCRIPTNAME=$2	
fi
java -cp ../../../Lib/iROS.jar:../../../Lib/jph.jar iwork.patchpanel.manager.PPManager -s $SCRIPTNAME $1
