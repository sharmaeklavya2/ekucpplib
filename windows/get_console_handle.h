#ifndef _INC_EKU_GET_CONSOLE_HANDLE
#define _INC_EKU_GET_CONSOLE_HANDLE

namespace eku
{
	HWND get_console_handle()
	{
		TCHAR title[256];
		GetConsoleTitle(title,500);
		return FindWindow(NULL,title);
	}
}

#endif	//_INC_EKU_GET_CONSOLE_HANDLE