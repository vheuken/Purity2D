

printf "\n\n\e[1;34mWorking in location: `pwd`\e[0m\n\n"
export BUILD_HOME=`pwd` &&\
         printf "Created \$BUILD_HOME at `pwd`\n"

printf "\n\n\e[1;34mInstalling core Android development packages\e[0m\n\n"
printf "Downloading and extracting Android NDK\n"
curl --location http://dl.google.com/android/ndk/android-ndk32-r10-linux-x86_64.tar.bz2 \
         | tar -jx &&\
         printf "Extracted Android NDK to `pwd`\n"

printf "Downloading and extracting Android SDK\n"
curl --location http://dl.google.com/android/android-sdk_r23.0.2-linux.tgz \
         | tar -zx &&\
         printf "Extracted Android NDK to `pwd`\n"

printf "\n\n\e[1;34mConfiguring build environment\e[0m\n\n"
export ANDROID_NDK=`pwd`/android-ndk-r10 &&\
         printf "Created \$ANDROID_NDK at `pwd`/android-ndk-r10\n"
export ANDROID_SDK=`pwd`/android-sdk-linux &&\
         printf "Created \$ANDROID_SDK at `pwd`/android-sdk-linux\n"
export PATH=$PATH:$ANDROID_SDK/tools:$ANDROID_SDK/platform-tools &&\
         printf "Added \$ANDROID_SDK/tools and \$ANDROID_SDK/platform-tools to \$PATH\n"

#Workaround to allow Android SDK update automation
printf "\n\n\e[1;34mUpdating Android SDK\e[0m\n\n"
( sleep 5 && while [ 1 ]; do sleep 1; echo y; done ) | android update sdk --no-ui #--filter "android-20"
printf "\n\n\e[1;34mFinished updating Android SDK\e[0m\n\n"

printf "\n\n\e[1;34mBuilding engine\e[0m\n\n"
bash $ANDROID_NDK/build/tools/make-standalone-toolchain.sh

mkdir build && cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/android.toolchain.cmake \
         -DANDROID_NATIVE_API_LEVEL=android-19
		
cmake --build . -- -j4 && cd $BUILD_HOME

printf "\n\n\e[1;34mBuilding APK\e[0m\n\n"
cd $BUILD_HOME
android update project \
         --name purity2d-build --path . --target "android-20"

ls -la $ANDROID_SDK/build-tools/20.0.0/

ant debug





