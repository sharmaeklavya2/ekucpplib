#ifndef _INC_EKU_WINDOWS_DEFAULT_FILL_WNDCLASSEX
#define _INC_EKU_WINDOWS_DEFAULT_FILL_WNDCLASSEX

#include<eku\windows\no_windows_error.h>

//returns a WNDCLASSEX structure filled with default values

namespace eku
{
	void default_fill_wndclassex(WNDCLASSEX& wc,HINSTANCE hInstance1,WNDPROC wndproc,LPCTSTR classname)
	{
		wc.cbSize			= sizeof(tagWNDCLASSEXW);
		wc.style			= CS_HREDRAW | CS_VREDRAW;
		wc.cbClsExtra		= NULL;
		wc.cbWndExtra		= NULL;
		wc.hInstance		= hInstance1;
		wc.hIcon			= LoadIcon(hInstance1, IDI_APPLICATION);
		wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
		wc.lpszClassName	= classname;
		wc.lpfnWndProc		= wndproc;
		wc.lpszMenuName		= NULL;
		wc.hIconSm			= LoadIcon(hInstance1, IDI_APPLICATION);
	}
}

#endif	//_INC_EKU_WINDOWS_DEFAULT_FILL_WNDCLASSEX