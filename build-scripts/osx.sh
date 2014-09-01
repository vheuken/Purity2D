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
mkdir bin \
          && export BUILD_BIN=${BUILD_HOME}/bin \
         && printf "${messageFormat}" "Created \${BUILD_BIN} at ${BUILD_BIN}"
export BUILD_ASSETS=${BUILD_HOME}/assets \
         && printf "${messageFormat}" "Created \${BUILD_ASSETS} at ${BUILD_ASSETS}"
mkdir release \
         && export BUILD_RELEASE=${BUILD_HOME}/release \
         && printf "${messageFormat}" "Created \${BUILD_RELEASE} at ${BUILD_RELEASE}"


printf "${headerFormat}" "Building binaries"
cd ${BUILD_HOME}
mkdir build && cd build
cmake -G Xcode ..
xcodebuild


printf "${headerFormat}" "Tests"
printf "${messageFormat}" "Contents of ${BUILD_HOME}"
ls -a ${BUILD_HOME}
printf "${messageFormat}" "Contents of ${BUILD_BIN}"
ls -a ${BUILD_BIN}
printf "${messageFormat}" "Contents of ${BUILD_BIN}/Debug"
ls -a ${BUILD_BIN}/Debug
printf "${messageFormat}" "Contents of ${BUILD_ASSETS}"
ls -a ${BUILD_ASSETS}
printf "${messageFormat}" "Tests complete"


printf "${headerFormat}" "Building packages"
cd ${BUILD_BIN}
printf "${messageFormat}" "Building debug package"
mkdir purity2d-build 
cp -r Debug/* purity2d-build
cp -r ${BUILD_ASSETS}/* purity2d-build/Purity-Engine.app/Contents/Resources/
zip -r purity2d-build.zip purity2d-build \
         && printf "${messageFormat}" "Done"

printf "${headerFormat}" "Gathering final release files"
cd ${BUILD_BIN}
printf "${messageFormat}" "Contents of ${BUILD_BIN}"
ls -a
printf "${messageFormat}" "Exporting release (ZIP) files"
cp *.zip ${BUILD_RELEASE} \
         && printf "${messageFormat}" "Copied release files to ${BUILD_RELEASE}"


printf "${headerFormat}" "Available releases:"
cd ${BUILD_RELEASE}
ls -1
#ls | cat
