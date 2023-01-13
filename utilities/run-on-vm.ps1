$VM_NAME=$args[0]
$LOCAL_TEST_DRIVER_PATH=$args[1]
$LOCAL_USERMODE_ADAPTER_PATH=$args[2]

$TEST_SERVICE_NAME=drvut_test

# remove the old service if exists 
$testServie=Get-WmiObject -Class Win32_Service -Filter "Name='$TEST_SERVICE_NAME'"
if ($testServie -ne $null) {
    $testServie.stop()
    $testServie.delete()
}

# remove old test files if exist
$TEST_DIR=C:\\test
if (Test-Path $TEST_DIR) {
    Remove-Item $TEST_DIR -Force
}

Copy-VMFile "$VM_NAME" -SourcePath $LOCAL_TEST_DRIVER_PATH -DestinationPath $TEST_DIR\\drvut_test_driver.sys
Copy-VMFile "$VM_NAME" -SourcePath $LOCAL_USERMODE_ADAPTER_PATH -DestinationPath $TEST_DIR\\drvut_udermode.exe

RUN powershell.exe -Command Invoke-Command -VMName "$VM_NAME" -ScriptBlock "sc.exe create $TEST_SERVICE_NAME type= kernel binPath= $TEST_DIR\\drvut_test_driver.sys"
RUN powershell.exe -Command Invoke-Command -VMName "$VM_NAME" -ScriptBlock "sc.exe start $TEST_SERVICE_NAME"
