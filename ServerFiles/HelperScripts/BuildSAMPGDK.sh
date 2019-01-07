####################################
# Notes:
# - Put this file in your root GoogleTest repository folder.
# - Configure variables below.
####################################

####################################
# User configuration:
####################################

# Dependencies:
dep_sampPluginSdkRoot=""

# Other settings:
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
	local mode=$1
	echo "Building:"
	echo "- Configuration: $mode"
	echo "- Platform: x86"

	local cmd="cmake .. \
		-DSAMP_SDK_ROOT:PATH=$dep_sampPluginSdkRoot \
		-DCMAKE_INSTALL_PREFIX:PATH=$targetInstallPath/x86/$mode \
		-DSAMPGDK_STATIC=ON \
		-DSAMPGDK_BUILD_PLUGINS=ON \
		-DSAMPGDK_BUILD_AMALGAMATION=ON \
		-DSAMPGDK_BUILD_DOCS=OFF"
	echo -e "- Command: \e[2m$cmd\e[0m"

	if [[ $runSilent == true ]];
	then 
		$cmd &> /dev/null
		cmake --build . --config $mode &> /dev/null
	else
		$cmd
		cmake --build . --config $mode
	fi;

	echo "================================================="
}

function install
{
	local mode=$1

	if [[ $runSilent == true ]];
	then 
		cmake --build . --config $mode --target install&> /dev/null
	else
		cmake --build . --config $mode --target install
	fi;
}

function postInstallRelocate
{
	echo "Performing post-install relocation."

	# Create and copy include folder:
	mkdir -p "$targetInstallPath/include"
	cp -r "$targetInstallPath/x86/Debug/include/." "$targetInstallPath/include"

	# Create and copy x86/Debug library folder:
	mkdir -p "$targetInstallPath/lib/x86/Debug"
	cp -r "$targetInstallPath/x86/Debug/lib/." "$targetInstallPath/lib/x86/Debug"

	# Create and copy x86/Release library folder:
	mkdir -p "$targetInstallPath/lib/x86/Release"
	cp -r "$targetInstallPath/x86/Release/lib/." "$targetInstallPath/lib/x86/Release"
}

function postInstallCleanup
{
	echo "Performing post-install cleanup."
	rm -rf "$targetInstallPath/x86"
	rm -rf "$targetInstallPath/x64"
}

function executeScript
{
	echo "================================================="
	echo "================== Build started ================"
	echo "================================================="
	echo ""


	echo "Cleaning up target install directory."
	rm -rf "$targetInstallPath"

	rm -rf build
	mkdir build
	cd build

	build "Debug"
	install "Debug"

	build "Release"
	install "Release"

	postInstallRelocate
	postInstallCleanup
}

executeScript