#ifndef _INC_EKU_WINDOWS_EXEC
#define _INC_EKU_WINDOWS_EXEC

#include<eku\windows\no_windows_error.h>

namespace eku
{
	bool exec(const TCHAR* prog,TCHAR* cmd,bool wait=true)
	//Creates a new process
	//prog - path to .exe file
	//cmd - command line to be passed to program
	//wait - wait for the process to end before continuing
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si,sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi,sizeof(pi));

		if(!CreateProcess(prog,   //Program name
			cmd,	//Command line
			NULL,	//Process handle not inheritable
			NULL,	//Thread handle not inheritable
			FALSE,	//Set handle inheritance to FALSE
			0,		//No creation flags
			NULL,	//Use parent's environment block
			NULL,	//Use parent's starting directory 
			&si,	//Pointer to STARTUPINFO structure
			&pi )	//Pointer to PROCESS_INFORMATION structure
		)return false;
		
		//Wait until child process exits.
		if(wait)WaitForSingleObject(pi.hProcess,INFINITE);

		//Close process and thread handles. 
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		return true;
	}
}

#endif	//_INC_EKU_WINDOWS_EXEC