@set CMD=debug\2_sequenceTest.exe
@set OPTBASE= --retrievalType waitForEvent --traceMask ALL --host localhost

@rem basic
%CMD% %OPTBASE% --threads 1 --count 100 --maxSleepTime 1000 --traceFile trace-1-1000.txt --outFile out-1-1000.xml

@rem multithreads
%CMD% %OPTBASE% --threads 10 --count 100 --maxSleepTime 1000 --traceFile trace-10-1000.txt --outFile out-10-1000.xml

@rem fast
%CMD% %OPTBASE% --threads 3 --count 500 --maxSleepTime 50 --traceFile trace-3-50.txt --outFile out-3-50.xml

@rem very fast
%CMD% %OPTBASE% --threads 3 --count 500 --maxSleepTime 10 --traceFile trace-3-10.txt --outFile out-3-10.xml

@rem crowded
%CMD% %OPTBASE% --threads 50 --count 50 --maxSleepTime 1000 --traceFile trace-50-1000.txt --outFile out-50-1000.xml

@rem very crowded
%CMD% %OPTBASE% --threads 100 --count 50 --maxSleepTime 1000 --traceFile trace-100-1000.txt --outFile out-100-1000.xml

@rem crowded and fast
%CMD% %OPTBASE% --threads 50 --count 50 --maxSleepTime 50 --traceFile trace-50-50.txt --outFile out-50-50.xml

