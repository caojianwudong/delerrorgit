# Microsoft Developer Studio Project File - Name="TaskManager" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=TaskManager - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "TaskManager.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TaskManager.mak" CFG="TaskManager - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TaskManager - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "TaskManager - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "TaskManager - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\0000object\release\TaskManager"
# PROP Intermediate_Dir "..\..\..\..\0000object\release\TaskManager"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\include\mysql" /I "..\..\include\db_manager" /I "..\..\include\DBFieldSDE" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 ole32.lib comsupp.lib ..\..\lib\libmysql.lib ..\..\lib\db_manager.lib ..\..\lib\FieldSde.lib /nologo /subsystem:windows /dll /machine:I386 /out:"..\..\bin\release\TaskManager.dll"

!ELSEIF  "$(CFG)" == "TaskManager - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\0000object\debug\TaskManager"
# PROP Intermediate_Dir "..\..\..\..\0000object\debug\TaskManager"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\include\mysql" /I "..\..\include\db_manager" /I "..\..\include\DBFieldSDE" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ole32.lib comsupp.lib ..\..\lib\libmysql.lib ..\..\lib\db_manager.lib ..\..\lib\FieldSded.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\..\bin\debug\TaskManager.dll" /pdbtype:sept
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy ..\..\..\..\0000object\debug\TaskManager\TaskManager.lib  ..\..\lib\	copy ctaskmanager.h   ..\..\include\taskmanager	copy ctask.h   ..\..\include\taskmanager	copy CTaskLinkAttach.h ..\..\include\taskmanager	copy CTaskLinkFieldData.h ..\..\include\taskmanager	copy task_definition.h  ..\..\include\taskmanager	copy CQCTask.h  ..\..\include\taskmanager	copy CTaskCommon.h  ..\..\include\taskmanager	copy CTaskLinkItemSet.h  ..\..\include\taskmanager	copy CTaskBlock.h  ..\..\include\taskmanager	copy CTaskBatch.h  ..\..\include\taskmanager	copy CTaskBlockDetail.h  ..\..\include\taskmanager
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "TaskManager - Win32 Release"
# Name "TaskManager - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CConvertTool.cpp
# End Source File
# Begin Source File

SOURCE=.\CQCTask.cpp
# End Source File
# Begin Source File

SOURCE=.\CTask.cpp
# End Source File
# Begin Source File

SOURCE=.\CTaskBatch.cpp
# End Source File
# Begin Source File

SOURCE=.\CTaskBlock.cpp
# End Source File
# Begin Source File

SOURCE=.\CTaskBlockDetail.cpp
# End Source File
# Begin Source File

SOURCE=.\CTaskChangeRoadTime.cpp
# End Source File
# Begin Source File

SOURCE=.\CTaskCommon.cpp
# End Source File
# Begin Source File

SOURCE=.\CTaskLinkAttach.cpp
# End Source File
# Begin Source File

SOURCE=.\CTaskLinkFieldData.cpp
# End Source File
# Begin Source File

SOURCE=.\CTaskLinkItemSet.cpp
# End Source File
# Begin Source File

SOURCE=.\CTaskManager.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TaskManager.cpp
# End Source File
# Begin Source File

SOURCE=.\TaskManager.def
# End Source File
# Begin Source File

SOURCE=.\TaskManager.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CConvertTool.h
# End Source File
# Begin Source File

SOURCE=.\CQCTask.h
# End Source File
# Begin Source File

SOURCE=.\CTask.h
# End Source File
# Begin Source File

SOURCE=.\CTaskBatch.h
# End Source File
# Begin Source File

SOURCE=.\CTaskBlock.h
# End Source File
# Begin Source File

SOURCE=.\CTaskBlockDetail.h
# End Source File
# Begin Source File

SOURCE=.\CTaskChangeRoadTime.h
# End Source File
# Begin Source File

SOURCE=.\CTaskCommon.h
# End Source File
# Begin Source File

SOURCE=.\CTaskLinkAttach.h
# End Source File
# Begin Source File

SOURCE=.\CTaskLinkFieldData.h
# End Source File
# Begin Source File

SOURCE=.\CTaskLinkItemSet.h
# End Source File
# Begin Source File

SOURCE=.\CTaskManager.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\task_definition.h
# End Source File
# Begin Source File

SOURCE=.\TaskManager.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\TaskManager.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project