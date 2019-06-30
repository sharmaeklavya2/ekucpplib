#ifndef _INC_EKU_WINCONIO_WINGETCH
#define _INC_EKU_WINCONIO_WINGETCH
//get a character
#include<windows.h>

namespace eku
{
	char wingetch()
	{
		HANDLE hStdin=GetStdHandle(STD_INPUT_HANDLE);
		INPUT_RECORD irInputRecord;
		DWORD dwEventsRead;
		CHAR cChar;

		while(ReadConsoleInputA (hStdin, &irInputRecord, 1, &dwEventsRead)) /* Read key press */
			if (irInputRecord.EventType == KEY_EVENT
			&&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_SHIFT
			&&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_MENU
			&&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_CONTROL)
			{
				cChar = irInputRecord.Event.KeyEvent.uChar.AsciiChar;
				ReadConsoleInputA (hStdin, &irInputRecord , 1, &dwEventsRead); /* Read key release */
				return cChar;
			}
		return EOF;
	}
}

#endif	//_INC_EKU_WINCONIO_WINGETCH