rem @echo off
if not exist Build goto end
if exist Package goto skip_lib_creation
mkdir Package
:skip_lib_creation
for /d %%d in (Build\*) do copy %%d\*.lib Package
for /d %%d in (Build\*) do copy %%d\*.pdb Package
copy winapi.h Package
:end
