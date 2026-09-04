@echo off
setlocal EnableDelayedExpansion
@echo exe-build.bat start
@echo *******************************
@echo *      win64-Chn-release Demo      = 1 *
@echo *      win32-Chn-release Demo      = 2 *
@echo *      win64-Eng-release Demo      = 3 *
@echo *      win32-Eng-release Demo      = 4 *
@echo *******************************
@set /p Param=Select Param:

if "%Param%"=="1" (
	set "os=x64"
) else if "%Param%"=="2" (
	set "os=Win32"
) else if "%Param%"=="3" (
	set "os=x64"
) else if "%Param%"=="4" (
	set "os=Win32"
) else (
    set "os=x64"
)

echo Detecting Visual Studio installation...
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
set "VS_DIR="

if exist "%VSWHERE%" (
    for /f "usebackq tokens=*" %%i in (`"%VSWHERE%" -latest -property installationPath`) do (
        set "VS_DIR=%%i"
    )
)

if not defined VS_DIR (
    if exist "C:\Program Files\Microsoft Visual Studio\2022" set "VS_DIR=C:\Program Files\Microsoft Visual Studio\2022"
    if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community" set "VS_DIR=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community"
    if exist "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community" set "VS_DIR=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community"
    if exist "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise" set "VS_DIR=C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise"
)

if not defined VS_DIR (
    echo [ERROR] Could not auto-detect Visual Studio installation path!
    pause
    exit /b 1
)

echo Found Visual Studio at: "%VS_DIR%"
set "DEVENV_EXE=%VS_DIR%\Common7\IDE\devenv.com"
if not exist "!DEVENV_EXE!" (
    set "DEVENV_EXE=%VS_DIR%\Common7\IDE\devenv.exe"
)

if "%os%"=="x64" (
    if exist "%VS_DIR%\VC\Auxiliary\Build\vcvars64.bat" (
        call "%VS_DIR%\VC\Auxiliary\Build\vcvars64.bat"
    ) else (
        call "%VS_DIR%\VC\Auxiliary\Build\vcvars32.bat"
    )
) else (
    call "%VS_DIR%\VC\Auxiliary\Build\vcvars32.bat"
)

echo -------------VS Environment Variables----------------
echo devenv path: "!DEVENV_EXE!"
echo -----------------------------------------------------

echo delete old files
del /f /s /q Bin\%os%\Release\*.* 2>nul
rd /s /q Bin\%os%\Release\Skin 2>nul

echo copy Skin to Bin
if not exist "Bin\%os%\Release\Skin" md "Bin\%os%\Release\Skin"
xcopy /s /y LCOpenSDKDemo-V2.0\Skin Bin\%os%\Release\Skin

echo copy QTRun system lib to Bin
copy /y LCOpenSDKDemo-V2.0\Depend\QTRun\%os%\bin\*.* Bin\%os%\Release

if not exist "Bin\%os%\Release\plugins" md "Bin\%os%\Release\plugins"
xcopy /s /y LCOpenSDKDemo-V2.0\Depend\QTRun\%os%\plugins Bin\%os%\Release\plugins

if not exist "Bin\%os%\Release\resources" md "Bin\%os%\Release\resources"
xcopy /s /y LCOpenSDKDemo-V2.0\Depend\QTRun\%os%\resources Bin\%os%\Release\resources

if not exist "Bin\%os%\Release\translations" md "Bin\%os%\Release\translations"
xcopy /s /y LCOpenSDKDemo-V2.0\Depend\QTRun\%os%\translations Bin\%os%\Release\translations

echo copy Third_Lib to Bin
echo copy playsdk to Bin
copy /y LCOpenSDKDemo-V2.0\Depend\lib\%os%\Third_Lib\playsdk\*.dll Bin\%os%\Release
copy /y LCOpenSDKDemo-V2.0\Depend\lib\%os%\Third_Lib\playsdk\*.pdb Bin\%os%\Release

echo copy netsdk to Bin
copy /y LCOpenSDKDemo-V2.0\Depend\lib\%os%\Third_Lib\netsdk\*.dll Bin\%os%\Release
copy /y LCOpenSDKDemo-V2.0\Depend\lib\%os%\Third_Lib\netsdk\*.pdb Bin\%os%\Release

