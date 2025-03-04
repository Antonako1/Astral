:: Usage: WIN_RUN.BAT <DIR_RUN> <arg2>
:: This script is used to run tests on Windows
:: Example 
::      ./WIN_RUN ./ASTRAL_UI_1         -> Builds the project
::      ./WIN_RUN ./ASTRAL_UI_1 r       -> Builds the project and runs the executable

@echo off
setlocal
set "DIR_RUN=%1"
set "arg2=%2"
cd /d "%DIR_RUN%"
echo "Running tests in %DIR_RUN%"
if not exist build mkdir build
cd build
cmake .. -G "Ninja"
cmake --build .
if "%arg2%" NEQ "" call TEST

endlocal