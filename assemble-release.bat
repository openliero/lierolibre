SET lldir="%~dp0\lierolibre-0.0_win32"

SET core=src\_bin\Release\lierolibre.exe scripts\lierolibre-cmd.bat
SET doc=AUTHORS.txt ChangeLog.txt COPYING.txt NEWS.txt README.txt lgpl-2.1.txt
SET lib=lib\boost\boost_program_options-vc100-mt-1_49.dll lib\msvcp100.dll lib\msvcr100.dll src\_build\Release\libconfig++.dll lib\SDL-1.2.15\VisualC\SDL\Release\SDL.dll
SET src=lib\SDL-1.2.15 lib\libconfig

MD %lldir%
MD %lldir%\libsrc

XCOPY /YIE data %lldir%\data
DEL %lldir%\data\.git %lldir%\data\LICENSE.TXT

FOR %%i IN (%core% %doc% %lib%) DO (
  COPY %%i %lldir%
)

XCOPY /YIE lib\SDL-1.2.15 %lldir%\libsrc\SDL-1.2.15
XCOPY /YIE lib\libconfig %lldir%\libsrc\libconfig

PAUSE

