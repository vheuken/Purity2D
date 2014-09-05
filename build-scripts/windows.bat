SET DXSDK_DIR=%ProgramFiles(x86)%\Windows Kits

:: Workaround for sh.exe in PATH
ren "C:/Program Files (x86)/Git/bin/sh.exe" shworkaround

mkdir build
cd build
cmake -G "MinGW Makefiles" ..
echo Is MinGW pathed?
mingw32-make.exe all

:: Undoing workaround
ren "C:/Program Files (x86)/Git/bin/shworkaround" sh.exe


:: MSBuild Purity2D.sln
