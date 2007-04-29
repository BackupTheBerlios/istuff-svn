mkdir ./classes
javac -classpath ../../../Lib/iROS.jar:./lib/libparticleJava.jar -d ./classes ./src/*.java
mkdir ./classes/img
cp ./src/img/* ./classes/img
echo build completed