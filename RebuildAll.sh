rm -rf Bin
rm -rf Build
premake5 --file=Premake5Build.lua gmake
cd Build
make config=debug_x86
make config=release_x86
make config=debug_x64
make config=release_x64
