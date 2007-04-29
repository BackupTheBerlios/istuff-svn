mkdir classes
javac -classpath ../../Lib/iROS.jar -d ./classes ./src/*.java
mkdir ./classes/img
cp ./src/img/* ./classes/img/