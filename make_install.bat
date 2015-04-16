@echo off

rem Skip building if the directory already exists
if exist WinAPIWrapper goto end

rem Create directory for the installation
mkdir WinAPIWrapper

rem Copy libs and pdbs for VS.NET, plus the header and text files
mkdir WinAPIWrapper\WinAPIWrapper
for /d %%d in (Build\*) do copy %%d\*.lib WinAPIWrapper\WinAPIWrapper
for /d %%d in (Build\*) do copy %%d\*.pdb WinAPIWrapper\WinAPIWrapper
copy winapi.h WinAPIWrapper\WinAPIWrapper
copy License.txt WinAPIWrapper\WinAPIWrapper
copy License.rtf WinAPIWrapper\WinAPIWrapper
copy change_log.txt WinAPIWrapper\WinAPIWrapper

rem Copy libs for VS6
mkdir WinAPIWrapper\WinAPIWrapper\VS6
for /d %%d in (Build6\*) do copy %%d\*.lib WinAPIWrapper\WinAPIWrapper\VS6

rem Copy help in HTML
mkdir "WinAPIWrapper\WinAPIWrapper\Help HTML"
copy Help\HTML\*.css "WinAPIWrapper\WinAPIWrapper\Help HTML"
copy Help\HTML\*.htm "WinAPIWrapper\WinAPIWrapper\Help HTML"
copy Help\HTML\*.txt "WinAPIWrapper\WinAPIWrapper\Help HTML"

rem Copy help in HxS
mkdir WinAPIWrapper\WinAPIWrapper\Help
copy Help\*.HxI WinAPIWrapper\WinAPIWrapper\Help
copy Help\*.HxS WinAPIWrapper\WinAPIWrapper\Help
copy Help\Setup\*.Hx? WinAPIWrapper\WinAPIWrapper\Help

rem Copy samples
mkdir WinAPIWrapper\WinAPIWrapper\Samples
copy Samples\*.* WinAPIWrapper\WinAPIWrapper\Samples
mkdir WinAPIWrapper\WinAPIWrapper\Samples\Basic
copy Samples\Basic\*.* WinAPIWrapper\WinAPIWrapper\Samples\Basic
mkdir WinAPIWrapper\WinAPIWrapper\Samples\Tiny
copy Samples\Tiny\*.* WinAPIWrapper\WinAPIWrapper\Samples\Tiny
mkdir WinAPIWrapper\WinAPIWrapper\Samples\Multithreading
copy Samples\Multithreading\*.* WinAPIWrapper\WinAPIWrapper\Samples\Multithreading

rem Copy AppWizard for VS.NET
mkdir WinAPIWrapper\AppWizard
mkdir WinAPIWrapper\AppWizard\vcprojects
copy WinAPIWrapperWiz\vcprojects\*.* WinAPIWrapper\AppWizard\vcprojects
mkdir WinAPIWrapper\AppWizard\VCWizards
mkdir WinAPIWrapper\AppWizard\VCWizards\WinAPIWrapperWiz
mkdir WinAPIWrapper\AppWizard\VCWizards\WinAPIWrapperWiz\html
mkdir WinAPIWrapper\AppWizard\VCWizards\WinAPIWrapperWiz\html\1033
mkdir WinAPIWrapper\AppWizard\VCWizards\WinAPIWrapperWiz\images
mkdir WinAPIWrapper\AppWizard\VCWizards\WinAPIWrapperWiz\scripts
mkdir WinAPIWrapper\AppWizard\VCWizards\WinAPIWrapperWiz\scripts\1033
mkdir WinAPIWrapper\AppWizard\VCWizards\WinAPIWrapperWiz\templates
mkdir WinAPIWrapper\AppWizard\VCWizards\WinAPIWrapperWiz\templates\1033
copy WinAPIWrapperWiz\VCWizards\WinAPIWrapperWiz\html\1033\*.* WinAPIWrapper\AppWizard\VCWizards\WinAPIWrapperWiz\html\1033
copy WinAPIWrapperWiz\VCWizards\WinAPIWrapperWiz\images\*.* WinAPIWrapper\AppWizard\VCWizards\WinAPIWrapperWiz\images
copy WinAPIWrapperWiz\VCWizards\WinAPIWrapperWiz\scripts\1033\*.* WinAPIWrapper\AppWizard\VCWizards\WinAPIWrapperWiz\scripts\1033
copy WinAPIWrapperWiz\VCWizards\WinAPIWrapperWiz\templates\1033\*.* WinAPIWrapper\AppWizard\VCWizards\WinAPIWrapperWiz\templates\1033

rem Copy and pack the setup executable
copy Setup3\Release\setup.exe WinAPIWrapper
\Extended\Programs\UPX\upx.exe WinAPIWrapper\setup.exe
copy WinAPIWrapper\setup.exe WinAPIWrapper\WinAPIWrapper

:end
