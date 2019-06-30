#ifndef _INC_EKU_IO_AUTOTAP
#define _INC_EKU_IO_AUTOTAP
//automatically taps std input to a text file

#ifndef NO_AUTO_DTAP
#define AUTO_DTAP
#endif	//NO_AUTO_TAP

#ifndef TAPPED_TEMP_FILE
#define TAPPED_TEMP_FILE "tap2.txt"
#endif	//TAPPED_TEMP_FILE

#ifndef TAPPED_FINAL_FILE
#define TAPPED_FINAL_FILE "tap.txt"
#endif	//TAPPED_FINAL_FILE

#include<eku\io\dtapped_istream.h>

#endif	//_INC_EKU_IO_AUTOTAP