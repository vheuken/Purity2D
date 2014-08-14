mkdir build
cd build
cmake -G Xcode -DVIDEO_X11=OFF ..
xcodebuild
