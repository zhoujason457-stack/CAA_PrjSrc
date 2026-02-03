// COPYRIGHT DASSAULT SYSTEMES 2002
#ifdef  _WINDOWS_SOURCE
#ifdef  __CAAAdtJournalThreadUtility
#define ExportedByCAAAdtJournalThreadUtility    __declspec(dllexport)
#else
#define ExportedByCAAAdtJournalThreadUtility     __declspec(dllimport)
#endif
#else
#define ExportedByCAAAdtJournalThreadUtility
#endif
