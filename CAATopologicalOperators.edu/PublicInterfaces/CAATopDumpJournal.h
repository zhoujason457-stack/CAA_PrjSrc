#ifdef	_WINDOWS_SOURCE
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
#ifdef	__CAATopDumpJournal
#define	ExportedByCAATopDumpJournal	__declspec(dllexport)
#else
#define	ExportedByCAATopDumpJournal	__declspec(dllimport)
#endif
#else
#define	ExportedByCAATopDumpJournal
#endif
