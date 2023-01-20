$VM_NAME = $args[0]
$LOCAL_TEST_DRIVER_PATH = $args[1]
$LOCAL_USERMODE_ADAPTER_PATH = $args[2]

$TEST_SERVICE_NAME = "drvut_test"
$DRVUT_TEST_PORT = "33333"
$TEST_DIR = "C:\test"

$username = "User"
$password = ConvertTo-SecureString "Password1!" -AsPlainText -Force
$cred = New-Object System.Management.Automation.PSCredential ($username, $password)

Start-VM -Name "$VM_NAME"

# remove the old service if exists 
Invoke-Command -VMName "$VM_NAME" -Credential $cred -ScriptBlock { 
    $testService = Get-Service $Using:TEST_SERVICE_NAME
    if ($null -ne $testService) {
        sc.exe stop $Using:TEST_SERVICE_NAME
        sc.exe delete $Using:TEST_SERVICE_NAME
    }
}

Copy-VMFile "$VM_NAME" -SourcePath "$LOCAL_TEST_DRIVER_PATH" -DestinationPath "$TEST_DIR\drvut_test_driver.sys" -FileSource Host -Force -CreateFullPath
Copy-VMFile "$VM_NAME" -SourcePath "$LOCAL_USERMODE_ADAPTER_PATH" -DestinationPath "$TEST_DIR\drvut_udermode.exe" -FileSource Host -Force -CreateFullPath

Invoke-Command -VMName "$VM_NAME" -Credential $cred -ScriptBlock {
    sc.exe create $Using:TEST_SERVICE_NAME type= kernel binPath= $Using:TEST_DIR\drvut_test_driver.sys
    sc.exe start $Using:TEST_SERVICE_NAME
    Invoke-Expression -Command "$Using:TEST_DIR\drvut_udermode.exe 0.0.0.0 $Using:DRVUT_TEST_PORT"
}
