rem set path and call cmd

if "%DSLCT_ADD_PATH%" == "" (set DSLCT_ADD_PATH=1) else goto RUN_CMD

set PATH=C:\Python27;%PATH%
set PATH=D:\Python27;%PATH%
set PATH=E:\Python27;%PATH%
set PATH=F:\Python27;%PATH%
set PATH=G:\Python27;%PATH%

set PATH=C:\Program Files\Microsoft Visual Studio 8\Common7\IDE;%PATH%
set PATH=D:\Program Files\Microsoft Visual Studio 8\Common7\IDE;%PATH%
set PATH=E:\Program Files\Microsoft Visual Studio 8\Common7\IDE;%PATH%
set PATH=F:\Program Files\Microsoft Visual Studio 8\Common7\IDE;%PATH%
set PATH=G:\Program Files\Microsoft Visual Studio 8\Common7\IDE;%PATH%

set PATH=C:\Program Files (x86)\Microsoft Visual Studio 8\Common7\IDE;%PATH%
set PATH=D:\Program Files (x86)\Microsoft Visual Studio 8\Common7\IDE;%PATH%
set PATH=E:\Program Files (x86)\Microsoft Visual Studio 8\Common7\IDE;%PATH%
set PATH=F:\Program Files (x86)\Microsoft Visual Studio 8\Common7\IDE;%PATH%
set PATH=G:\Program Files (x86)\Microsoft Visual Studio 8\Common7\IDE;%PATH%

set PATH=C:\Program Files\Subversion\bin;%PATH%
set PATH=D:\Program Files\Subversion\bin;%PATH%
set PATH=E:\Program Files\Subversion\bin;%PATH%
set PATH=F:\Program Files\Subversion\bin;%PATH%
set PATH=G:\Program Files\Subversion\bin;%PATH%

set PATH=C:\Program Files (x86)\Subversion\bin;%PATH%
set PATH=D:\Program Files (x86)\Subversion\bin;%PATH%
set PATH=E:\Program Files (x86)\Subversion\bin;%PATH%
set PATH=F:\Program Files (x86)\Subversion\bin;%PATH%
set PATH=G:\Program Files (x86)\Subversion\bin;%PATH%

:RUN_CMD

rem Usage : test_pkg.bat [target_type]
python test_pkg_windows.py %1

