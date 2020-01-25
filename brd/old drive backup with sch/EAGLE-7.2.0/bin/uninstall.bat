@echo off
if "%1" == "" exit
if "%1" == "-ui" goto UNINSTALL
if "%1" == "-db" goto DOSBASED
set DIR="%*"
set STA=
goto COPY
:DOSBASED
shift
set DIR=%1
set STA=start /w

:COPY
set TMPDIR=%TEMP%\uninstall-eagle
md "%TMPDIR%"
copy /y %DIR%\eagle.exe "%TMPDIR%\uninstall.exe"
copy /y %DIR%\*.qm "%TMPDIR%"
copy /y %DIR%\uninstall.bat "%TEMP%\uninstall.bat"
"%TEMP%\uninstall.bat" -ui
exit

:UNINSTALL
%STA% "%TMPDIR%\uninstall.exe" %DIR%\uninstall.lst
for %%i in ("%TMPDIR%"\*) do del "%%i"
rd "%TMPDIR%"
for %%i in (del cls exit) do %%i "%TEMP%\uninstall.bat"
