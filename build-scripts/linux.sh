# sets up build environment for Ubuntu 12.04 (used by Travis-CI)
sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test # GCC 4.7
sudo apt-get -qq update
sudo apt-get -qq install g++-4.7
[[ $CXX == "g++" ]] && export CXX=g++-4.7 && export CC=gcc-4.7

sudo apt-get install libpthread-stubs0-dev libgl1-mesa-dev libglu1-mesa-dev libx11-dev libxrandr-dev

mkdir build
cd build

cmake .. 

make -j4
