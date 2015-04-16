@echo off
set MINGWPATH=C:\Programs\mingw\bin
set GCCOPT=-c -DMINGW -O3 -Os -fomit-frame-pointer -mcpu=i686 -march=i686
del *.o

for %%f in (..\*.cpp) do %MINGWPATH%\gcc %GCCOPT% %%f
%MINGWPATH%\ar r winapi.a *.o
del *.o

for %%f in (..\*.cpp) do %MINGWPATH%\gcc -DPURE_WRAPPER %GCCOPT% %%f
%MINGWPATH%\ar r winapip.a *.o
del *.o
