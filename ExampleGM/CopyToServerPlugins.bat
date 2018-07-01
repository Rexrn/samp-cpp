@echo off

:: [ Manual configuration ]

:: Configure this variable to point to samp server \plugins directory.
:: Example:
:: Lets say, your folder has this path:
::
:: C:\Path\To\SAMPServer\plugins
::
:: The line below should look like this:
::
:: SET "TargetDir=C:\Path\To\SAMPServer\plugins"
::
:: Do not add slash or backslash at the end.
SET "TargetDir=D:\Inne\SampServer\plugins"

:: [ Automatic configuration (parameters taken from Visual Studio) ]
SET "SourceFile=%1"
SET "TargetName=%2"
SET "TargetFile=%TargetDir%\%TargetName%.dll"


:: Note: prints run command for debug purposes:
:: echo "echo f | xcopy /f /y %SourceFile% %TargetFile%"

echo Copying built binary to server \plugins directory!
echo f | xcopy /f /y %SourceFile% %TargetFile%