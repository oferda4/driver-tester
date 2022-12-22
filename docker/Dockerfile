FROM mcr.microsoft.com/dotnet/framework/runtime:4.8-windowsservercore-ltsc2022

SHELL ["cmd", "/S", "/C"]

# Download and install Build Tools for Visual Studio 2022 for native desktop workload.
ADD https://aka.ms/vs/17/release/vs_buildtools.exe C:\TEMP\vs_buildtools.exe
RUN C:\TEMP\Install.cmd C:\TEMP\vs_buildtools.exe --quiet --wait --norestart --nocache \
    --channelUri C:\TEMP\VisualStudio.chman                                            \
    --installChannelUri C:\TEMP\VisualStudio.chman                                     \
    --add Microsoft.VisualStudio.Workload.VCTools --includeRecommended                 \
    --installPath C:\BuildTools

# Use developer command prompt and start PowerShell if no other command specified.
ENTRYPOINT C:\BuildTools\Common7\Tools\VsDevCmd.bat &&
CMD ["powershell.exe", "-NoLogo", "-ExecutionPolicy", "Bypass"]