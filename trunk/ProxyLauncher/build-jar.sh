mkdir ../../release/test
javac -cp ./:AppleJavaExtensions.jar *.java
jar cvfm ../../release/test/istuff.jar manifest.txt  *.class *.prefs *.xml JUnit com org icons javax
rm *.class
