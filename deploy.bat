@echo off

rem
rem Check if Qt's tools are installed in default location.
rem

set windeployqt=C:\Qt\5.15.2\msvc2019_64\bin\windeployqt.exe

if not exist "%windeployqt%" PowerShell -Command "Add-Type -AssemblyName PresentationFramework;[System.Windows.MessageBox]::Show('MSVC2019 is not installed in the default location.', 'Program check', 'Ok', 'Warning')" && exit /b 1

rem
rem First find absolute path to release build directory,
rem create a folder containing only the final exe,
rem run the deploy tool.
rem
rem Finally, to make .zip use 'tar' program (which seems to be provided by Windows 10 now...)
rem

pushd   .
cd      /d %~dp0

set releasedir=..\build*release

if not exist "%releasedir%" PowerShell -Command "Add-Type -AssemblyName PresentationFramework;[System.Windows.MessageBox]::Show('Release build has not been compiled.', 'Program check', 'Ok', 'Warning')" && exit /b 1

rem Assuming there's ever going to be one folder with 'release' in its name...
pushd      .
set        deployqt=C:\Qt\5.15.2\msvc2019_64\bin\windeployqt.exe
set        deploydir=deploy
cd         ..
mkdir      %deploydir%
cd         build*release
set        releasedir=%cd%
cd         ..
copy       %releasedir%\05-muzicka-tabla.exe %deploydir%\
%deployqt% %deploydir%\05-muzicka-tabla.exe --no-translations
tar        -a -cf 05-muzicka-tabla.zip %deploydir%
popd

echo %cd%\05-muzicka-tabla.zip

popd
