@echo off
if exist WinAPIWrapper goto end
call make_install.bat
mkdir WinAPIWrapper\WinAPIWrapper\Source
copy *.cpp WinAPIWrapper\WinAPIWrapper\Source
copy *.h WinAPIWrapper\WinAPIWrapper\Source
copy *.sln WinAPIWrapper\WinAPIWrapper\Source
copy *.vcproj WinAPIWrapper\WinAPIWrapper\Source
copy *.dsp WinAPIWrapper\WinAPIWrapper\Source
copy *.txt WinAPIWrapper\WinAPIWrapper\Source
:end
