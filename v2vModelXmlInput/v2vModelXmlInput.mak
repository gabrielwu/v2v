# Microsoft Developer Studio Generated NMAKE File, Based on v2vModelXmlInput.dsp
!IF $(CFG)" == "
CFG=v2vModelXmlInput - Win32 Debug
!MESSAGE No configuration specified. Defaulting to v2vModelXmlInput - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "v2vModelXmlInput - Win32 Release" && "$(CFG)" != "v2vModelXmlInput - Win32 Debug"
!MESSAGE 指定的配置 "$(CFG)" 无效.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "v2vModelXmlInput.mak" CFG="v2vModelXmlInput - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "v2vModelXmlInput - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "v2vModelXmlInput - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF $(OS)" == "Windows_NT
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "v2vModelXmlInput - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# 开始自定义宏
OutDir=.\Release
# 结束自定义宏

ALL : "$(OUTDIR)\v2vModelXmlInput.exe"


CLEAN :
	-@erase "$(INTDIR)\auto_model.obj"
	-@erase "$(INTDIR)\base.obj"
	-@erase "$(INTDIR)\diffraction.obj"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\model.obj"
	-@erase "$(INTDIR)\tinystr.obj"
	-@erase "$(INTDIR)\tinyxml.obj"
	-@erase "$(INTDIR)\tinyxmlerror.obj"
	-@erase "$(INTDIR)\tinyxmlparser.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\xmlHelper.obj"
	-@erase "$(OUTDIR)\v2vModelXmlInput.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Fp"$(INTDIR)\v2vModelXmlInput.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\v2vModelXmlInput.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\v2vModelXmlInput.pdb" /machine:I386 /out:"$(OUTDIR)\v2vModelXmlInput.exe" 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\tinystr.obj" \
	"$(INTDIR)\tinyxml.obj" \
	"$(INTDIR)\tinyxmlerror.obj" \
	"$(INTDIR)\tinyxmlparser.obj" \
	"$(INTDIR)\xmlHelper.obj" \
	"$(INTDIR)\auto_model.obj" \
	"$(INTDIR)\base.obj" \
	"$(INTDIR)\diffraction.obj" \
	"$(INTDIR)\model.obj"

"$(OUTDIR)\v2vModelXmlInput.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "v2vModelXmlInput - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# 开始自定义宏
OutDir=.\Debug
# 结束自定义宏

ALL : "$(OUTDIR)\v2vModelXmlInput.exe" "$(OUTDIR)\v2vModelXmlInput.bsc"


CLEAN :
	-@erase "$(INTDIR)\auto_model.obj"
	-@erase "$(INTDIR)\auto_model.sbr"
	-@erase "$(INTDIR)\base.obj"
	-@erase "$(INTDIR)\base.sbr"
	-@erase "$(INTDIR)\diffraction.obj"
	-@erase "$(INTDIR)\diffraction.sbr"
	-@erase "$(INTDIR)\main.obj"
	-@erase "$(INTDIR)\main.sbr"
	-@erase "$(INTDIR)\model.obj"
	-@erase "$(INTDIR)\model.sbr"
	-@erase "$(INTDIR)\tinystr.obj"
	-@erase "$(INTDIR)\tinystr.sbr"
	-@erase "$(INTDIR)\tinyxml.obj"
	-@erase "$(INTDIR)\tinyxml.sbr"
	-@erase "$(INTDIR)\tinyxmlerror.obj"
	-@erase "$(INTDIR)\tinyxmlerror.sbr"
	-@erase "$(INTDIR)\tinyxmlparser.obj"
	-@erase "$(INTDIR)\tinyxmlparser.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\xmlHelper.obj"
	-@erase "$(INTDIR)\xmlHelper.sbr"
	-@erase "$(OUTDIR)\v2vModelXmlInput.bsc"
	-@erase "$(OUTDIR)\v2vModelXmlInput.exe"
	-@erase "$(OUTDIR)\v2vModelXmlInput.ilk"
	-@erase "$(OUTDIR)\v2vModelXmlInput.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\v2vModelXmlInput.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\v2vModelXmlInput.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\main.sbr" \
	"$(INTDIR)\tinystr.sbr" \
	"$(INTDIR)\tinyxml.sbr" \
	"$(INTDIR)\tinyxmlerror.sbr" \
	"$(INTDIR)\tinyxmlparser.sbr" \
	"$(INTDIR)\xmlHelper.sbr" \
	"$(INTDIR)\auto_model.sbr" \
	"$(INTDIR)\base.sbr" \
	"$(INTDIR)\diffraction.sbr" \
	"$(INTDIR)\model.sbr"

