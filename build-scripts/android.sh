printf "\n\nWorking in location:     `pwd`\n"

printf "\n\nInstalling core Android development packages\n"
curl --location http://dl.google.com/android/ndk/android-ndk32-r10-linux-x86_64.tar.bz2 | tar -jx  &
curl --location http://dl.google.com/android/android-sdk_r23.0.2-linux.tgz | tar -zx &
wait

printf "\n\nConfiguring and updating Android build environment\n"
export ANDROID_NDK=`pwd`/android-ndk-r10 \
         ANDROID_SDK=`pwd`/android-sdk-linux/sdk \
         PATH=$PATH:$ANDROID_SDK/tools:$ANDROID_SDK/platform-tools
printf "\n\nTesting location\n"
ls -la
#Workaround to allow Android SDK update automation
( sleep 5 && while [ 1 ]; do sleep 1; echo y; done ) | android update sdk --no-ui


bash $ANDROID_NDK/build/tools/make-standalone-toolchain.sh

mkdir build && cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/android.toolchain.cmake \
         -DANDROID_NATIVE_API_LEVEL=android-19
		
cmake --build . -- -j4






