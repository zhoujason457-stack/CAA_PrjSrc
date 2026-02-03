// COPYRIGHT DASSAULT SYSTEMES 2002
#ifdef  _WINDOWS_SOURCE
#ifdef  __CAAAdtThreadUtility
#define ExportedByCAAAdtThreadUtility    __declspec(dllexport)
#else
#define ExportedByCAAAdtThreadUtility     __declspec(dllimport)
#endif
#else
#define ExportedByCAAAdtThreadUtility
#endif
