// COPYRIGHT DASSAULT SYSTEMES 1999

#ifdef _WINDOWS_SOURCE
#ifdef __CAAMmrUtilities
#define ExportedByCAAMmrUtilities __declspec(dllexport)
#else
#define ExportedByCAAMmrUtilities __declspec(dllimport)
#endif
#else
#define ExportedByCAAMmrUtilities
#endif
