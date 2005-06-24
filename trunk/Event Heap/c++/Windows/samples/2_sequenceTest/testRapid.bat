@set CMD=debug\2_sequenceTest.exe
@set OPTBASE= --retrievalType waitForEvent --traceMask ALL --host localhost

@rem rapid
%CMD% %OPTBASE% --threads 1 --count 100 --maxSleepTime 0 --traceFile trace.txt --outFile out.xml
