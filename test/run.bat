set TARGET=..\x64\Release\drvut_test_driver_with_props.sys

powershell.exe -ExecutionPolicy Bypass -Command "%DRVUT_PATH%\utilities\hyperv\run-on-vm.ps1 %TEST_MACHINE_NAME% %TARGET% %DRVUT_PATH%\bin\x64\drvut_user.exe"

pause