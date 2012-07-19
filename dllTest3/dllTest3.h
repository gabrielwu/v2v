
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DLLTEST3_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DLLTEST3_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef DLLTEST3_EXPORTS
#define DLLTEST3_API __declspec(dllexport)
#else
#define DLLTEST3_API __declspec(dllimport)
#endif

// This class is exported from the dllTest3.dll
class DLLTEST3_API CDllTest3 {
public:
	CDllTest3(void);
	// TODO: add your methods here.
};

extern DLLTEST3_API int nDllTest3;

DLLTEST3_API int fnDllTest3(void);

