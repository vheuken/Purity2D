#Requires -Version 3

Write-Host Creating "`${Env:BUILD_HOME}" in (Get-Location)
${Env:BUILD_HOME} = Get-Location

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

#Write-Host "Downlading DX SDK"
#Invoke-Webrequest `
#         -Uri "http://download.microsoft.com/download/A/E/7/AE743F1F-632B-4809-87A9-AA1BB3458E31/DXSDK_Jun10.exe" `
#         -Outfile "${Env:BUILD_HOME}\DXSDK_Jun10.exe"

#Write-Host "Installing DX SDK"
## /S skips prinstallation checks
## /O skips operating system checks
## /U does a silent install
## /P sets the installation path, default "${Env:Programfiles(x86)}\DirectX SDK (June 2010)"
#.\DXSDK_Jun10.exe /S /O /U /P "${Env:SystemDrive}\DXSDK"

Set-Variable `
         -Name "DXSDK_DIR" `
         -Value "${Env:ProgramFiles(x86)}\Microsoft DirectX SDK" `
         ; Write-Host "DXSDK_DIR at ${Env:DXSDK_DIR}" `
         ; Get-ChildItem ${Env:DXSDK_DIR}

Write-Host "Starting build"
New-Item "${Env:BUILD_HOME}\build" `
         -ItemType directory `
         -Force
Set-Location ${Env:BUILD_HOME}\build
cmake ..
MSBuild Purity2D.sln










