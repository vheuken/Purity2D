mkdir build
cd build
cmake -G Xcode -DVIDEO_X11=0 ..
xcodebuild
