FROM mcr.microsoft.com/windows/servercore:ltsc2022

# download and install Visual Studio 2022 Build Tools
ADD https://aka.ms/vs/17/release/vs_buildtools.exe /temp/vs_buildtools.exe
RUN C:\TEMP\vs_buildtools.exe --quiet --wait --norestart --nocache  \
    --add Microsoft.VisualStudio.Workload.NativeDesktop             \
    --add Microsoft.VisualStudio.Workload.NetCoreTools              \
    --add Microsoft.VisualStudio.Workload.NetCoreBuildTools         \
    --add Microsoft.VisualStudio.Workload.MSBuildTools              \
    --add Microsoft.VisualStudio.Component.VC.CMake.Project         \
    --add Microsoft.VisualStudio.Component.VC.14.30.CLI.Support     \
    --add Microsoft.VisualStudio.Component.Windows10SDK.19041       \
    --add Microsoft.VisualStudio.Component.VC.CMake.Project         \
    --add Microsoft.Component.MSBuild                               \
    --add Microsoft.Component.MSBuild.Redist                        \
    --add Microsoft.VisualStudio.Component.NuGet                    \
    --add Microsoft.Net.Component.4.7.2.SDK                         \
    --add Microsoft.NetCore.Component.SDK                           \
    --add Microsoft.Net.ComponentGroup.DevelopmentPrerequisites     \
    --includeRecommended                                            \
    && del C:\TEMP\vs_buildtools.exe

# install vcpkg
RUN powershell -Command "Set-ExecutionPolicy Bypass -Scope Process -Force;  \
    Invoke-WebRequest https://github.com/microsoft/vcpkg/archive/refs/heads/master.zip -OutFile C:\temp\vcpkg.zip -UseBasicParsing; \
    Expand-Archive C:\temp\vcpkg.zip -DestinationPath C:\temp\vcpkg;    \
    Move-Item -Path C:\temp\vcpkg\vcpkg-master -Destination C:\vcpkg;   \
    C:\vcpkg\bootstrap-vcpkg.bat;                                       \
    del C:\temp\vcpkg.zip"

# install ProtocolBuffer
RUN powershell -Command "Set-ExecutionPolicy Bypass -Scope Process -Force;  \
    C:\vcpkg\vcpkg install protobuf:x64-windows-static"

# set environment variables for Visual Studio and Protocol Buffer compiler
ENV PATH="C:\vcpkg\installed\x64-windows-static\lib;C:\vcpkg\installed\x64-windows-static\include;C:\vcpkg\installed\x64-windows-static\bin;C:\vcpkg\installed\x64-windows-static\tools\protobuf;\
C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin;C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.30.30705\bin\Hostx64\x64;C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin;\
C:\Program Files\dotnet;\
${PATH}"

WORKDIR C:\\build
COPY . .
