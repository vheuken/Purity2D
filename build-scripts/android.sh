printf "\n\nWorking in location:     `pwd`"

echo "\n\nInstalling core Android development packages"
wget http://dl.google.com/android/ndk/android-ndk32-r10-linux-x86_64.tar.bz2 | tar -x -z &
#wget http://dl.google.com/android/android-sdk_r23.0.2-linux.tgz | tar -x -z &
wait

echo "\n\nConfiguring and updating Android build environment"
export ANDROID_NDK=`pwd`/android-ndk-r10 \
         ANDROID_SDK=`pwd`/android-sdk-linux \
         PATH=$PATH:$ANDROID_SDK/tools:$ANDROID_SDK/platform-tools
#Workaround to allow Android SDK update automation
( sleep 5 && while [ 1 ]; do sleep 1; echo y; done ) | android update sdk --no-ui


bash $ANDROID_NDK/build/tools/make-standalone-toolchain.sh

mkdir build && cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/android.toolchain.cmake \
         -DANDROID_NATIVE_API_LEVEL=android-19
		
cmake --build . -- -j4






