#Requires -Version 3

${Env:BUILD_OS} = "Windows"

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
7z.exe x `
         -t7z `
         "x32-4.8.1-release-posix-sjlj-rev5.7z" `
         -o"${Env:ProgramFiles(x86)}\mingw-builds\x32-4.8.1-release-posix-sjlj-rev5\" `
         | Find /V "Extracting " # 7z.exe does not have a quiet mode


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


Write-Host "Building binaries"
New-Item "${Env:BUILD_HOME}\build" `
         -ItemType directory `
         -Force
Set-Location "${Env:BUILD_HOME}\build"
cmake.exe -G "MinGW Makefiles" ..
mingw32-make.exe all


Write-Host "Building packages"
Set-Location "${Env:BUILD_BIN}"
New-Item ".\purity2d-build" `
         -ItemType directory `
         -Force
Copy-Item `
         -Path ".\*.exe" `
         -Destination ".\purity2d-build\"
Copy-Item `
         -Path "${Env:BUILD_ASSETS}\*" `
         -Destination ".\purity2d-build\" `
         -Recurse
7z.exe a `
         -tzip `
         "purity2d-build.zip" `
         .\purity2d-build


Write-Host "Gathering final release files"
Set-Location "${Env:BUILD_BIN}"
Write-Host "Contents of ${Env:BUILD_BIN}"
Get-ChildItem
Write-Host "Exporting release (ZIP) files"
Copy-Item `
         -Path ".\*.zip" `
         -Destination "${Env:BUILD_RELEASE}\"


Write-Host "Available releases:"
Set-Location "${Env:BUILD_RELEASE}"
Get-ChildItem -Name

Write-Host "Cleaning workaround for CMake errors"
Rename-Item `
         "C:\Program Files (x86)\Git\bin\shworkaround" `
         "sh.exe"

sh.exe --login -i "${Env:APPVEYOR_BUILD_FOLDER}\build-scripts\ci\appveyor\update-gh-pages.sh" | Out-File test.txt

Get-Content test.txt






