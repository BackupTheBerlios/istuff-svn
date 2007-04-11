mkdir ../../release/test
javac *.java
jar cvfm ../../release/test/istuff.jar manifest.txt  *.class *.prefs *.xml JUnit com org icons javax
rm *.class
