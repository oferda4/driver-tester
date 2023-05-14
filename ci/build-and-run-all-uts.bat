dotnet restore runner\runner\test\runner_tests.csproj

msbuild tester.sln /m /t:"User Mode\drvut_user_tests:Clean" /t:"Kernel Mode\drvut_lib_tests:Clean" /t:"Runner\runner_tests:Clean" /p:Configuration=Release /p:Platform=x64
msbuild tester.sln /m /t:"User Mode\drvut_user_tests" /t:"Kernel Mode\drvut_lib_tests" /t:"Runner\runner_tests" /p:Configuration=Release /p:Platform=x64

x64\Release\drvut_user_tests.exe
x64\Release\drvut_lib_tests.exe
dotnet test runner\runner\test\bin\Release\runner_tests.dll