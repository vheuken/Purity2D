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
#Message formats
messageFormat="\n${blue}%s${clearFormat}\n\n"
successFormat="\n${green}%s${clearFormat}\n\n"
#Prints directory in cyan
location="${cyan}`pwd`${clearFormat}"
#Need header $
#$header="printf $Headerformat %s"


printf "${headerFormat}" "Configuring build environment"
printf "${messageFormat}" "Working in `pwd`"
export BUILD_HOME=`pwd` \
         && printf "${messageFormat}" "Created \${BUILD_HOME} at ${BUILD_HOME}"
mkdir android-sdk \
         && export ANDROID_SDK=${BUILD_HOME}/android-sdk \
         && printf "${messageFormat}" "Created \${ANDROID_SDK} at ${ANDROID_SDK}"
mkdir android-ndk \
         && export ANDROID_NDK=${BUILD_HOME}/android-ndk \
         && printf "${messageFormat}" "Created \${ANDROID_NDK} at ${ANDROID_NDK}"
mkdir bin \
         && export BUILD_BIN=${BUILD_HOME}/bin \
         && printf "${messageFormat}" "Created \${BUILD_BIN} at ${BUILD_BIN}"
mkdir release \
         && export BUILD_RELEASE=${BUILD_HOME}/release \
         && printf "${messageFormat}" "Created \${BUILD_RELEASE} at ${BUILD_RELEASE}"
export PATH=$PATH:${ANDROID_SDK}/tools:${ANDROID_SDK}/platform-tools \
         && printf "${messageFormat}" "Added \${ANDROID_SDK}/tools and \${ANDROID_SDK}/platform-tools to \$PATH"

#Need generic libraries, the following only works on Ubuntu 12.04
printf "${headerFormat}" "Installing i386 architecture libraries"
sudo apt-get -qqy update
sudo apt-get -qqy install libc6-i386 lib32stdc++6 lib32gcc1 lib32ncurses5 lib32z1


printf "${headerFormat}" "Installing core Android development packages"
printf "$messageFormat" "Downloading and extracting Android SDK"
curl --location http://dl.google.com/android/android-sdk_r23.0.2-linux.tgz \
         | tar -zx \
         && mv android-sdk-linux/* android-sdk \
         && rmdir android-sdk-linux \
         && printf "${messageFormat}" "Extracted Android NDK to ${ANDROID_SDK}"
printf "${messageFormat}" "Downloading and extracting Android NDK"
curl --location http://dl.google.com/android/ndk/android-ndk32-r10-linux-x86_64.tar.bz2 \
         | tar -jx \
         && mv android-ndk-r10/* android-ndk \
         && rmdir android-ndk-r10 \
         && printf "${messageFormat}" "Extracted Android NDK to ${ANDROID_NDK}"

#Workaround to allow Android SDK update automation, hardcoded for Android  API 20 (4.4W). 
printf "${headerFormat}" "Updating Android SDK"
( sleep 5 && while [ 1 ]; do sleep 1; echo y; done ) | android update sdk --no-ui \
         --filter "platform-tools, build-tools-20.0.0, android-20"
printf "${messageFormat}" "Finished updating Android SDK"


printf "${headerFormat}" "Building binaries"
bash ${ANDROID_NDK}/build/tools/make-standalone-toolchain.sh

mkdir build && cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/android.toolchain.cmake \
         -DANDROID_NATIVE_API_LEVEL=android-19
		
cmake --build . -- -j4 && cd ${BUILD_HOME}


printf "${headerFormat}" "Starting package build"
cd ${BUILD_HOME}
android update project \
         --name purity2d-build --path . --target "android-20"
printf "${messageFormat}" "Building debug packages"
ant debug
printf "${messageFormat}" "Building release packages"
ant release
#Clarifying names to make packages easier to identify
printf "${messageFormat}" "Semantic fixes"
cd ${BUILD_BIN}
mv purity2d-build-debug.apk purity2d-build-debug-aligned.apk
mv purity2d-build-release-unsigned.apk purity2d-build-release-unsigned-unaligned.apk
printf "${messageFormat}" "Done"


printf "${headerFormat}" "Generating signatures for signed packages"
#Needs to be refined.
cd ${BUILD_BIN}
keytool -genkey -noprompt \
         -alias alias_name \
         -dname "CN=, OU=, O=, L=, S=, C=" \
         -keystore keystore \
         -storepass password \
         -keypass password \
         -keyalg RSA \
         -keysize 2048 \
         -validity 10000 \
&& printf "${messageFormat}" "Generated signature in ${BUILD_BIN}"


printf "${headerFormat}" "Creating signed release package"
cd ${BUILD_BIN}
cp purity2d-build-release-unsigned-unaligned.apk signing.apk \
         && jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 \
                 -keystore keystore -storepass password signing.apk alias_name \
         && mv signing.apk purity2d-build-release-signed-unaligned.apk \
         && printf "${messageFormat}" "Signed package"


printf "${headerFormat}" "Aligning release package archives"
#Workaround for zipalign, hardcoded for API 20 (4.4W)
cd ${BUILD_BIN}
export PATH=$PATH:$ANDROID_SDK/build-tools/20.0.0 \
         && printf "${messageFormat}" "Added \$ANDROID_SDK/build-tools/20.0.0 to \$PATH"
printf "${messageFormat}" "Aligning signed package archive"
zipalign -v 4 purity2d-build-release-signed-unaligned.apk purity2d-build-release-signed-aligned.apk
printf "${messageFormat}" "Aligning unsigned package archive"
zipalign -v 4 purity2d-build-release-unsigned-unaligned.apk purity2d-build-release-unsigned-aligned.apk


printf "${headerFormat}" "Validating package signatures"
cd ${BUILD_BIN}
printf "${messageFormat}" "Verifying aligned package"
jarsigner -verify -certs purity2d-build-release-signed-aligned.apk
printf "${messageFormat}" "Verifying unaligned package"
jarsigner -verify -certs purity2d-build-release-signed-unaligned.apk


printf "${headerFormat}" "Gathering final release files"
cd ${BUILD_BIN}
printf "${messageFormat}" "Contents of ${BUILD_BIN}"
ls -a
printf "${messageFormat}" "Exporting release files"
cp *.apk ${BUILD_RELEASE} \
         && printf "${messageFormat}" "Copied release files to ${BUILD_RELEASE}"


printf "${headerFormat}" "Available release:"
cd ${BUILD_RELEASE}
ls -1
#ls | cat


