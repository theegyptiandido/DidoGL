@echo off
setlocal
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" >nul
if not exist "%~dp0build" mkdir "%~dp0build"
pushd "%~dp0"
cl /nologo /std:c++17 /EHsc /W3 /O2 /DUNICODE /D_UNICODE /Fo:build\ /Fe:build\DidoGL.exe ^
   src\platform.cpp src\didogl.cpp src\engine.cpp src\game.cpp src\main.cpp ^
   /link opengl32.lib gdi32.lib user32.lib /SUBSYSTEM:CONSOLE
set ERR=%ERRORLEVEL%
popd
echo build exit=%ERR%
