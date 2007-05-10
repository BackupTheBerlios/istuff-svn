# create directoryname
REL_DIR=$(date +%Y.%m.%d)

# clear target and create correct folder
#rm -rf ../../release/$REL_DIR
mkdir ../../release/$REL_DIR
mkdir ../../release/$REL_DIR/iStuff/
TARGET=../../release/$REL_DIR/iStuff

# build the java project
javac -classpath ./:AppleJavaExtensions.jar *.java

# move/copy all important files for the jar-target into a clean subfolder "build"
rm -rf build
mkdir build
cp -r addons/*.class build/
svn export addons/iwork build/iwork
mv *.class build/
cp -r manifest.txt *.prefs *.xml build/
svn export JUnit build/JUnit
svn export com build/com
svn export org build/org
svn export icons build/icons
svn export javax build/javax

# goto the build dir and create the jar - put it into tha target dir
cd build
jar cvfm ../$TARGET/iStuff.jar manifest.txt  *
cd ..

# clean up
rm -rf build

# copy some surroundings into the target dir
cp start* $TARGET/
cp README.txt $TARGET/
svn export Hardware\ Proxies $TARGET/Hardware\ Proxies
svn export Software\ Proxies $TARGET/Software\ Proxies
svn export ../installer/Resources/QC\ iStuff\ Installer.mpkg \
    $TARGET/QC\ iStuff\ Installer.mpkg

# constructing the Mac app
# note: the already constructed iStuff.jar is used by this app,
# so have both in the same directory
svn export iStuff.app $TARGET/iStuff.app

# goto target, and zip everything into one iStuff.zip
ORIGIN=`pwd`
cd $TARGET/..
zip -r iStuff.zip ./
rm -rf iStuff
# only iStuff.zip remains with everything in it

# return
cd $ORIGIN

# done
echo "Done\n"
