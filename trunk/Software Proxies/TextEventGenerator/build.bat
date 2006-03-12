mkdir classes
javac -classpath ..\..\Lib\iROS.jar; -d .\classes .\src\*.java
mkdir .\classes\img
copy .\src\img\* .\classes\img