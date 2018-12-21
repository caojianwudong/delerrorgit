# Microsoft Developer Studio Project File - Name="CreateTaskForChangedRoad" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=CreateTaskForChangedRoad - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "CreateTaskForChangedRoad.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "CreateTaskForChangedRoad.mak" CFG="CreateTaskForChangedRoad - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "CreateTaskForChangedRoad - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "CreateTaskForChangedRoad - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CreateTaskForChangedRoad - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\00object\release\UpdateBlockDetail"
# PROP Intermediate_Dir "..\..\..\..\00object\release\UpdateBlockDetail"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /Od /I "..\..\include\sde" /I "..\..\include\TaskManager" /I "..\..\include\db_manager" /I "..\..\include\DBFieldSDE" /I "..\..\include\excel" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ..\..\lib\sde.lib ..\..\lib\TaskManager.lib ..\..\lib\db_manager.lib ..\..\lib\FieldSDE.lib ..\..\lib\ControlExcel.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\bin\Release\DeleteError.exe"

!ELSEIF  "$(CFG)" == "CreateTaskForChangedRoad - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\00object\Debug\UpdateBlockDetail"
# PROP Intermediate_Dir "..\..\..\..\00object\Debug\UpdateBlockDetail"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\include\sde" /I "..\..\include\TaskManager" /I "..\..\include\db_manager" /I "..\..\include\DBFieldSDE" /I "..\..\include\excel" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ..\..\lib\sded.lib ..\..\lib\TaskManager.lib ..\..\lib\db_manager.lib ..\..\lib\FieldSDEd.lib ..\..\lib\ControlExcel.lib /nologo /stack:0x989680 /subsystem:windows /debug /machine:I386 /out:"..\..\bin\Debug\DeleteErrorD.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "CreateTaskForChangedRoad - Win32 Release"
# Name "CreateTaskForChangedRoad - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\CCreateTask.cpp
# End Source File
# Begin Source File

SOURCE=.\CObjectOwner.cpp
# End Source File
# Begin Source File

SOURCE=.\CreateTaskForChangedRoad.cpp
# End Source File
# Begin Source File

SOURCE=.\CreateTaskForChangedRoad.rc
# End Source File
# Begin Source File

SOURCE=.\CreateTaskForChangedRoadDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CTransOwner.cpp
# End Source File
# Begin Source File

SOURCE=.\CWriteLog.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\CCreateTask.h
# End Source File
# Begin Source File

SOURCE=.\CObjectOwner.h
# End Source File
# Begin Source File

SOURCE=.\CreateTaskForChangedRoad.h
# End Source File
# Begin Source File

SOURCE=.\CreateTaskForChangedRoadDlg.h
# End Source File
# Begin Source File

SOURCE=.\CTransOwner.h
# End Source File
# Begin Source File

SOURCE=.\CWriteLog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\CreateTaskForChangedRoad.ico
# End Source File
# Begin Source File

SOURCE=.\res\CreateTaskForChangedRoad.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
