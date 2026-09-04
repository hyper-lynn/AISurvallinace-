; LCOpenSDKDemo.nsi
;
; This script is perhaps one of the simplest NSIs you can make. All of the
; optional settings are left to their default settings. The installer simply 
; prompts the user asking them where to install, and drops a copy of LCOpenSDKDemo.nsi
; there. 

;--------------------------------

; The name of the installer
Name "LCOpenSDKDemo"
 
; The file to write
OutFile "LCOpenSDKDemoSetup_x86.exe"

; The default installation directory
InstallDir "C:\Program Files (x86)\LCOpenSDKDemo"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages

Page directory
Page instfiles

;--------------------------------
	


; The stuff to install
Section "" ;No components page, name is not important

  ; Set output path to the installation directory.
  SetOutPath "$INSTDIR"
  ; Put file there
  File /r /x .svn "..\Bin\Win32\Release\"
  
SectionEnd ; end the section

