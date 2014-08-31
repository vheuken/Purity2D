#Formatting
clearFormat="\e[0m"
black="\e[1;30m"
red="\e[1;31m"
green="\e[1;32m"
yellow="\e[1;33m"
blue="\e[1;34m"
magenta="\e[1;35m"
cyan="\e[1;36m"
white="\e[1;37m"
#Prints string in bold blue with many lines of surrounding whitespace.
headerFormat="\n\n\n\n\n${cyan}%s${clearFormat}\n\n"
#Prints string in blue with one line of surrounding whitespace
messageFormat="\n${blue}%s${clearFormat}\n\n"
#Prints directory in cyan
location="${cyan}`pwd`${clearFormat}"
#Need header $
#$header="printf $Headerformat %s"


printf "${headerFormat}" "Working in `pwd`"
export BUILD_HOME=`pwd` &&\
         printf "${messageFormat}" "Created \$BUILD_HOME at `pwd`"


#Need generic libraries, the following only works on Ubuntu 12.04
printf "${headerFormat}" "Installing i386 architecture libraries"
sudo apt-get -qqy update
sudo apt-get -qqy install libc6-i386 lib32stdc++6 lib32gcc1 lib32ncurses5 lib32z1


printf "${headerFormat}" "Installing core Android development packages"
printf "${messageFormat}" "Downloading and extracting Android NDK"
curl --location http://dl.google.com/android/ndk/android-ndk32-r10-linux-x86_64.tar.bz2 \
         | tar -jx \
         && printf "${messageFormat}" "Extracted Android NDK to `pwd`"
printf "$messageFormat" "Downloading and extracting Android SDK"
curl --location http://dl.google.com/android/android-sdk_r23.0.2-linux.tgz \
         | tar -zx \
         && printf "${messageFormat}" "Extracted Android NDK to `pwd`"


printf "${headerFormat}" "Configuring build environment"
export ANDROID_NDK=`pwd`/android-ndk-r10 \
         && printf "${messageFormat}" "Created \$ANDROID_NDK at `pwd`/android-ndk-r10"
export ANDROID_SDK=`pwd`/android-sdk-linux \
         && printf "${messageFormat}" "Created \$ANDROID_SDK at `pwd`/android-sdk-linux"
export PATH=$PATH:$ANDROID_SDK/tools:$ANDROID_SDK/platform-tools \
         && printf "${messageFormat}" "Added \$ANDROID_SDK/tools and \$ANDROID_SDK/platform-tools to \$PATH"


#Workaround to allow Android SDK update automation, hardcoded for Android  API 20 (4.4W). 
printf "${headerFormat}" "Updating Android SDK"
( sleep 5 && while [ 1 ]; do sleep 1; echo y; done ) | android update sdk --no-ui \
         --filter "platform-tools, build-tools-20.0.0, android-20"
printf "${messageFormat}" "Finished updating Android SDK"


printf "${headerFormat}" "Building binaries"
bash $ANDROID_NDK/build/tools/make-standalone-toolchain.sh

mkdir build && cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/android.toolchain.cmake \
         -DANDROID_NATIVE_API_LEVEL=android-19
		
cmake --build . -- -j4 && cd $BUILD_HOME


printf "${headerFormat}" "Starting APK build"
cd $BUILD_HOME
android update project \
         --name purity2d-build --path . --target "android-20"


printf "${headerFormat}" "Building debug APK"
ant debug
#Clarifying semantics
mv ./bin/purity2d-build-debug.apk ./bin/purity2d-build-debug-aligned.apk

printf "${headerFormat}" "Building release APK"
ant release
#Clarifying semantics
mv ./bin/purity2d-build-release-unsigned.apk ./bin/purity2d-build-release-unsigned-unaligned.apk

printf "${headerFormat}" "Generating signature"
#Needs to be refined.
keytool -genkey -noprompt \
         -alias alias_name \
         -dname "CN=, OU=, O=, L=, S=, C=" \
         -keystore keystore \
         -storepass password \
         -keypass password \
         -keyalg RSA \
         -keysize 2048 \
         -validity 10000 \
&& printf "${messageFormat}" "Generated signature"


printf "${headerFormat}" "Creating signed release APK"
cd $BUILD_HOME
cp ./bin/purity2d-build-release-unsigned-unaligned.apk ./bin/signing.apk \
         && jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 \
                 -keystore keystore -storepass password ./bin/signing.apk alias_name \
         && mv ./bin/signing.apk ./bin/purity2d-build-release-signed-unaligned.apk \
         && printf "${messageFormat}" "Signed APK"

printf "${headerFormat}" "Zipaligning APKs"
#Workaround for zipalign, hardcoded for API 20 (4.4W)
ls $ANDROID_SDK/build-tools/20.0.0
export PATH=$PATH:$ANDROID_SDK/build-tools/20.0.0 \
         && printf "${messageFormat}" "Added \$ANDROID_SDK/build-tools/20.0.0 to \$PATH"
printf "${messageFormat}" "Aligning signed APK"
zipalign -v 4 ./bin/purity2d-build-release-signed-unaligned.apk ./bin/purity2d-build-release-signed-aligned.apk
printf "${messageFormat}" "Aligning unsigned APK"
zipalign -v 4 ./bin/purity2d-build-release-unsigned-unaligned.apk ./bin/purity2d-build-release-unsigned-aligned.apk

printf "${headerFormat}" "Validating APK build signatures"
cd $BUILD_HOME
printf "${messageFormat}" "Verifying aligned APK"
jarsigner -verify -certs ./bin/purity2d-build-release-signed-aligned.apk
printf "${messageFormat}" "Verifying unaligned APK"
jarsigner -verify -certs ./bin/purity2d-build-release-signed-unaligned.apk

printf "${headerFormat}" "Contents of `pwd`/bin"
cd $BUILD_HOME
ls -l ./bin

printf "${headerFormat}" "Builds Available:"
cd $BUILD_HOME
ls -l ./bin/*.apk


