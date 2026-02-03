// COPYRIGHT DASSAULT SYSTEMES 2012

#ifdef _WINDOWS_SOURCE
#ifdef __CAAV5V6MmrUtilities
#define ExportedByCAAV5V6MmrUtilities __declspec(dllexport)
#else
#define ExportedByCAAV5V6MmrUtilities __declspec(dllimport)
#endif
#else
#define ExportedByCAAV5V6MmrUtilities
#endif
