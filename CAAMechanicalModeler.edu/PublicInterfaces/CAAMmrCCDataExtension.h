// COPYRIGHT DASSAULT SYSTEMES 2007
#ifdef  _WINDOWS_SOURCE
#ifdef  __CAAMmrCCDataExtension
#define ExportedByCAAMmrCCDataExtension     __declspec(dllexport)
#else
#define ExportedByCAAMmrCCDataExtension     __declspec(dllimport)
#endif
#else
#define ExportedByCAAMmrCCDataExtension
#endif
