javac -classpath "class;..\..\..\java\dist\iROS.jar;lib\JXInput.jar" -d class *.java
jar -mfc Manifest GameController.jar -C class\ .
