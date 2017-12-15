@echo off

cls

call where emcc
if %errorlevel% == 1 (
	echo Loading Emscripten Environment Variables
	call emsdk_env.bat
)

set CC=emcc
set CONFIG=Debug
set CONFIG_FLAG=DEBUG
set SAMPLE_OUTPUT_DIR=C:\xampp\htdocs\entanglement\%CONFIG%\
set FLAGS_WASM=^
 --shell-file tools\shell.html^
 -g4^
 -Wno-format^
 -Wno-deprecated^
 -Wno-format-security^
 -Wno-address-of-temporary^
 -D_%CONFIG_FLAG%^
 -DPLATFORM_WEB^
 -s TOTAL_MEMORY=838860800^
 -s WASM=1
 
set FLAGS_ASMJS=^
 --shell-file tools\shell.html^
 -g4^
 -Wno-format^
 -Wno-deprecated^
 -Wno-format-security^
 -Wno-address-of-temporary^
 -D_%CONFIG_FLAG%^
 -DPLATFORM_WEB^
 -s TOTAL_MEMORY=838860800
 
echo Building Debug

mkdir %SAMPLE_OUTPUT_DIR%
call %CC% %FLAGS_WASM% -c code\unity.c -o %SAMPLE_OUTPUT_DIR%game.o
call %CC% %FLAGS_WASM% %SAMPLE_OUTPUT_DIR%game.o -o %SAMPLE_OUTPUT_DIR%index.html --preload-file .\data\
call %CC% %FLAGS_ASMJS% -c code\unity.c -o %SAMPLE_OUTPUT_DIR%game.o
call %CC% %FLAGS_ASMJS% %SAMPLE_OUTPUT_DIR%game.o -o %SAMPLE_OUTPUT_DIR%index.asm.js --preload-file .\data\
call rm -rf %SAMPLE_OUTPUT_DIR%game.o

echo Compilation Complete