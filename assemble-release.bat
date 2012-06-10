set lldir="%~dp0\lierolibre-0.0_win32"

md %lldir%
md %lldir%\libsrc


copy ..\src\_bin\Release\lierolibre.exe ..\data ..\scripts\lierolibre-cmd.bat %lldir%

copy ..\AUTHORS.txt ..\ChangeLog.txt ..\COPYING.txt ..\NEWS.txt ..\README.txt ..\lgpl-2.1.txt %lldir%

copy ..\lib\boost\boost_program_options-vc100-mt-1_49.dll ..\lib\msvcp100.dll ..\lib\msvcr100.dll ..\src\_build\Release\libconfig++.dll ..\lib\SDL-1.2.15\VisualC\SDL\Release\SDL.dll %lldir%

copy ..\lib\SDL-1.2.15 ..\lib\libconfig %lldir%\libsrc

