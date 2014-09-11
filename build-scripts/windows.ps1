#Requires -Version 3


Write-Output "Downlading DX SDK"
Invoke-Webrequest "http://download.microsoft.com/download/A/E/7/AE743F1F-632B-4809-87A9-AA1BB3458E31/DXSDK_Jun10.exe" -Outfile "C:\DXSDK.exe"

Write-Output "Changing to C:\"
Set-Location C:\

Write-Output "Displaying contents of C:\"
Get-Location

Write-Output "Installing DX SDK"
