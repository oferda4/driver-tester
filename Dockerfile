FROM mcr.microsoft.com/windows/servercore:ltsc2022

ENV DRIVER_SERVICE_NAME drvut_tester
ENV VM_HARD_DRIVE_NAME WinDev2212Eval.vhdx
ENV VM_NAME TestVM
ENV MACHINE_ZIP WinDev2212Eval.HyperV.zip

COPY docker\\machine\\$MACHINE_ZIP C:\\machine\\$MACHINE_ZIP
RUN powershell.exe -Command Expand-Archive C:\\machine\\$MACHINE_ZIP -DestinationPath C:\\machine
RUN powershell.exe -Command Remove-Item C:\\machine\\$MACHINE_ZIP

RUN powershell.exe -Command New-VM -Name "$VM_NAME" -MemoryStartupBytes 4GB -BootDevice VHD -VHDPath C:\\machine\\$VM_HARD_DRIVE_NAME -Path C:\\VMData -Generation 2 -Switch InternalSwitch
RUN powershell.exe -Command Start-VM -Name "$VM_NAME"

COPY x64\\Debug\\drvut_user.exe C:\\drvut_user.exe
RUN powershell.exe -Command Copy-VMFile "$VM_NAME" -SourcePath C:\\drvut_user.exe -DestinationPath C:\\drvut_user.exe
COPY x64\\Debug\\drvut_test_driver.sys C:\\drvut_test_driver.sys
RUN powershell.exe -Command Copy-VMFile "$VM_NAME" -SourcePath C:\\drvut_test_driver.sys -DestinationPath C:\\drvut_test_driver.sys

RUN powershell.exe -Command Invoke-Command -VMName "$VM_NAME" -ScriptBlock "sc.exe create $DRIVER_SERVICE_NAME type= kernel binPath= C:\\drvut_test_driver.sys"
RUN powershell.exe -Command Invoke-Command -VMName "$VM_NAME" -ScriptBlock "sc.exe start $DRIVER_SERVICE_NAME"
RUN powershell.exe -Command Invoke-Command -VMName "$VM_NAME" -ScriptBlock "sc.exe query $DRIVER_SERVICE_NAME"

CMD powershell.exe -Command Invoke-Command -VMName "$VM_NAME" -ScriptBlock "C:\\drvut_user.exe 0.0.0.0 33333"