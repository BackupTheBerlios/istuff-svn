REL_DIR=$(date +%Y.%m.%d)
mkdir ../../release/$REL_DIR
rm -rf ../../release/$REL_DIR/*
javac -classpath ./:AppleJavaExtensions.jar *.java
mkdir build
rm -rf build/*
cp -r addons/* build/
mv *.class build/
cp -r manifest.txt *.prefs *.xml JUnit com org icons javax build/
cd build
jar cvfm ../../../release/$REL_DIR/istuff.jar manifest.txt  *
cd ..
rm -rf build
cp start* ../../release/$REL_DIR/
