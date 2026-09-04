rem set path and call cmd

if "%DSLCT_ADD_PATH%" == "" (set DSLCT_ADD_PATH=1) else goto RUN_CMD

set PATH=C:\Program Files\MSBuild\14.0\Bin;%PATH%
set PATH=D:\Program Files\MSBuild\14.0\Bin;%PATH%
set PATH=E:\Program Files\MSBuild\14.0\Bin;%PATH%
set PATH=F:\Program Files\MSBuild\14.0\Bin;%PATH%
set PATH=G:\Program Files\MSBuild\14.0\Bin;%PATH%

set PATH=C:\Program Files (x86)\MSBuild\14.0\Bin;%PATH%
set PATH=D:\Program Files (x86)\MSBuild\14.0\Bin;%PATH%
set PATH=E:\Program Files (x86)\MSBuild\14.0\Bin;%PATH%
set PATH=F:\Program Files (x86)\MSBuild\14.0\Bin;%PATH%
set PATH=G:\Program Files (x86)\MSBuild\14.0\Bin;%PATH%

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

rem Usage : build_depend.bat [target_type]
rem set PYTHONPATH=./;%PYTHONPATH%
rem python -c "import dslct; do_build_depend_ui( %1 )"
python dslct.py do_build_depend_ui %1

