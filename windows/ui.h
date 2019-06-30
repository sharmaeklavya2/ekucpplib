#ifndef _INC_EKU_WINDOWS_UI
#define _INC_EKU_WINDOWS_UI

#include<tchar.h>
#include<eku\miscdef.h>
#include<eku\tchar\tstring.h>
#include<eku\windows\no_windows_error.h>
#include<eku\windows\get_console_handle.h>

namespace eku
{

	bool winin(const TCHAR* ques,const TCHAR* caption,HWND hwnd=NULL)
	{return (MessageBox(hwnd,ques,caption,MB_ICONQUESTION|MB_YESNO)==IDYES);}

	bool winin_con(const TCHAR* ques)
	{
		TCHAR title[500];
		HWND hwnd;
		GetConsoleTitle(title,500);
		hwnd=FindWindow(NULL,title);
		return (MessageBox(hwnd,ques,title,MB_ICONQUESTION|MB_YESNO)==IDYES);
	}

}

#endif	//_INC_EKU_WINDOWS_UI