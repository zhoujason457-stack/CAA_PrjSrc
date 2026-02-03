#ifdef	_WINDOWS_SOURCE
// COPYRIGHT DASSAULT SYSTEMES  2000
#ifdef	__CAAAmtForeignFct
#define	ExportedByCAAAmtForeignFct	__declspec(dllexport)
#else
#define	ExportedByCAAAmtForeignFct	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAAmtForeignFct
#endif
