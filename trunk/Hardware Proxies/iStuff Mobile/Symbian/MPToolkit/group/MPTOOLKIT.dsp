# Microsoft Developer Studio Project File - Name="MPTOOLKIT" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=MPTOOLKIT - Win32 Uni Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MPTOOLKIT.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MPTOOLKIT.mak" CFG="MPTOOLKIT - Win32 Uni Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MPTOOLKIT - Win32 Uni Release" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE "MPTOOLKIT - Win32 Uni Debug" (based on\
 "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MPTOOLKIT - Win32 Uni Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Win32_U0"
# PROP BASE Intermediate_Dir ".\Win32_U0"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB"
# PROP Intermediate_Dir "\dev\Symbian\7.0s\Series60_v20\EPOC32\BUILD\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP\MPTOOLKIT\WINS\UDEB"
# ADD CPP /nologo /Zp4 /GF /MDd /W4 /Zi /Od /X /I "\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP" /I "\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\INC" /I "\dev\Symbian\7.0s\Series60_v20\EPOC32\INCLUDE" /D "__SYMBIAN32__" /D "__VC32__" /D "__WINS__" /D "__DLL__" /D "_DEBUG" /D "_UNICODE" /FR /Fd"\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\Z\SYSTEM\APPS\MPTOOLKIT\MPTOOLKIT.PDB" /c
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\EDLL.LIB" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\euser.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\apparc.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\cone.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\eikcore.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\apgrfx.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\esock.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\btextnotifiers.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\bafl.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\eikcoctl.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\avkon.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\ws32.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\bluetooth.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\flogger.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\mediaclientaudio.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\vibractrl.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\BUILD\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP\MPTOOLKIT\WINS\UDEB\MPTOOLKIT.exp" /nologo /entry:"_E32Dll" /subsystem:windows /dll /pdb:"\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\Z\SYSTEM\APPS\MPTOOLKIT\MPTOOLKIT.pdb" /debug /machine:IX86 /nodefaultlib /include:"?_E32Dll@@YGHPAXI0@Z" /out:"\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\Z\SYSTEM\APPS\MPTOOLKIT\MPTOOLKIT.APP" /WARN:3
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE=$(InputPath)
PreLink_Cmds=echo Doing first-stage link by name\
	nmake -nologo -f "\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP\MPTOOLKIT.SUP.MAKE" PRELINKUDEB\
	if errorlevel 1 nmake -nologo -f "\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP\MPTOOLKIT.SUP.MAKE" STOPLINKUDEB 
PostBuild_Cmds=nmake -nologo -f "\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP\MPTOOLKIT.SUP.MAKE" POSTBUILDUDEB
# End Special Build Tool

!ELSEIF  "$(CFG)" == "MPTOOLKIT - Win32 Uni Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Win32_Un"
# PROP BASE Intermediate_Dir ".\Win32_Un"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UREL"
# PROP Intermediate_Dir "\dev\Symbian\7.0s\Series60_v20\EPOC32\BUILD\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP\MPTOOLKIT\WINS\UREL"
# ADD CPP /nologo /Zp4 /GF /MD /W4 /O1 /Op /X /I "\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP" /I "\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\INC" /I "\dev\Symbian\7.0s\Series60_v20\EPOC32\INCLUDE" /D "__SYMBIAN32__" /D "__VC32__" /D "__WINS__" /D "__DLL__" /D "NDEBUG" /D "_UNICODE" /c
# ADD MTL /nologo /mktyplib203 /D /win32
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UREL\EDLL.LIB" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\euser.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\apparc.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\cone.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\eikcore.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\apgrfx.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\esock.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\btextnotifiers.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\bafl.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\eikcoctl.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\avkon.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\ws32.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\bluetooth.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\flogger.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\mediaclientaudio.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\vibractrl.lib" "\dev\Symbian\7.0s\Series60_v20\EPOC32\BUILD\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP\MPTOOLKIT\WINS\UREL\MPTOOLKIT.exp" /nologo /entry:"_E32Dll" /subsystem:windows /dll /machine:IX86 /nodefaultlib /include:"?_E32Dll@@YGHPAXI0@Z" /out:"\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UREL\Z\SYSTEM\APPS\MPTOOLKIT\MPTOOLKIT.APP" /WARN:3
# Begin Special Build Tool
SOURCE=$(InputPath)
PreLink_Cmds=echo Doing first-stage link by name\
	nmake -nologo -f "\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP\MPTOOLKIT.SUP.MAKE" PRELINKUREL\
	if errorlevel 1 nmake -nologo -f "\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP\MPTOOLKIT.SUP.MAKE" STOPLINKUREL 
PostBuild_Cmds=nmake -nologo -f "\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP\MPTOOLKIT.SUP.MAKE" POSTBUILDUREL
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "MPTOOLKIT - Win32 Uni Debug"
# Name "MPTOOLKIT - Win32 Uni Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\DATA\Mptoolkit.rss
USERDEP__MPTOOLKIT="\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\INC\MPTOOLKIT.HRH"\
 "\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\INC\MPTOOLKIT.LOC"

