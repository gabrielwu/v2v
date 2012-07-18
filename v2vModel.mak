# Microsoft Developer Studio Generated NMAKE File, Based on v2vModel.dsp
!IF $(CFG)" == "
CFG=v2vModel - Win32 Debug
!MESSAGE No configuration specified. Defaulting to v2vModel - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "v2vModel - Win32 Release" && "$(CFG)" != "v2vModel - Win32 Debug"
!MESSAGE 指定的配置 "$(CFG)" 无效.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "v2vModel.mak" CFG="v2vModel - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "v2vModel - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "v2vModel - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF $(OS)" == "Windows_NT
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "v2vModel - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# 开始自定义宏
OutDir=.\Release
# 结束自定义宏

ALL : "$(OUTDIR)\v2vModel.exe"


CLEAN :
	-@erase "$(INTDIR)\auto_model.obj"
	-@erase "$(INTDIR)\base.obj"
	-@erase "$(INTDIR)\diffraction.obj"
	-@erase "$(INTDIR)\mainExcel.obj"
	-@erase "$(INTDIR)\model.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\v2vModel.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\v2vModel.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\v2vModel.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\v2vModel.pdb" /machine:I386 /out:"$(OUTDIR)\v2vModel.exe" 
LINK32_OBJS= \
	"$(INTDIR)\mainExcel.obj" \
	"$(INTDIR)\auto_model.obj" \
	"$(INTDIR)\base.obj" \
	"$(INTDIR)\diffraction.obj" \
	"$(INTDIR)\model.obj"

"$(OUTDIR)\v2vModel.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "v2vModel - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# 开始自定义宏
OutDir=.\Debug
# 结束自定义宏

ALL : "$(OUTDIR)\v2vModel.exe"


CLEAN :
	-@erase "$(INTDIR)\auto_model.obj"
	-@erase "$(INTDIR)\base.obj"
	-@erase "$(INTDIR)\diffraction.obj"
	-@erase "$(INTDIR)\mainExcel.obj"
	-@erase "$(INTDIR)\model.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\v2vModel.exe"
	-@erase "$(OUTDIR)\v2vModel.ilk"
	-@erase "$(OUTDIR)\v2vModel.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\v2vModel.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\v2vModel.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\v2vModel.pdb" /debug /machine:I386 /out:"$(OUTDIR)\v2vModel.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\mainExcel.obj" \
	"$(INTDIR)\auto_model.obj" \
	"$(INTDIR)\base.obj" \
	"$(INTDIR)\diffraction.obj" \
	"$(INTDIR)\model.obj"

"$(OUTDIR)\v2vModel.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("v2vModel.dep")
!INCLUDE "v2vModel.dep"
!ELSE 
!MESSAGE Warning: cannot find "v2vModel.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "v2vModel - Win32 Release" || "$(CFG)" == "v2vModel - Win32 Debug"
SOURCE=.\mainExcel.cpp

"$(INTDIR)\mainExcel.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\auto_model.cpp

"$(INTDIR)\auto_model.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\base.cpp

"$(INTDIR)\base.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\diffraction.cpp

"$(INTDIR)\diffraction.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\model.cpp

"$(INTDIR)\model.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

