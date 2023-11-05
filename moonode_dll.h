// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the MOONODE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// MOONODE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef MOONODE_EXPORTS
#define MOONODE_API __declspec(dllexport)
#else
#define MOONODE_API __declspec(dllimport)
#endif

// This class is exported from the dll
//class MOONODE_API Cmoonode {
//public:
//	Cmoonode(void);
//	// TODO: add your methods here.
//};

//extern MOONODE_API int nmoonode;

//MOONODE_API int fnmoonode(void);