!IF  "$(CFG)" == "MPTOOLKIT - Win32 Uni Debug"

# PROP Intermediate_Dir "\dev\Symbian\7.0s\Series60_v20\EPOC32\BUILD\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP\MPTOOLKIT\WINS"
# Begin Custom Build - Building resources from Mptoolkit.rss
InputPath=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\DATA\Mptoolkit.rss

BuildCmds= \
	nmake -nologo -f "\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP\MPTOOLKIT.SUP.MAKE"\
  "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\Z\SYSTEM\APPS\MPTOOLKIT\MPTOOLKIT.r"

"\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\Z\SYSTEM\APPS\MPTOOLKIT\MPTOOLKIT.rSC.dummy" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "MPTOOLKIT - Win32 Uni Release"

# PROP Intermediate_Dir "\dev\Symbian\7.0s\Series60_v20\EPOC32\BUILD\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP\MPTOOLKIT\WINS"
# Begin Custom Build - Building resources from Mptoolkit.rss
InputPath=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\DATA\Mptoolkit.rss

BuildCmds= \
	nmake -nologo -f "\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP\MPTOOLKIT.SUP.MAKE"\
  "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UREL\Z\SYSTEM\APPS\MPTOOLKIT\MPTOOLKIT.r"

"\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UREL\Z\SYSTEM\APPS\MPTOOLKIT\MPTOOLKIT.rSC.dummy" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\DATA\Mptoolkit_caption.rss
USERDEP__MPTOOLKIT_CAPTION="\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\INC\MPTOOLKIT.LOC"

!IF  "$(CFG)" == "MPTOOLKIT - Win32 Uni Debug"

# PROP Intermediate_Dir "\dev\Symbian\7.0s\Series60_v20\EPOC32\BUILD\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP\MPTOOLKIT\WINS"
# Begin Custom Build - Building resources from Mptoolkit_caption.rss
InputPath=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\DATA\Mptoolkit_caption.rss

BuildCmds= \
	nmake -nologo -f "\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP\MPTOOLKIT.SUP.MAKE"\
  "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\Z\SYSTEM\APPS\MPTOOLKIT\MPTOOLKIT_CAPTION.r"

"\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UDEB\Z\SYSTEM\APPS\MPTOOLKIT\MPTOOLKIT_CAPTION.rSC.dummy" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ELSEIF  "$(CFG)" == "MPTOOLKIT - Win32 Uni Release"

# PROP Intermediate_Dir "\dev\Symbian\7.0s\Series60_v20\EPOC32\BUILD\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP\MPTOOLKIT\WINS"
# Begin Custom Build - Building resources from Mptoolkit_caption.rss
InputPath=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\DATA\Mptoolkit_caption.rss

BuildCmds= \
	nmake -nologo -f "\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP\MPTOOLKIT.SUP.MAKE"\
  "\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UREL\Z\SYSTEM\APPS\MPTOOLKIT\MPTOOLKIT_CAPTION.r"

"\dev\Symbian\7.0s\Series60_v20\EPOC32\RELEASE\WINS\UREL\Z\SYSTEM\APPS\MPTOOLKIT\MPTOOLKIT_CAPTION.rSC.dummy" : $(SOURCE) "$(INTDIR)"\
 "$(OUTDIR)"
   $(BuildCmds)
# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP\Mptoolkit.uid.cpp
# End Source File
# Begin Source File

SOURCE=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\SRC\Codelistener.cpp
# End Source File
# Begin Source File

SOURCE=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\SRC\Mptoolkitapp.cpp
# End Source File
# Begin Source File

SOURCE=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\SRC\Mptoolkitappui.cpp
# End Source File
# Begin Source File

SOURCE=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\SRC\Mptoolkitcontainer.cpp
# End Source File
# Begin Source File

SOURCE=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\SRC\Mptoolkitdocument.cpp
# End Source File
# Begin Source File

SOURCE=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\SRC\Soundplayer.cpp
# End Source File
# Begin Source File

SOURCE=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\GROUP\Mptoolkit.mmp
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\INC\Codelistener.h
# End Source File
# Begin Source File

SOURCE=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\INC\Mptoolkitapp.h
# End Source File
# Begin Source File

SOURCE=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\INC\Mptoolkitdocument.h
# End Source File
# Begin Source File

SOURCE=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\INC\Soundplayer.h
# End Source File
# Begin Source File

SOURCE=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\INC\Global.h
# End Source File
# Begin Source File

SOURCE=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\INC\Mptoolkitappui.h
# End Source File
# Begin Source File

SOURCE=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\INC\Mptoolkit.hrh
# End Source File
# Begin Source File

SOURCE=\DEV\SYMBIAN\PROJECTS\MPTOOLKIT\INC\Mptoolkitcontainer.h
# End Source File
# End Group
# End Target
# End Project
