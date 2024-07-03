echo. > output\results1.txt

echo test_1 >> output\results1.txt

echo Expected data: >> output\results1.txt
type expected_output\test1.txt >> output\results1.txt
echo. >> output\results1.txt
echo. >> output\results1.txt

echo Received data: >> output\results1.txt
powershell -Command "& {..\Executable\ConvertingInequalityToOperationLess.exe input\test1.txt output\ps_results.txt}"
type output\ps_results.txt >> output\results1.txt
powershell -Command "& {rm output\ps_results.txt}"


echo. > output\results2.txt

echo test_2 >> output\results2.txt

echo Expected data: >> output\results2.txt
type expected_output\test2.txt >> output\results2.txt
echo. >> output\results2.txt
echo. >> output\results2.txt

echo Received data: >> output\results2.txt
powershell -Command "& {..\Executable\ConvertingInequalityToOperationLess.exe input\test2.txt output\ps_results.txt}"
type output\ps_results.txt >> output\results2.txt
powershell -Command "& {rm output\ps_results.txt}"


echo. > output\results3.txt

echo test_3 >> output\results3.txt

echo Expected data: >> output\results3.txt
type expected_output\test3.txt >> output\results3.txt
echo. >> output\results3.txt
echo. >> output\results3.txt

echo Received data: >> output\results3.txt
powershell -Command "& {..\Executable\ConvertingInequalityToOperationLess.exe input\test3.txt output\ps_results.txt}"
type output\ps_results.txt >> output\results3.txt
powershell -Command "& {rm output\ps_results.txt}"

echo. > output\results4.txt

echo test_4 >> output\results4.txt

echo Expected data: >> output\results4.txt
type expected_output\test4.txt >> output\results4.txt
echo. >> output\results4.txt
echo. >> output\results4.txt

echo Received data: >> output\results4.txt
powershell -Command "& {..\Executable\ConvertingInequalityToOperationLess.exe input\test4.txt output\ps_results.txt}"
type output\ps_results.txt >> output\results4.txt
powershell -Command "& {rm output\ps_results.txt}"


echo. > output\results5.txt

echo test_5 >> output\results5.txt

echo Expected data: >> output\results5.txt
type expected_output\test5.txt >> output\results5.txt
echo. >> output\results5.txt
echo. >> output\results5.txt

echo Received data: >> output\results5.txt
powershell -Command "& {..\Executable\ConvertingInequalityToOperationLess.exe input\test5.txt output\ps_results.txt}"
type output\ps_results.txt >> output\results5.txt
powershell -Command "& {rm output\ps_results.txt}"


echo. > output\results6.txt

echo test_6 >> output\results6.txt

echo Expected data: >> output\results6.txt
type expected_output\test6.txt >> output\results6.txt
echo. >> output\results6.txt
echo. >> output\results6.txt

echo Received data: >> output\results6.txt
powershell -Command "& {..\Executable\ConvertingInequalityToOperationLess.exe input\test6.txt output\ps_results.txt}"
type output\ps_results.txt >> output\results6.txt
powershell -Command "& {rm output\ps_results.txt}"


echo. > output\results7.txt

echo test_7 >> output\results7.txt

echo Expected data: >> output\results7.txt
type expected_output\test7.txt >> output\results7.txt
echo. >> output\results7.txt
echo. >> output\results7.txt

echo Received data: >> output\results7.txt
powershell -Command "& {..\Executable\ConvertingInequalityToOperationLess.exe input\test7.txt output\ps_results.txt}"
type output\ps_results.txt >> output\results7.txt
powershell -Command "& {rm output\ps_results.txt}"


echo. > output\results8.txt

echo test_8 >> output\results8.txt

echo Expected data: >> output\results8.txt
type expected_output\test8.txt >> output\results8.txt
echo. >> output\results8.txt
echo. >> output\results8.txt

echo Received data: >> output\results8.txt
powershell -Command "& {..\Executable\ConvertingInequalityToOperationLess.exe input\test8.txt output\ps_results.txt}"
type output\ps_results.txt >> output\results8.txt
powershell -Command "& {rm output\ps_results.txt}"


echo. > output\results9.txt

echo test_9 >> output\results9.txt

echo Expected data: >> output\results9.txt
type expected_output\test9.txt >> output\results9.txt
echo. >> output\results9.txt
echo. >> output\results9.txt

echo Received data: >> output\results9.txt
powershell -Command "& {..\Executable\ConvertingInequalityToOperationLess.exe input\test9.txt output\ps_results.txt}"
type output\ps_results.txt >> output\results9.txt
powershell -Command "& {rm output\ps_results.txt}"


echo. > output\results10.txt

echo test_10 >> output\results10.txt

echo Expected data: >> output\results10.txt
type expected_output\test10.txt >> output\results10.txt
echo. >> output\results10.txt
echo. >> output\results10.txt

echo Received data: >> output\results10.txt
powershell -Command "& {..\Executable\ConvertingInequalityToOperationLess.exe input\test10.txt output\ps_results.txt}"
type output\ps_results.txt >> output\results10.txt
powershell -Command "& {rm output\ps_results.txt}"