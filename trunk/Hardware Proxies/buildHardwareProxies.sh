JAVAC="javac -classpath ../ProxyLauncher/:../ProxyLauncher/addons/"

# Blue Sentry
$JAVAC:./BlueSentry ./BlueSentry/*.java -d ./BlueSentry
echo "build BlueSentry..."

# DTMouseKeyboardProxy
# TODO: How to build?

# GameController - SKIPED (Build under Windows)
#cd GameController/Windows
#sh build.bat
#cd ../..
#$JAVAC:./GameController/lib/JXInput.jar -d GameController/Windows/class \
#  GameController/*.java
#jar -mfc GameController/Manifest GameController/Windows/GameController.jar \
#  -C Gamecontroller/Windows/class/ .
#echo "build GameController"

# KeyRobot
$JAVAC KeyRobot/*.java -d KeyRobot/

# KnobServer
# KnobServer2
# errors due to missing files in project - linking to eugen's home dir
#cd KnobServer/
#xcodebuild
#echo "build KnobServer"
#cd ../KnobServer2
#xcodebuild
#echo "build KnobServer2"

# MultiPointerServer
$JAVAC:./MultiPointerServer -d ./MultiPointerServer ./MultiPointerServer/*.java
echo "build MultiPointerServer"

# PRReceiver SKIP - ANT?

# Phidgets
  # Accelerometer
$JAVAC:./Phidgets:./Phidgets/Accelerometer   -d ./Phidgets/Accelerometer   ./Phidgets/Accelerometer/*.java
  # InterfaceKit
$JAVAC:./Phidgets:./Phidgets/InterfaceKit    -d ./Phidgets/InterfaceKit    ./Phidgets/InterfaceKit/*.java
  # RFID
$JAVAC:./Phidgets:./Phidgets/RFID            -d ./Phidgets/RFID            ./Phidgets/RFID/*.java
  # ServoController
$JAVAC:./Phidgets:./Phidgets/ServoController -d ./Phidgets/ServoController ./Phidgets/ServoController/*.java

# PowerbookTiltSensor
$JAVAC:./PowerbookTiltSensor -d ./PowerbookTiltSensor ./PowerbookTiltSensor/*.java

# Smart-Its

# Teleo

# iPhone

# iStuff Mobile

# moteRFID

# x10
