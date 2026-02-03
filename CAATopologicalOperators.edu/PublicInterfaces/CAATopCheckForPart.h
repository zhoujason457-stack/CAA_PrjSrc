#ifdef	_WINDOWS_SOURCE
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
#ifdef	__CAATopCheckForPart
#define	ExportedByCAATopCheckForPart	__declspec(dllexport)
#else
#define	ExportedByCAATopCheckForPart	__declspec(dllimport)
#endif
#else
#define	ExportedByCAATopCheckForPart
#endif
