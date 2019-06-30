#ifndef _INC_EKU_WINDOWS_IN_STYLE
#define _INC_EKU_WINDOWS_IN_STYLE

//#defining IN_STYLE makes windows applications look better.
//Otherwise they have a windows 2000 look.
#ifdef IN_STYLE
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' \
version='6.0.0.0' processorArchitecture='*' \
publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif	//IN_STYLE

#endif	//_INC_EKU_WINDOWS_IN_STYLE