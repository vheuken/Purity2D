wget http://dl.google.com/android/ndk/android-ndk32-r10-linux-x86_64.tar.bz2
tar xf android-ndk32-r10-linux-x86_64.tar.bz2

export ANDROID_NDK=`pwd`/android-ndk-r10

bash $ANDROID_NDK/build/tools/make-standalone-toolchain.sh

mkdir build && cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE=../cmake/toolchains/android.toolchain.cmake \
         -DANDROID_NATIVE_API_LEVEL=android-19
		
cmake --build . -- -j4