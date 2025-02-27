@echo off
where cl.exe > nul 2>&1
if %errorlevel% == 0 goto :EOF
if not exist D:\build_tools_x64\devcmd.bat goto :EOF
call D:\build_tools_x64\devcmd.bat
ECHO Setting up Visual Studio 2019 x64 Developer Command Prompt