echo copy LCOpenSDK and LCOpenApiClient to Bin
copy /y LCOpenSDKDemo-V2.0\Depend\lib\%os%\LCOpenSDK\LCOpenSDKmd.dll Bin\%os%\Release
copy /y LCOpenSDKDemo-V2.0\Depend\lib\%os%\LCOpenSDK\LCOpenSDKmd.pdb Bin\%os%\Release
copy /y LCOpenSDKDemo-V2.0\Depend\lib\%os%\LCOpenApiClient\LCOpenApiClientmd.dll Bin\%os%\Release
copy /y LCOpenSDKDemo-V2.0\Depend\lib\%os%\LCOpenApiClient\LCOpenApiClientmd.pdb Bin\%os%\Release

echo copy VCRedist to Bin
copy /y LCOpenSDKDemo-V2.0\Depend\lib\%os%\VCRedist\*.dll Bin\%os%\Release
copy /y LCOpenSDKDemo-V2.0\Depend\lib\%os%\VCRedist\Microsoft.VC80.CRT.manifest Bin\%os%\Release 2>nul
copy /y LCOpenSDKDemo-V2.0\Depend\lib\%os%\VCRedist\Microsoft.VC80.ATL.manifest Bin\%os%\Release 2>nul
copy /y LCOpenSDKDemo-V2.0\Depend\lib\%os%\VCRedist\Microsoft.VC80.MFC.manifest Bin\%os%\Release 2>nul
copy /y LCOpenSDKDemo-V2.0\Depend\lib\%os%\VCRedist\Microsoft.VC80.DebugCRT.manifest Bin\%os%\Release 2>nul

if "%Param%"=="1" (
	echo copy ssl cert to Bin
	copy /y LCOpenSDKDemo-V2.0\cert.pem Bin\%os%\Release
	echo copy ch.qm to Bin
	copy /y LCOpenSDKDemo-V2.0\ch.qm Bin\%os%\Release
) else if "%Param%"=="2" (
	echo copy ssl cert to Bin
	copy /y LCOpenSDKDemo-V2.0\cert.pem Bin\%os%\Release
	echo copy ch.qm to Bin
	copy /y LCOpenSDKDemo-V2.0\ch.qm Bin\%os%\Release
) else if "%Param%"=="3" (
	echo copy ssl cert to Bin
	copy /y LCOpenSDKDemo-V2.0\cert_en.pem Bin\%os%\Release
) else if "%Param%"=="4" (
	echo copy ssl cert to Bin
	copy /y LCOpenSDKDemo-V2.0\cert_en.pem Bin\%os%\Release
)

echo copy LoginInfo to Bin
if "%Param%"=="1" (
	copy /y LCOpenSDKDemo-V2.0\LoginInfo.cfg Bin\%os%\Release
) else if "%Param%"=="2" (
	copy /y LCOpenSDKDemo-V2.0\LoginInfo.cfg Bin\%os%\Release
) else if "%Param%"=="3" (
	copy /y LCOpenSDKDemo-V2.0\LoginInfo_en.cfg Bin\%os%\Release
) else if "%Param%"=="4" (
	copy /y LCOpenSDKDemo-V2.0\LoginInfo_en.cfg Bin\%os%\Release
)

echo start building release...

if "%Param%"=="1" (
	call "!DEVENV_EXE!" "LCOpenSDKDemo-V2.0.sln" /rebuild "Release|x64"
) else if "%Param%"=="2" (
	call "!DEVENV_EXE!" "LCOpenSDKDemo-V2.0.sln" /rebuild "Release|Win32"
) else if "%Param%"=="3" (
	call "!DEVENV_EXE!" "LCOpenSDKDemo-V2.0.sln" /rebuild "Release|x64"
) else if "%Param%"=="4" (
	call "!DEVENV_EXE!" "LCOpenSDKDemo-V2.0.sln" /rebuild "Release|Win32"
)

if errorlevel 1 (
    echo build LCOpenSDKDemo error...
    pause
) else (
    echo build release success!
)

echo set NSIS environment path
if exist "C:\Program Files (x86)\NSIS\makensis.exe" set PATH=C:\Program Files (x86)\NSIS;%PATH%
if exist "C:\Program Files\NSIS\makensis.exe" set PATH=C:\Program Files\NSIS;%PATH%

if exist "C:\Program Files (x86)\NSIS\makensis.exe" (
	makensis "Install\LCOpenSDKDemo_%os%.nsi" 2>nul
) else if exist "C:\Program Files\NSIS\makensis.exe" (
	makensis "Install\LCOpenSDKDemo_%os%.nsi" 2>nul
) else (
	echo NSIS makensis.exe not installed. Skipping installer package creation. Output binaries built cleanly in Bin\%os%\Release.
)

echo exe-build.bat end
pause
