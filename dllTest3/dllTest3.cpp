// dllTest3.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "dllTest3.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}


// This is an example of an exported variable
DLLTEST3_API int nDllTest3=0;

// This is an example of an exported function.
DLLTEST3_API int fnDllTest3(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see dllTest3.h for the class definition
CDllTest3::CDllTest3()
{ 
	return; 
}

