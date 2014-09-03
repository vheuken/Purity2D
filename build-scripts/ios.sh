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


printf "${headerFormat}" "Configuring build environment"
export BUILD_HOME=`pwd` \
         && printf "${messageFormat}" "Created \${BUILD_HOME} at ${BUILD_HOME}"
mkdir -p bin \
         && export BUILD_BIN=${BUILD_HOME}/bin \
         && printf "${messageFormat}" "Created \${BUILD_BIN} at ${BUILD_BIN}"
mkdir -p assets \
         && export BUILD_ASSETS=${BUILD_HOME}/assets \
         && printf "${messageFormat}" "Created \${BUILD_ASSETS} at ${BUILD_ASSETS}"
mkdir -p release \
         && export BUILD_RELEASE=${BUILD_HOME}/release \
         && printf "${messageFormat}" "Created \${BUILD_RELEASE} at ${BUILD_RELEASE}"









mkdir build
cd build 
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/iOS.cmake -DIOS_PLATFORM=SIMULATOR -G Xcode ..
xcodebuild



printf "${headerFormat}" "Tests"
printf "${messageFormat}" "Contents of `pwd`"
pwd
ls -A
printf "${messageFormat}" "Contents of ${BUILD_HOME}"
cd ${BUILD_HOME}
pwd
ls -A
printf "${messageFormat}" "Contents of ${BUILD_BIN}"
cd ${BUILD_BIN}
pwd
ls -A













printf "${headerFormat}" "Gathering final release files"
cd ${BUILD_BIN}
printf "${messageFormat}" "Contents of ${BUILD_BIN}"
ls -a
printf "${messageFormat}" "Exporting release files"
cp *.tgz ${BUILD_RELEASE} \
         && printf "${messageFormat}" "Copied release files to ${BUILD_RELEASE}"


printf "${headerFormat}" "Available releases:"
cd ${BUILD_RELEASE}
ls -1
#ls | cat




