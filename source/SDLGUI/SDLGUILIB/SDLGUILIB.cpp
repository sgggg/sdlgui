// SDLGUILIB.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "SDLGUILIB.h"


// This is an example of an exported variable
SDLGUILIB_API int nSDLGUILIB=0;

// This is an example of an exported function.
SDLGUILIB_API int fnSDLGUILIB(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see SDLGUILIB.h for the class definition
CSDLGUILIB::CSDLGUILIB()
{
    return;
}