"$(OUTDIR)\v2vModelXmlInput.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\v2vModelXmlInput.pdb" /debug /machine:I386 /out:"$(OUTDIR)\v2vModelXmlInput.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\main.obj" \
	"$(INTDIR)\tinystr.obj" \
	"$(INTDIR)\tinyxml.obj" \
	"$(INTDIR)\tinyxmlerror.obj" \
	"$(INTDIR)\tinyxmlparser.obj" \
	"$(INTDIR)\xmlHelper.obj" \
	"$(INTDIR)\auto_model.obj" \
	"$(INTDIR)\base.obj" \
	"$(INTDIR)\diffraction.obj" \
	"$(INTDIR)\model.obj"

"$(OUTDIR)\v2vModelXmlInput.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("v2vModelXmlInput.dep")
!INCLUDE "v2vModelXmlInput.dep"
!ELSE 
!MESSAGE Warning: cannot find "v2vModelXmlInput.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "v2vModelXmlInput - Win32 Release" || "$(CFG)" == "v2vModelXmlInput - Win32 Debug"
SOURCE=.\main.cpp

!IF  "$(CFG)" == "v2vModelXmlInput - Win32 Release"


"$(INTDIR)\main.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "v2vModelXmlInput - Win32 Debug"


"$(INTDIR)\main.obj"	"$(INTDIR)\main.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=..\..\..\..\..\Projects\v2vModel\v2vModel\tinystr.cpp

!IF  "$(CFG)" == "v2vModelXmlInput - Win32 Release"


"$(INTDIR)\tinystr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "v2vModelXmlInput - Win32 Debug"


"$(INTDIR)\tinystr.obj"	"$(INTDIR)\tinystr.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\..\Projects\v2vModel\v2vModel\tinyxml.cpp

!IF  "$(CFG)" == "v2vModelXmlInput - Win32 Release"


"$(INTDIR)\tinyxml.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "v2vModelXmlInput - Win32 Debug"


"$(INTDIR)\tinyxml.obj"	"$(INTDIR)\tinyxml.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\..\Projects\v2vModel\v2vModel\tinyxmlerror.cpp

!IF  "$(CFG)" == "v2vModelXmlInput - Win32 Release"


"$(INTDIR)\tinyxmlerror.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "v2vModelXmlInput - Win32 Debug"


"$(INTDIR)\tinyxmlerror.obj"	"$(INTDIR)\tinyxmlerror.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\..\Projects\v2vModel\v2vModel\tinyxmlparser.cpp

!IF  "$(CFG)" == "v2vModelXmlInput - Win32 Release"


"$(INTDIR)\tinyxmlparser.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "v2vModelXmlInput - Win32 Debug"


"$(INTDIR)\tinyxmlparser.obj"	"$(INTDIR)\tinyxmlparser.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\..\..\Projects\v2vModel\v2vModel\xmlHelper.cpp

!IF  "$(CFG)" == "v2vModelXmlInput - Win32 Release"


"$(INTDIR)\xmlHelper.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "v2vModelXmlInput - Win32 Debug"


"$(INTDIR)\xmlHelper.obj"	"$(INTDIR)\xmlHelper.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\auto_model.cpp

!IF  "$(CFG)" == "v2vModelXmlInput - Win32 Release"


"$(INTDIR)\auto_model.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "v2vModelXmlInput - Win32 Debug"


"$(INTDIR)\auto_model.obj"	"$(INTDIR)\auto_model.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\base.cpp

!IF  "$(CFG)" == "v2vModelXmlInput - Win32 Release"


"$(INTDIR)\base.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "v2vModelXmlInput - Win32 Debug"


"$(INTDIR)\base.obj"	"$(INTDIR)\base.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\diffraction.cpp

!IF  "$(CFG)" == "v2vModelXmlInput - Win32 Release"


"$(INTDIR)\diffraction.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "v2vModelXmlInput - Win32 Debug"


"$(INTDIR)\diffraction.obj"	"$(INTDIR)\diffraction.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\model.cpp

!IF  "$(CFG)" == "v2vModelXmlInput - Win32 Release"


"$(INTDIR)\model.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "v2vModelXmlInput - Win32 Debug"


"$(INTDIR)\model.obj"	"$(INTDIR)\model.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

