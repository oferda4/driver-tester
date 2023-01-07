FROM mcr.microsoft.com/windows/servercore:ltsc2022

COPY x64/Debug/drvut_user.exe C:\\drvut_user.exe
COPY x64\\Debug\\drvut_test_driver.sys C:\\drvut_test_driver.sys

RUN sc create tester_drvut type= kernel binPath= C:\\drvut_test_driver.sys
RUN sc start tester_drvut
RUN sc query tester_drvut
CMD "C:\\drvut_user.exe 0.0.0.0 33333"