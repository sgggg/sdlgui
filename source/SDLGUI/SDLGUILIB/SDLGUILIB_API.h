// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SDLGUILIB_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SDLGUILIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef SDLGUILIB_EXPORTS
#define SDLGUILIB_API __declspec(dllexport)
#else
#define SDLGUILIB_API __declspec(dllimport)
#endif

/*
// Example usage:

// This class is exported from the SDLGUILIB.dll
class SDLGUILIB_API CSDLGUILIB {
public:
	CSDLGUILIB(void);
	// TODO: add your methods here.
};

extern SDLGUILIB_API int nSDLGUILIB;

SDLGUILIB_API int fnSDLGUILIB(void);

*/