#Requires -Version 3

# Issue present on Appveyor
Write-Host "Using workarounds for CMake errors"
Rename-Item `
         "C:\Program Files (x86)\Git\bin\sh.exe" `
         "shworkaround"
Remove-Item `
         -Recurse `
         -Force `
         "C:\MinGW"

Write-Host Creating "`${Env:BUILD_HOME}" in (Get-Location)
${Env:BUILD_HOME} = Get-Location

Write-Host "Installing MinGW"
Invoke-WebRequest `
         -Uri "http://iweb.dl.sourceforge.net/project/mingwbuilds/host-windows/releases/4.8.1/32-bit/threads-posix/sjlj/x32-4.8.1-release-posix-sjlj-rev5.7z" `
         -Outfile x32-4.8.1-release-posix-sjlj-rev5.7z
7z `
         -t7z `
         "x32-4.8.1-release-posix-sjlj-rev5.7z" `
         -o"${Env:ProgramFiles(x86)}\mingw-builds\x32-4.8.1-release-posix-sjlj-rev5\"

Write-Host "Adding MinGW to `${Env:Path}"
${Env:Path} = ${Env:Path} + ";${Env:ProgramFiles(x86)}\mingw-builds\x32-4.8.1-release-posix-sjlj-rev5\mingw32\bin"

Write-Host Creating "`${Env:BUILD_BIN}" in (Get-Location)\bin
New-Item "${Env:BUILD_HOME}\bin" `
         -ItemType directory `
         -Force `
         ; ${Env:BUILD_BIN} = "${Env:BUILD_HOME}\bin"

Write-Host Creating "`${Env:BUILD_ASSETS}" in (Get-Location)\assets
New-Item "${Env:BUILD_HOME}\assets" `
         -ItemType directory `
         -Force `
         ; ${Env:BUILD_ASSETS} = "${Env:BUILD_HOME}\assets"

Write-Host Creating "`${Env:BUILD_RELEASE}" in (Get-Location)\release
New-Item "${Env:BUILD_HOME}\release" `
         -ItemType directory `
         -Force `
         ; ${Env:BUILD_RELEASE} = "${Env:BUILD_HOME}\release"

Write-Host "Creating `${DXSDK_DIR} at ${Env:ProgramFiles(x86)}\Microsoft DirectX SDK"
Set-Variable `
         -Name "DXSDK_DIR" `
         -Value "${Env:ProgramFiles(x86)}\Microsoft DirectX SDK"

Write-Host "Starting build"
New-Item "${Env:BUILD_HOME}\build" `
         -ItemType directory `
         -Force
Set-Location ${Env:BUILD_HOME}\build
cmake -G "MinGW Makefiles" ..
mingw32-make.exe all
