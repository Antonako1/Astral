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