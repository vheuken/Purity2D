echo Adding DXSDK to PATH
SET DXSDK_DIR=%ProgramFiles(x86)%\Windows Kits

echo Showing PATH
set

:: Workaround for sh.exe in PATH
echo Using workaround for sh.exe
ren "C:/Program Files (x86)/Git/bin/sh.exe" shworkaround

echo Building
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
echo Is MinGW pathed?
mingw32-make.exe all

:: Undoing workaround
echo Correcting workaround for sh.exe
ren "C:/Program Files (x86)/Git/bin/shworkaround" sh.exe


:: MSBuild Purity2D.sln
