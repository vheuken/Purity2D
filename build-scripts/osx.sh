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
xcodebuild \
         && xcodebuild -configuration Release

printf "${headerFormat}" "Starting package build"

printf "${headerFormat}" "Building debug package"
cd ${BUILD_BIN}
mkdir purity2d-build-debug
cp -R Debug/* purity2d-build-debug/
#OSX does not support the [-p   --parents] option in [cp]
mkdir -p purity2d-build-debug/Purity-Engine.app/Contents/Resources
cp -R ${BUILD_ASSETS}/* purity2d-build-debug/Purity-Engine.app/Contents/Resources/
cd purity2d-build-debug
zip --recurse-paths ../purity2d-build-debug.zip Purity-Engine.app

printf "${headerFormat}" "Building relase package (ZIP)"
cd ${BUILD_BIN}
mkdir purity2d-build-release
cp -R Release/* purity2d-build-release/
#OSX does not support the [-p   --parents] option in [cp]
mkdir -p purity2d-build-release/Purity-Engine.app/Contents/Resources
cp -R ${BUILD_ASSETS}/* purity2d-build-release/Purity-Engine.app/Contents/Resources/
cd purity2d-build-release
zip --recurse-paths ../purity2d-build-release.zip Purity-Engine.app




printf "${headerFormat}" "Building relase package (PKG)"
cd ${BUILD_BIN}
cd purity2d-build-release

printf "${messageFormat}" "Copying APP to `pwd`/app"
mkdir -p app && cp -R Purity-Engine.app ./app/

printf "${messageFormat}" "Running pkgbuild analyze"
pwd
ls -A
pkgbuild --analyze --root ./app 'Purity-Engine.plist'
cd app

printf "${messageFormat}" "Making dummy files"
pwd
ls -A
touch installerImage.png \
         license.txt

printf "${messageFormat}" "Running productbuild synthesize"
pwd
ls -A
productbuild --synthesize \
--package 'Purity-Engine.pkg' \
Distribution.xml

printf "${messageFormat}" "Running productbuild synthesize"
pwd
ls -A
#mkdir resources
#cp ./installerImage.png /resources
#cp ./license.txt /resources
 
#mkdir helper_scripts
#cp ./postinstall 
 
#cp $(SRC)/*.plist .
#cp $(SRC)/Distribution.xml


#chmod -R a+xr 'Purity-Engine.app'
#chmod -R a+xr examples

#printf "${messageFormat}" "Moving APP"
#cp -Rfp 'Purity-Engine.app' app/'Purity-Engine.app'


printf "${messageFormat}" "Done"






printf "${headerFormat}" "Gathering final release files"
cd ${BUILD_BIN}
printf "${messageFormat}" "Contents of ${BUILD_BIN}"
ls -A
printf "${messageFormat}" "Exporting release files"
cp *.zip ${BUILD_RELEASE} \
         && printf "${messageFormat}" "Copied release files to ${BUILD_RELEASE}"


printf "${headerFormat}" "Available packages:"
cd ${BUILD_RELEASE}
ls -1
#ls | cat
