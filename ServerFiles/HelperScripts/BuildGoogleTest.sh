####################################
# Notes:
# - Put this file in your root GoogleTest repository folder.
# - Configure variables below.
####################################

####################################
# User configuration:
####################################
targetInstallPath=""

####################################
# Script content. Do not edit.
####################################

if [[ $targetInstallPath == "" ]];
then
	echo "You have to properly configure \"targetInstallPath\" variable!"
	exit 1
fi

function build
{
	rm -rf build/
	mkdir build
	cd build
	local cmd="cmake .. -DCMAKE_BUILD_TYPE=$1"
	local platform="x64"
if $2 = true; then
	platform="x86"
	cmd="$cmd -DCMAKE_CXX_FLAGS=-m32 -DCMAKE_C_FLAGS=-m32"
fi
	echo "Building:"
	echo "- Configuration: $1"
	echo "- Platform: $platform"
	cmd="$cmd -DCMAKE_INSTALL_PREFIX:PATH=$targetInstallPath/$platform/$1"
	$cmd &> /dev/null
	echo -e "- Command: \e[2m$cmd\e[0m"

	# Advanced:
	# Uses 16 concurrent threads to build.
	# make -j16 &> /dev/null

	make &> /dev/null

	make install &> /dev/null
	cd ..
	echo "================================================="
}

echo "================================================="
echo "================== Build started ================"
echo "================================================="
echo ""
build "Debug" true
build "RelWithDebInfo" true
build "MinSizeRel" true
build "Release" true

build "Debug" false
build "RelWithDebInfo" false
build "MinSizeRel" false
build "Release" false

function relocate
{
	local targetPath="$targetInstallPath/$1/$2/$3"
	local srcPath="$targetInstallPath/$2/$3/$1"

	mkdir -p "$targetPath"
	cp -r "$srcPath/." "$targetPath"
}

cp -r "$targetInstallPath/x86/Debug/include/." "$targetInstallPath/include"

relocate "lib" x86 Debug
relocate "lib" x86 MinSizeRel
relocate "lib" x86 Release
relocate "lib" x86 RelWithDebInfo
relocate "lib" x64 Debug
relocate "lib" x64 MinSizeRel
relocate "lib" x64 Release
relocate "lib" x64 RelWithDebInfo

rm -rf "$targetInstallPath/x86"
rm -rf "$targetInstallPath/x64"