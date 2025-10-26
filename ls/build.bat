@echo off

mkdir ..\ls\build
pushd ..\ls\build
cl -Zi w:\Probe\CoreUtils\ls\ls.c /link /SUBSYSTEM:CONSOLE Shell32.lib
popd
