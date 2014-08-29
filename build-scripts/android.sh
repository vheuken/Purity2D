#Formatting
#Header format
headerFormat="\n\n\e[1;34m%s\e[0m\n\n"
#Need header $
#$header="printf $Headerformat %s"


printf "$headerFormat" "Working in location: `pwd`"
export BUILD_HOME=`pwd` &&\
         printf "Created \$BUILD_HOME at `pwd`\n"


#Need generic libraries, the following only works on Ubuntu 12.04
printf "$headerFormat" "Installing i386 architecture libraries"
sudo apt-get -qqy update
sudo apt-get -qqy install libc6-i386 lib32stdc++6 lib32gcc1 lib32ncurses5 lib32z1


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
cd $BUILD_HOME
export ANDROID_NDK=./android-ndk-r10 &&\
         printf "Created \$ANDROID_NDK at `pwd`/android-ndk-r10\n"
export ANDROID_SDK=./android-sdk-linux &&\
         printf "Created \$ANDROID_SDK at `pwd`/android-sdk-linux\n"
export PATH=$PATH:$ANDROID_SDK/tools:$ANDROID_SDK/platform-tools &&\
         printf "Added \$ANDROID_SDK/tools and \$ANDROID_SDK/platform-tools to \$PATH\n"


#Workaround to allow Android SDK update automation
printf "$headerFormat" "Updating Android SDK"
( sleep 5 && while [ 1 ]; do sleep 1; echo y; done ) | android update sdk --no-ui
#         --filter "platform-tools, build-tools-20.0.0, android-20, build-tools-19"
printf "$headerFormat" "Finished updating Android SDK"


printf "$headerFormat" "Building binaries"
bash $ANDROID_NDK/build/tools/make-standalone-toolchain.sh

mkdir build && cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/android.toolchain.cmake \
         -DANDROID_NATIVE_API_LEVEL=android-19
		
cmake --build . -- -j4 && cd $BUILD_HOME


printf "$headerFormat" "Starting APK build"
cd $BUILD_HOME
android update project \
         --name purity2d-build --path . --target "android-20"


printf "$headerFormat" "Building debug APK"
ant debug


printf "$headerFormat" "Building release APK"
ant release

printf "$headerFormat" "Generating signature"
#Needs to be refined.
keytool -genkey -noprompt \
         -alias alias_name \
         -dname "CN=, OU=, O=, L=, S=, C=" \
         -keystore keystore \
         -storepass password \
         -keypass password \
         -keyalg RSA \
         -keysize 2048 \
         -validity 10000 &&\
         printf "Generated signature\n"


printf "$headerFormat" "Signing APK"
jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 \
         -keystore keystore -storepass password ./bin/purity2d-build-release-unsigned.apk alias_name &&\
         mv ./bin/purity2d-build-release-unsigned.apk ./bin/purity2d-build-release-signed.apk
         printf "Signed APK\n"

printf "$headerFormat" "Validating build"
cd $BUILD_HOME
ls -la ./bin

jarsigner -verify -verbose -certs ./bin/purity2d-build-release-signed.apk

printf "$headerFormat" "Validating build again"
ls -la ./bin

