REL_DIR=$(date +%Y.%m.%d)
rm -rf ../../release/$REL_DIR
mkdir ../../release/$REL_DIR
mkdir ../../release/$REL_DIR/iStuff/
javac -classpath ./:AppleJavaExtensions.jar *.java
rm -rf build
mkdir build
cp -r addons/* build/
mv *.class build/
cp -r manifest.txt *.prefs *.xml JUnit com org icons javax build/
cd build
jar cvfm ../../../release/$REL_DIR/iStuff/iStuff.jar manifest.txt  *
cd ..
rm -rf build
cp start* ../../release/$REL_DIR/iStuff/
cp -r Hardware\ Proxies Software\ Proxies ../../release/$REL_DIR/iStuff/
