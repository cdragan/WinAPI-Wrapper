# Microsoft Developer Studio Project File - Name="WinAPI" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=WinAPI - Win32 Debug Pure
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WinAPI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WinAPI.mak" CFG="WinAPI - Win32 Debug Pure"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WinAPI - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "WinAPI - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE "WinAPI - Win32 Release Pure" (based on "Win32 (x86) Static Library")
!MESSAGE "WinAPI - Win32 Debug Pure" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WinAPI - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Build6\Release"
# PROP Intermediate_Dir "Build6\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /G6 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x415 /d "NDEBUG"
# ADD RSC /l 0x415 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "WinAPI - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Build6\Debug"
# PROP Intermediate_Dir "Build6\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /W3 /GX /Zd /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x415 /d "_DEBUG"
# ADD RSC /l 0x415 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Build6\Debug\WinAPId.lib"

!ELSEIF  "$(CFG)" == "WinAPI - Win32 Release Pure"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinAPI___Win32_Release_Pure"
# PROP BASE Intermediate_Dir "WinAPI___Win32_Release_Pure"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Build6\Release_Pure"
# PROP Intermediate_Dir "Build6\Release_Pure"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /G6 /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "PURE_WRAPPER" /YX /FD /c
# ADD BASE RSC /l 0x415 /d "NDEBUG"
# ADD RSC /l 0x415 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Build6\Release_Pure\WinAPIp.lib"

!ELSEIF  "$(CFG)" == "WinAPI - Win32 Debug Pure"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinAPI___Win32_Debug_Pure"
# PROP BASE Intermediate_Dir "WinAPI___Win32_Debug_Pure"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Build6\Debug_Pure"
# PROP Intermediate_Dir "Build6\Debug_Pure"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /W3 /GX /Zd /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /G6 /W3 /GX /Zd /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "PURE_WRAPPER" /YX /FD /GZ /c
# ADD BASE RSC /l 0x415 /d "_DEBUG"
# ADD RSC /l 0x415 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /out:"Build6\Debug\WinAPId.lib"
# ADD LIB32 /nologo /out:"Build6\Debug_Pure\WinAPIpd.lib"

!ENDIF 

# Begin Target

# Name "WinAPI - Win32 Release"
# Name "WinAPI - Win32 Debug"
# Name "WinAPI - Win32 Release Pure"
# Name "WinAPI - Win32 Debug Pure"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\application.cpp
# End Source File
# Begin Source File

SOURCE=.\combobox_getlbtext.cpp
# End Source File
# Begin Source File

SOURCE=.\comboboxex_getitemtext.cpp
# End Source File
# Begin Source File

SOURCE=.\default_mdichild_class.cpp
# End Source File
# Begin Source File

SOURCE=.\default_window_class.cpp
# End Source File
# Begin Source File

SOURCE=.\dialog.cpp
# End Source File
# Begin Source File

SOURCE=.\dialog_enddialog.cpp
# End Source File
# Begin Source File

SOURCE=.\dialog_go1.cpp
# End Source File
# Begin Source File

SOURCE=.\dialog_go2.cpp
# End Source File
# Begin Source File

SOURCE=.\edit_getline.cpp
# End Source File
# Begin Source File

SOURCE=.\listbox_gettext.cpp
# End Source File
# Begin Source File

SOURCE=.\listview_getitemtext.cpp
# End Source File
# Begin Source File

SOURCE=.\mdichild.cpp
# End Source File
# Begin Source File

SOURCE=.\mdichild_defaultproc.cpp
# End Source File
# Begin Source File

SOURCE=.\mdiwindow.cpp
# End Source File
# Begin Source File

SOURCE=.\menu_getstring.cpp
# End Source File
# Begin Source File

SOURCE=.\modelessdialog_create1.cpp
# End Source File
# Begin Source File

SOURCE=.\modelessdialog_create2.cpp
# End Source File
# Begin Source File

SOURCE=.\modelessdialog_create3.cpp
# End Source File
# Begin Source File

SOURCE=.\regkey_deletekeytree.cpp
# End Source File
# Begin Source File

SOURCE=.\regkey_enum.cpp
# End Source File
# Begin Source File

SOURCE=.\regkey_enumkeys.cpp
# End Source File
# Begin Source File

SOURCE=.\regkey_enumkeys2.cpp
# End Source File
# Begin Source File

SOURCE=.\regkey_queryvalue.cpp
# End Source File
# Begin Source File

SOURCE=.\socket.cpp
# End Source File
# Begin Source File

SOURCE=.\statusbar_gettext.cpp
# End Source File
# Begin Source File

SOURCE=.\statusbar_gettiptext.cpp
# End Source File
# Begin Source File

SOURCE=.\tabcontrol_getitemtext.cpp
# End Source File
# Begin Source File

SOURCE=.\thread.cpp
# End Source File
# Begin Source File

SOURCE=.\toolbar_getbuttontext.cpp
# End Source File
# Begin Source File

SOURCE=.\treeitem_getitemtext.cpp
# End Source File
# Begin Source File

SOURCE=.\window.cpp
# End Source File
# Begin Source File

SOURCE=.\window_class.cpp
# End Source File
# Begin Source File

SOURCE=.\window_defaultproc.cpp
# End Source File
# Begin Source File

SOURCE=.\window_gettext.cpp
# End Source File
# Begin Source File

SOURCE=.\windowclass_constructor.cpp
# End Source File
# Begin Source File

SOURCE=.\winmain.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\passlparam.h
# End Source File
# Begin Source File

SOURCE=.\winapi.h
# End Source File
# End Group
# End Target
# End Project
