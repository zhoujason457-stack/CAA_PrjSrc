#ifdef	_WINDOWS_SOURCE
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
#ifdef	__CAAGMOperatorsOperatorCreation
#define	ExportedByCAAGMOperatorsOperatorCreation	__declspec(dllexport)
#else
#define	ExportedByCAAGMOperatorsOperatorCreation	__declspec(dllimport)
#endif
#else
#define	ExportedByCAAGMOperatorsOperatorCreation
#endif
