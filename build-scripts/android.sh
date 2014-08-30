#Formatting
tfBold=`tput bold`
tfNormal=`tput sgr0`
tcBlue="\e[1;34m"
tcCyan="\e[1;36m"
tcNormal="\e[0m"
#Prints string in bold blue with three lines of surrounding whitespace.
headerFormat="\n\n\n${tfBold}${tcBlue}%s${tfNormal}${tcNormal}\n\n\n\n"
#Prints string in blue with one line of surrounding whitespace
messageFormat"\n\e${tcBlue}%s${tcNormal}\n\n"
#Prints directory in cyan
location="${tcCyan}`pwd`${tcNormal}"
#Need header $
#$header="printf $Headerformat %s"


printf "$headerFormat" "Working in `pwd`"
export BUILD_HOME=`pwd` &&\
         printf "Created \$BUILD_HOME at $location\n"


#Need generic libraries, the following only works on Ubuntu 12.04
printf "$headerFormat" "Installing i386 architecture libraries"
sudo apt-get -qqy update
sudo apt-get -qqy install libc6-i386 lib32stdc++6 lib32gcc1 lib32ncurses5 lib32z1


printf "$headerFormat" "Installing core Android development packages"
printf "Downloading and extracting Android NDK\n"
curl --location http://dl.google.com/android/ndk/android-ndk32-r10-linux-x86_64.tar.bz2 \
         | tar -jx \
         && printf "Extracted Android NDK to $location\n"
printf "Downloading and extracting Android SDK\n"
curl --location http://dl.google.com/android/android-sdk_r23.0.2-linux.tgz \
         | tar -zx \
         && printf "Extracted Android NDK to $location\n"


printf "$headerFormat" "Configuring build environment"
export ANDROID_NDK=`pwd`/android-ndk-r10 \
         && printf "Created \$ANDROID_NDK at $location/android-ndk-r10\n"
export ANDROID_SDK=`pwd`/android-sdk-linux \
         && printf "Created \$ANDROID_SDK at $location/android-sdk-linux\n"
export PATH=$PATH:$ANDROID_SDK/tools:$ANDROID_SDK/platform-tools \
         && printf "Added \$ANDROID_SDK/tools and \$ANDROID_SDK/platform-tools to \$PATH\n"


#Workaround to allow Android SDK update automation, hardcoded for Android  API 20 (4.4W). 
printf "$headerFormat" "Updating Android SDK"
( sleep 5 && while [ 1 ]; do sleep 1; echo y; done ) | android update sdk --no-ui \
         --filter "platform-tools, build-tools-20.0.0, android-20"
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
#Clarifying semantics
mv ./bin/purity2d-build-debug.apk ./bin/purity2d-build-debug-aligned.apk

printf "$headerFormat" "Building release APK"
ant release
#Clarifying semantics
mv ./bin/purity2d-build-release-unsigned.apk ./bin/purity2d-build-release-unsigned-unaligned.apk

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
         -validity 10000 \
&& printf "Generated signature\n"


printf "$headerFormat" "Creating signed release APK"
cd $BUILD_HOME
cp ./bin/purity2d-build-release-unsigned-unaligned.apk ./bin/signing.apk \
         && jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 \
                 -keystore keystore -storepass password ./bin/signing.apk alias_name \
         && mv ./bin/signing.apk ./bin/purity2d-build-release-signed-unaligned.apk \
         && printf "Signed APK\n"

printf "$headerFormat" "Zipaligning APKs"
#Workaround for zipalign, hardcoded for API 20 (4.4W)
ls $ANDROID_SDK/build-tools/20.0.0
export PATH=$PATH:$ANDROID_SDK/build-tools/20.0.0 \
         && printf "Added \$ANDROID_SDK/build-tools/android-4.4W to \$PATH\n"
printf "Aligning signed APK\n"
zipalign -v 4 ./bin/purity2d-build-release-signed-unaligned.apk ./bin/purity2d-build-release-signed-aligned.apk
printf "Aligning unsigned APK\n"
zipalign -v 4 ./bin/purity2d-build-release-unsigned-unaligned.apk ./bin/purity2d-build-release-unsigned-aligned.apk

printf "$headerFormat" "Validating APK build signatures"
cd $BUILD_HOME
printf "Verifying aligned APK\n"
jarsigner -verify -certs ./bin/purity2d-build-release-signed-aligned.apk
printf "Verifying unaligned APK\n"
jarsigner -verify -certs ./bin/purity2d-build-release-signed-unaligned.apk

printf "$headerFormat" "Builds Available:"
cd $BUILD_HOME
ls -l ./bin/*.apk


