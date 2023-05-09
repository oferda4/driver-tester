FROM mcr.microsoft.com/windows/servercore:ltsc2022

# download and install Visual Studio 2022 Build Tools
ADD https://aka.ms/vs/17/release/vs_buildtools.exe /temp/vs_buildtools.exe
RUN C:\TEMP\vs_buildtools.exe --quiet --wait --norestart --nocache  \
    --add Microsoft.VisualStudio.Workload.NativeDesktop --includeRecommended --add Microsoft.VisualStudio.Workload.NetCoreTools --add Microsoft.VisualStudio.Workload.MSBuildTools  \
    --add Microsoft.VisualStudio.Component.VC.CMake.Project --add Microsoft.VisualStudio.Component.VC.14.30.CLI.Support     \
    --add Microsoft.VisualStudio.Component.Windows10SDK.19041 --add Microsoft.VisualStudio.Component.VC.CMake.Project       \
    --add Microsoft.Component.MSBuild --add Microsoft.Component.MSBuild.Redist                                              \
    && del C:\TEMP\vs_buildtools.exe

# download and install Protocol Buffer compiler
ADD https://github.com/protocolbuffers/protobuf/releases/download/v3.17.3/protoc-3.17.3-win64.zip /temp/protoc.zip
RUN powershell -Command \
    "Expand-Archive C:\temp\protoc.zip -DestinationPath C:\temp\protoc; \ 
    Move-Item C:\temp\protoc\bin\protoc.exe C:\Windows\System32;        \
    del C:\temp\protoc.zip"

# set environment variables for Visual Studio and Protocol Buffer compiler
ENV PATH="C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin;C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.30.30705\bin\Hostx64\x64;C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin;C:\Windows\System32;${PATH}"
ENV INCLUDE="C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.30.30705\include;C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.30.30705\ATLMFC\include;C:\Program Files (x86)\Windows Kits\NETFXSDK\4.8\include\um;C:\Program Files (x86)\Windows Kits\10\include\10.0.19041.0\ucrt;C:\Program Files (x86)\Windows Kits\10\include\10.0.19041.0\shared;C:\Program Files (x86)\Windows Kits\10\include\10.0.19041.0\winrt;C:\Program Files (x86)\Windows Kits\10\include\10.0.19041.0\cppwinrt"
ENV LIB="C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.30.30705\lib\x64;C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Tools\MSVC\14.30.30705\ATLMFC\lib\x64;C:\Program Files (x86)\Windows Kits\NETFXSDK\4.8\lib\um\x64;C:\Program Files (x86)\Windows Kits\10\lib\10.0.19041.0\ucrt\x64;"

# set the working directory for the container
WORKDIR C:\\build

# copy the source code to the container
COPY . .
