SET DXSDK_DIR="C:\Program Files x86\Windows Kits\"

mkdir build
cd build
cmake ..
MSBuild Purity2D.sln
