#ifndef _INC_EKU_DEFAULT_FILL_CHOOSEFONT
#define _INC_EKU_DEFAULT_FILL_CHOOSEFONT

#include<eku\windows\no_windows_error.h>

namespace eku
{
	void default_fill_choosefont(CHOOSEFONT* cf,LOGFONT* lpLogFont,HWND hwnd=NULL)
	{
		ZeroMemory(cf,sizeof(CHOOSEFONT));
		cf->lStructSize=sizeof(CHOOSEFONT);
		cf->hwndOwner=hwnd;
		cf->lpLogFont=lpLogFont;
	}
}

#endif	//_INC_EKU_DEFAULT_FILL_CHOOSEFONT