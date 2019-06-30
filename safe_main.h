#ifndef _INC_EKU_SAFE_MAIN
#define _INC_EKU_SAFE_MAIN

#include<stdexcept>
#include<iostream>

int safe_main();

int main()
{
	try{return safe_main();}
	catch(const std::exception& e)
	{std::cout<<"Exception: "<<e.what()<<std::endl;}
	catch(...)
	{std::cout<<"An unknown exception was thrown"<<std::endl;}
	return 12345;
}

#define main safe_main

#endif	//_INC_EKU_SAFE_MAIN