@echo off
setlocal
cd /D %~dp0

cd ..
if not exist build mkdir build
cd build
cmake .. -G "Ninja"
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Build failed with error code %ERRORLEVEL%.
    echo.
    pause
    exit /b %ERRORLEVEL%
)

cmake --build .
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo Build failed with error code %ERRORLEVEL%.
    echo.
    pause
    exit /b %ERRORLEVEL%
)

endlocal

goto :EOF
