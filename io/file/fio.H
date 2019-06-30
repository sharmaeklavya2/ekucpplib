#ifndef _INC_EKU_IO_FIO
#define _INC_EKU_IO_FIO 1
//functions for file IO

#include<cstring>
#include<string>
#include<iostream>
#include<fstream>

#ifdef _INC_SHELLAPI
bool copy_file(const char* from,const char* to)
{
	from[strlen(from)+1]='\0';
	to[strlen(to)+1]='\0';
	return CopyDirectory(from,to);
}

#elif defined(_WINBASE_)
bool copy_file(const char* from,const char* to)
{return CopyFile(from,to,false);}

#else
bool copy_file(const char* from,const char* to)
{
	std::ifstream ffile(from,std::ios::binary);
	std::ofstream tfile(to,std::ios::binary);
	if(!ffile.is_open() || !tfile.is_open())return false;
	tfile<<ffile.rdbuf();
	return true;
}

#endif

bool load_string_from_file(std::string& str,const char* file_path)
{
	STD(ifstream) file;
	file.open(file_path);
	if(!file.is_open())return false;
	getline(file,str,char(EOF));
	return true;
}

#endif	//_INC_EKU_IO_FIO