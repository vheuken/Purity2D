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
sudo apt-get install -qqy libpthread-stubs0-dev libgl1-mesa-dev libglu1-mesa-dev libx11-dev libxrandr-dev


printf "${headerFormat}" "Building binaries"
mkdir build && cd build

cmake .. 

make -j4


printf "${headerFormat}" "Test"
printf "${messageFormat}" "Showing ${BUILD_HOME}"
ls -l ${BUILD_HOME}
printf "${messageFormat}" "Showing ${BUILD_BIN}"
ls -l ${BUILD_BIN}
printf "${messageFormat}" "${BUILD_HOME}/assets"
ls -l ${BUILD_HOME}/assets

