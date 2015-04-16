@echo off
set INSDIR=%VSCOMNTOOLS%..\..\vc7
xcopy/s vcprojects\*.* %INSDIR%\vcprojects
xcopy/s VCWizards\*.* %INSDIR%\VCWizards
