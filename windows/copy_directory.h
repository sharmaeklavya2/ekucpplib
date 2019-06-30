#ifndef _INC_EKU_WINDOWS_COPY_DIRECTORY
#define _INC_EKU_WINDOWS_COPY_DIRECTORY

#include<eku\windows\no_windows_error.h>

namespace eku
{
	bool copy_directory(LPCTSTR frompath,LPCTSTR topath, bool noUndo=true)
	{
		SHFILEOPSTRUCT fileop;
		memset(&fileop,0,sizeof(fileop));
		fileop.hwnd   = NULL;		// no status display
		fileop.wFunc  = FO_COPY;	// copy operation
		fileop.pFrom  = frompath;	// source file name as double null terminated string
		fileop.pTo    = topath;		// no destination needed
		fileop.fFlags = FOF_NOCONFIRMATION|FOF_SILENT|FOF_NOCONFIRMMKDIR|FOF_MULTIDESTFILES;	// do not prompt the user

		if(!noUndo)fileop.fFlags |= FOF_ALLOWUNDO;

		fileop.fAnyOperationsAborted = FALSE;
		fileop.lpszProgressTitle     = NULL;
		fileop.hNameMappings         = NULL;

		int ret = SHFileOperation(&fileop);
		return (ret == 0);
	}
}

#endif	//_INC_EKU_WINDOWS_COPY_DIRECTORY