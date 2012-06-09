@echo off

set lldir="%~dp0\lierolibre-0.0_win32"

md %lldir%
cd %lldir%

copy ..\src\_bin\Release\lierolibre.exe ..\data ..\scripts\lierolibre-cmd.bat

copy ..\AUTHORS.txt ..\ChangeLog.txt ..\COPYING.txt ..\NEWS.txt ..\README.txt

copy ..\lib\boost\boost_program_options-vc100-mt-1_49.dll ..\lib\msvcp100.dll ..\lib\msvcr100.dll ..\src\_build\Release\libconfig++.dll

