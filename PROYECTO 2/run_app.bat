@echo off
REM Ejecutar TaskScriptAnalyzer desde MSYS2
REM Agrega las DLLs de MSYS2 MinGW al PATH

SET PATH=C:\msys64\mingw64\bin;C:\msys64\mingw64\lib;%PATH%

cd /d "C:\Users\jimhu\Desktop\1S2026_-LFPA-_-202303768\PROYECTO 2\build"
.\TaskScriptAnalyzer.exe

pause
