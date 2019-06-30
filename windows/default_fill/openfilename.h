#ifndef _INC_EKU_DEFAULT_FILL_OPENFILENAME
#define _INC_EKU_DEFAULT_FILL_OPENFILENAME

#include<eku\windows\no_windows_error.h>

namespace eku
{
	void default_fill_openfilename(OPENFILENAME* ofn,LPTSTR path,
		int size,	//size of 'path'
		LPCTSTR title=TEXT("Open"),
		HWND hwnd=NULL,	//owner window
		LPCTSTR filter=TEXT("All files\0*.*\0"),
		LPCTSTR defext=TEXT("txt"))
	//Parameter struct for Open and Save file dialogs
	//The resulting structure will be used for the functions GetOpenFileName() and GetSaveFileName()
	{
		ZeroMemory(ofn,sizeof(ofn));
		ofn->lStructSize=sizeof(ofn);
		ofn->hwndOwner=hwnd;
		ofn->lpstrFilter=filter;
		ofn->lpstrFile=path;
		ofn->nMaxFile=size;
		ofn->lpstrDefExt=defext;
		ofn->lpstrTitle=title;
	}
}

#endif	//_INC_EKU_DEFAULT_FILL_OPENFILENAME