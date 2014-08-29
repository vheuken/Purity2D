#Formatting
#Header
headerFormat="\n\n\e[1;34m %s \e[0m\n\n"
#Need header
#$header="printf $Headerformat %s"

printf "$headerFormat" "Working in location: `pwd`"
export BUILD_HOME=`pwd` &&\
         printf "Created \$BUILD_HOME at `pwd`\n"

printf "$headerFormat" "Installing core Android development packages"
printf "Downloading and extracting Android NDK\n"
curl --location http://dl.google.com/android/ndk/android-ndk32-r10-linux-x86_64.tar.bz2 \
         | tar -jx &&\
         printf "Extracted Android NDK to `pwd`\n"

printf "Downloading and extracting Android SDK\n"
curl --location http://dl.google.com/android/android-sdk_r23.0.2-linux.tgz \
         | tar -zx &&\
         printf "Extracted Android NDK to `pwd`\n"

printf "$headerFormat" "Configuring build environment"
export ANDROID_NDK=`pwd`/android-ndk-r10 &&\
         printf "Created \$ANDROID_NDK at `pwd`/android-ndk-r10\n"
export ANDROID_SDK=`pwd`/android-sdk-linux &&\
         printf "Created \$ANDROID_SDK at `pwd`/android-sdk-linux\n"
export PATH=$PATH:$ANDROID_SDK/tools:$ANDROID_SDK/platform-tools &&\
         printf "Added \$ANDROID_SDK/tools and \$ANDROID_SDK/platform-tools to \$PATH\n"

#Workaround to allow Android SDK update automation, hard coded for "android-20"
printf "$headerFormat" "Updating Android SDK"
( sleep 5 && while [ 1 ]; do sleep 1; echo y; done ) | android update sdk --no-ui --filter "android-20"
printf "$headerFormat" "Finished updating Android SDK"

printf "$headerFormat" "Building engine"
bash $ANDROID_NDK/build/tools/make-standalone-toolchain.sh

mkdir build && cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/android.toolchain.cmake \
         -DANDROID_NATIVE_API_LEVEL=android-19
		
cmake --build . -- -j4 && cd $BUILD_HOME

printf "$headerFormar" "Building APK"
cd $BUILD_HOME
android update project \
         --name purity2d-build --path . --target "android-20"

#Failing due to missing 32bit libraries
ant debug





