javac -classpath ..\..\..\Lib\iROS.jar;"%CLASSPATH%";.\lib\libparticleJava.jar;. -d .\classes .\src\*.java
mkdir .\classes\img
copy .\src\img\* .\classes\img