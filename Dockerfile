FROM mcr.microsoft.com/windows/servercore:ltsc2022

ENV DRIVER_SERVICE_NAME drvut_tester

COPY x64/Debug/drvut_user.exe C:\\drvut_user.exe
COPY x64\\Debug\\drvut_test_driver.sys C:\\drvut_test_driver.sys

RUN sc create $DRIVER_SERVICE_NAME type= kernel binPath= C:\\drvut_test_driver.sys
RUN sc start $DRIVER_SERVICE_NAME
RUN sc query $DRIVER_SERVICE_NAME

CMD "C:\\drvut_user.exe 0.0.0.0 33333"