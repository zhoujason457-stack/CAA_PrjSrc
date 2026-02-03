#ifdef	_WINDOWS_SOURCE
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
#ifdef	__CAATopCheckJournal
#define	ExportedByCAATopCheckJournal	__declspec(dllexport)
#else
#define	ExportedByCAATopCheckJournal	__declspec(dllimport)
#endif
#else
#define	ExportedByCAATopCheckJournal
#endif
