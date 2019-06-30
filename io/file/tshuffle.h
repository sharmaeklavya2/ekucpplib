#ifndef _INC_EKU_IO_FILE_TSHUFFLE
#define _INC_EKU_IO_FILE_TSHUFFLE

#include<cstdlib>
#include<ctime>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<eku\io\getline.h>
#include<eku\io\file\bfile.h>

#ifndef TMP_FILE_NAME_SIZE
#define TMP_FILE_NAME_SIZE 40
#endif	//TMP_FILE_NAME_SIZE

namespace eku
{
	bool shuffle_tfile_internal(const char* fname)
	{
		std::vector<std::string> v;
		std::string str;
		std::ifstream ifile(fname);
		std::ofstream ofile;
		std::vector<std::string>::iterator it;
		if(!ifile.is_open())return false;
		while(atleast_getline(ifile,str))v.push_back(str);
		ifile.close();
		std::random_shuffle(v.begin(),v.end());
		ofile.open(fname,std::ios::out|std::ios::trunc);
		if(!ofile.is_open())return false;
		for(it=v.begin();it!=v.end();++it)ofile<<*it<<'\n';
		ofile.close();
		return true;
	}

	bool shuffle_tfile_internal(const char* ifname,const char* ofname)
	{
		std::vector<std::string> v;
		std::string str;
		std::ifstream ifile(ifname);
		std::ofstream ofile(ofname);
		std::vector<std::string>::iterator it;
		if(!ifile.is_open() || !ofile.is_open())return false;
		while(atleast_getline(ifile,str))v.push_back(str);
		ifile.close();
		std::random_shuffle(v.begin(),v.end());
		for(it=v.begin();it!=v.end();++it)ofile<<*it<<'\n';
		return true;
	}

	bool shuffle_tfile(const char* fname,unsigned max_size=1048576)
	//size below which internal sorting will take place
	{
		bool firstfile=true;
		std::string str;
		unsigned size;

		//temporary file names
		char tmpname1[TMP_FILE_NAME_SIZE];
		char tmpname2[TMP_FILE_NAME_SIZE];
		
		//open input file
		std::ifstream ifile(fname);
		if(!ifile.is_open())return false;

		//get size of file. If it is small, sort it internally
		ifile.seekg(0,std::ios::end);
		size=ifile.tellg();
		ifile.seekg(0,std::ios::beg);
		if(size<=max_size)
		{
			ifile.close();
			if(!shuffle_tfile_internal(fname))return false;
			return true;
		}

		//get names of temp files and open them
	#pragma warning(disable:4996)
		std::tmpnam(tmpname1);
		std::tmpnam(tmpname2);
	#pragma warning(default:4996)
		std::ofstream tmp1(tmpname1+1);
		std::ofstream tmp2(tmpname2+1);
		if(!tmp1.is_open() || !tmp2.is_open())return false;

		std::srand(unsigned(time(NULL)));

		//write half lines to tmp1 and other half to tmp2
		while(atleast_getline(ifile,str))
		{
			if(std::rand()&1)tmp1<<str<<'\n';
			else tmp2<<str<<'\n';
			firstfile=!firstfile;
		}

		//close files
		ifile.close();
		tmp1.close();
		tmp2.close();

		if(!shuffle_tfile(tmpname1+1))return false;
		if(!shuffle_tfile(tmpname2+1))return false;
		if(!concat_files(tmpname1+1,tmpname2+1,fname))return false;

		std::remove(tmpname1+1);
		std::remove(tmpname2+1);

		return true;
	}

	bool shuffle_tfile(const char* ifname,const char* ofname,unsigned max_size=1048576)
	//size below which internal sorting will take place
	{
		bool firstfile=true;
		std::string str;
		unsigned size;

		//temporary file names
		char tmpname1[TMP_FILE_NAME_SIZE];
		char tmpname2[TMP_FILE_NAME_SIZE];
		
		//open input file
		std::ifstream ifile(ifname);
		if(!ifile.is_open())return false;

		//get size of file. If it is small, sort it internally
		ifile.seekg(0,std::ios::end);
		size=ifile.tellg();
		ifile.seekg(0,std::ios::beg);
		if(size<=max_size)
		{
			ifile.close();
			if(!shuffle_tfile_internal(ifname,ofname))return false;
			return true;
		}

		//get names of temp files and open them
#pragma warning(disable:4996)
		std::tmpnam(tmpname1);
		std::tmpnam(tmpname2);
#pragma warning(default:4996)
		std::ofstream tmp1(tmpname1+1);
		std::ofstream tmp2(tmpname2+1);
		if(!tmp1.is_open() || !tmp2.is_open())return false;

		std::srand(unsigned(time(NULL)));

		//write half lines to tmp1 and other half to tmp2
		while(atleast_getline(ifile,str))
		{
			if(std::rand()&1)tmp1<<str<<'\n';
			else tmp2<<str<<'\n';
			firstfile=!firstfile;
		}

		//close files
		ifile.close();
		tmp1.close();
		tmp2.close();

		if(!shuffle_tfile(tmpname1+1))return false;
		if(!shuffle_tfile(tmpname2+1))return false;
		if(!concat_files(tmpname1+1,tmpname2+1,ofname))return false;

		std::remove(tmpname1+1);
		std::remove(tmpname2+1);

		return true;
	}
}

#endif	//_INC_EKU_IO_FILE_TSHUFFLE