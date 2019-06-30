#ifndef _INC_EKU_WINDOWS_DELETE_DIRECTORY
#define _INC_EKU_WINDOWS_DELETE_DIRECTORY

#include<eku\windows\no_windows_error.h>

namespace eku
{
	bool delete_directory(LPCTSTR lpszDir, bool noRecycleBin=true)
	{
		SHFILEOPSTRUCT fileop;
		fileop.hwnd   = NULL;		// no status display
		fileop.wFunc  = FO_DELETE;	// delete operation
		fileop.pFrom  = lpszDir;	// source file name as double null terminated string
		fileop.pTo    = NULL;		// no destination needed
		fileop.fFlags = FOF_NOCONFIRMATION|FOF_SILENT|FOF_NOCONFIRMMKDIR;	// do not prompt the user

		if(!noRecycleBin)fileop.fFlags |= FOF_ALLOWUNDO;

		fileop.fAnyOperationsAborted = FALSE;
		fileop.lpszProgressTitle     = NULL;
		fileop.hNameMappings         = NULL;

		int ret = SHFileOperation(&fileop);
		return (ret == 0);
	}
}

#endif	//_INC_EKU_WINDOWSDELETE_DIRECTORY