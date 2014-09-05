SET DXSDK_DIR=C:\Program Files x86\Windows Kits

mkdir build
cd build
cmake -G "MinGW Makefiles" ..
echo Is MinGW pathed?
mingw32-make.exe all
#MSBuild Purity2D.sln
