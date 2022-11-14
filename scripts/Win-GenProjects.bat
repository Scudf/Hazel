@echo off
pushd %~dp0\..\
CALL vendor\bin\premake5\premake5.exe vs2022
popd
PAUSE
