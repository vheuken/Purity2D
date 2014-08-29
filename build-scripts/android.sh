#Formatting
#Header
startHeader="\n\n\e[1;34m"
endHeader="\e[0m\n\n"

printf "$startHeader Working in location: `pwd` $endHeader"
export BUILD_HOME=`pwd` &&\
         printf "Created \$BUILD_HOME at `pwd`\n"

printf "$startHeader Installing core Android development packages $endHeader"
printf "Downloading and extracting Android NDK\n"
curl --location http://dl.google.com/android/ndk/android-ndk32-r10-linux-x86_64.tar.bz2 \
         | tar -jx &&\
         printf "Extracted Android NDK to `pwd`\n"

printf "Downloading and extracting Android SDK\n"
curl --location http://dl.google.com/android/android-sdk_r23.0.2-linux.tgz \
         | tar -zx &&\
         printf "Extracted Android NDK to `pwd`\n"

printf "$startHeader Configuring build environment $endHeader"
export ANDROID_NDK=`pwd`/android-ndk-r10 &&\
         printf "Created \$ANDROID_NDK at `pwd`/android-ndk-r10\n"
export ANDROID_SDK=`pwd`/android-sdk-linux &&\
         printf "Created \$ANDROID_SDK at `pwd`/android-sdk-linux\n"
export PATH=$PATH:$ANDROID_SDK/tools:$ANDROID_SDK/platform-tools &&\
         printf "Added \$ANDROID_SDK/tools and \$ANDROID_SDK/platform-tools to \$PATH\n"

#Workaround to allow Android SDK update automation
printf "$startHeader Updating Android SDK $endHeader"
( sleep 5 && while [ 1 ]; do sleep 1; echo y; done ) | android update sdk --no-ui #--filter "android-20"
printf "$startHeader Finished updating Android SDK $endHeader"

printf "$startHeader Building engine $endHeader"
bash $ANDROID_NDK/build/tools/make-standalone-toolchain.sh

mkdir build && cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/android.toolchain.cmake \
         -DANDROID_NATIVE_API_LEVEL=android-19
		
cmake --build . -- -j4 && cd $BUILD_HOME

printf "$startHeader Building APK $endHeader"
cd $BUILD_HOME
android update project \
         --name purity2d-build --path . --target "android-20"

#Failing due to missing 32bit libraries
ant debug





