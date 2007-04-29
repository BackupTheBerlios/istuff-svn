# create directoryname
REL_DIR=$(date +%Y.%m.%d)

# clear target and create correct folder
rm -rf ../../release/$REL_DIR
mkdir ../../release/$REL_DIR
mkdir ../../release/$REL_DIR/iStuff/

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
jar cvfm ../../../release/$REL_DIR/iStuff/iStuff.jar manifest.txt  *
cd ..

# clean up
rm -rf build

# copy some surroundings into the target dir
cp start* ../../release/$REL_DIR/iStuff/
svn export Hardware\ Proxies ../../release/$REL_DIR/iStuff/Hardware\ Proxies
svn export Software\ Proxies ../../release/$REL_DIR/iStuff/Software\ Proxies

# done
echo "Done\n"
