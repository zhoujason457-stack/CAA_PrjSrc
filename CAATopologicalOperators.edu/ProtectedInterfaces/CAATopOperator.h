#ifdef	_WINDOWS_SOURCE
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
#ifdef	__CAATopOperator
#define	ExportedByCAATopOperator	__declspec(dllexport)
#else
#define	ExportedByCAATopOperator	__declspec(dllimport)
#endif
#else
#define	ExportedByCAATopOperator
#endif
