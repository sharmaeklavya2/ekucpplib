#ifndef _INC_EKU_WINDOWS_GET_STR_FROM_EDIT
#define _INC_EKU_WINDOWS_GET_STR_FROM_EDIT

#include<eku\windows\no_windows_error.h>
#include<string>
#include<eku\tchar\tstring.h>

namespace eku
{
	bool get_str_from_edit(HWND hEdit,eku::tstring& a)
	//Gets a std::string from a text box
	{
		int len=GetWindowTextLength(hEdit);
		if(len>0)
		{
			TCHAR* buf;
			buf=(TCHAR*)GlobalAlloc(GPTR,len+1);
			GetWindowText(hEdit,buf,len+1);
			a=buf;
			GlobalFree((HANDLE)buf);
			return true;
		}
		else return false;
	}
}

#endif	//_INC_EKU_WINDOWS_GET_STR_FROM_EDIT