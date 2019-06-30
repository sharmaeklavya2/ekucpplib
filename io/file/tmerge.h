#ifndef _INC_EKU_IO_FILE_TMERGE
#define _INC_EKU_IO_FILE_TMERGE

#include<eku\io\getline.h>

namespace eku
{
	bool merge_tfiles(const char* ifname1,const char* ifname2,const char* ofname)
	//merges 2 text files into a 3rd file
	{
		std::string str1,str2;
		std::ifstream ifile1(ifname1),ifile2(ifname2);
		std::ofstream ofile(ofname);
		bool in1=false,in2=false;
		if(!ifile1.is_open())return false;
		if(!ifile2.is_open())return false;
		if(!ofile.is_open())return false;
		in1=!(atleast_getline(ifile1,str1).fail());
		in2=!(atleast_getline(ifile2,str2).fail());
		while(in1 && in2)
		{
			if(str1<str2)
			{ofile<<str1<<'\n';in1=!atleast_getline(ifile1,str1).fail();}
			else
			{ofile<<str2<<'\n';in2=!atleast_getline(ifile2,str2).fail();}
		}
		while(in1)
		{ofile<<str1<<'\n';in1=!atleast_getline(ifile1,str1).fail();}
		while(in2)
		{ofile<<str2<<'\n';in2=!atleast_getline(ifile2,str2).fail();}
		return true;
	}
}

#endif	//_INC_EKU_IO_FILE_TMERGE