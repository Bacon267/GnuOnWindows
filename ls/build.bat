@echo off

REM Define the relative path to ls.c from the script location
set LS_PATH=%~dp0ls.c

REM Compile using the relative path
cl "%LS_PATH%" /link /SUBSYSTEM:CONSOLE Shell32.lib

