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



# sets up build environment for Ubuntu 12.04 (used by Travis-CI)
printf "${headerFormat}" "Installing and setting compiler"
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test # GCC 4.7
sudo apt-get -qq update
sudo apt-get -qq install g++-4.7
[[ $CXX == "g++" ]] && export CXX=g++-4.7 && export CC=gcc-4.7


printf "${headerFormat}" "Installing libraries"
sudo apt-get install -qqy libpthread-stubs0-dev libgl1-mesa-dev libglu1-mesa-dev libx11-dev libxrandr-dev \
         && printf "${messageFormat}" "Done"


printf "${headerFormat}" "Building binaries"
mkdir build && cd build

cmake .. 

make -j4


printf "${headerFormat}" "Building packages"
cd ${BUILD_BIN}
mkdir purity2d-build 
cp * purity2d-build
cp -r ${BUILD_ASSETS}/* purity2d-build
tar -czf purity2d-build.tgz purity2d-build \
         && printf "${messageFormat}" "Done"


printf "${headerFormat}" "Gathering final release files"
cd ${BUILD_BIN}
printf "${messageFormat}" "Contents of ${BUILD_BIN}"
ls -a
printf "${messageFormat}" "Exporting release (TGZ) files"
cp *.tgz ${BUILD_RELEASE} \
         && printf "${messageFormat}" "Copied release files to ${BUILD_RELEASE}"


printf "${headerFormat}" "Available releases:"
cd ${BUILD_RELEASE}
ls -1
#ls | cat
