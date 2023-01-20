powershell.exe -ExecutionPolicy Bypass -Command "..\utilities\hyperv\run-on-vm.ps1 %TEST_MACHINE_NAME% ..\x64\Debug\drvut_test_driver.sys ..\x64\Debug\drvut_user.exe"

pause