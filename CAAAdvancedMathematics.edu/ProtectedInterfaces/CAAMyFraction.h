#ifdef	_WINDOWS_SOURCE
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
#ifdef	__CAAMyFraction
#define	ExportedByCAAMyFraction	__declspec(dllexport)
#else
#define	ExportedByCAAMyFraction	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAMyFraction
#endif
