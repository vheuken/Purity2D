echo Adding DXSDK to PATH
echo.
SET DXSDK_DIR=%ProgramFiles(x86)%\Windows Kits
echo.

echo Showing PATH
echo.
set
echo.

:: Workaround for sh.exe in PATH
echo Using workaround for sh.exe
echo.
dir "C:/Program Files (x86)/Git/bin/"
echo.
rename "C:/Program Files (x86)/Git/bin/sh.exe" shworkaround
echo.
dir "C:/Program Files (x86)/Git/bin/"
echo.

echo Building
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
echo Is MinGW pathed?
mingw32-make.exe all

:: Undoing workaround
echo Correcting workaround for sh.exe
rename "C:/Program Files (x86)/Git/bin/shworkaround" sh.exe


:: MSBuild Purity2D.sln
