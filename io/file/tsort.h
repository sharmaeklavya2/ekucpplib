#ifndef _INC_EKU_IO_FILE_TSORT
#define _INC_EKU_IO_FILE_TSORT

#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<eku\str_case_ins_cmp.h>
#include<eku\io\getline.h>
#include<eku\io\file\tmerge.h>

#ifndef TMP_FILE_NAME_SIZE
#define TMP_FILE_NAME_SIZE 40
#endif	//TMP_FILE_NAME_SIZE

namespace eku
{
	bool sort_tfile_internal(const char* ifname,const char* ofname,bool case_sens=true)
	//sorts a tfile by copying all its data and sorting it
	{
		std::vector<std::string> v;
		std::string str;
		std::ifstream ifile(ifname);
		std::ofstream ofile(ofname);
		std::vector<std::string>::iterator it;
		if(!ifile.is_open() || !ofile.is_open())return false;
		while(atleast_getline(ifile,str))v.push_back(str);
		ifile.close();
		if(case_sens)std::sort(v.begin(),v.end());
		else std::sort(v.begin(),v.end(),isless);
		for(it=v.begin();it!=v.end();++it)ofile<<*it<<'\n';
		ofile.close();
		return true;
	}

	bool sort_tfile_internal(const char* fname,bool case_sens=true)
	//sorts a tfile by copying all its data and sorting it
	{
		std::vector<std::string> v;
		std::string str;
		std::ifstream ifile(fname);
		std::ofstream ofile;
		std::vector<std::string>::iterator it;
		if(!ifile.is_open())return false;
		while(atleast_getline(ifile,str))v.push_back(str);
		ifile.close();
		if(case_sens)std::sort(v.begin(),v.end());
		else std::sort(v.begin(),v.end(),isless);
		ofile.open(fname,std::ios::out|std::ios::trunc);
		if(!ofile.is_open())return false;
		for(it=v.begin();it!=v.end();++it)ofile<<*it<<'\n';
		ofile.close();
		return true;
	}

	bool mergesort_tfile(const char* fname,bool case_sens=true,unsigned max_size=1048576)
	/*sorts a text files using the merge sort algorithm
	case_sens means case sensitive comparison
	max_size is maximum file size the function can sort in one go.
	if size of file is more than max_size, the function
	splits the file into 2 and recurively sorts.
	Default max_size is 1MB*/
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
			if(!sort_tfile_internal(fname,case_sens))return false;
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

		//write half lines to tmp1 and other half to tmp2
		while(atleast_getline(ifile,str))
		{
			if(firstfile)tmp1<<str<<'\n';
			else tmp2<<str<<'\n';
			firstfile=!firstfile;
		}

		//close files
		ifile.close();
		tmp1.close();
		tmp2.close();

		if(!mergesort_tfile(tmpname1+1))return false;
		if(!mergesort_tfile(tmpname2+1))return false;
		if(!merge_tfiles(tmpname1+1,tmpname2+1,fname))return false;

		std::remove(tmpname1+1);
		std::remove(tmpname2+1);

		return true;
	}

	bool mergesort_tfile(const char* ifname,const char* ofname,bool case_sens=true,unsigned max_size=1048576)
	/*sorts a text files using the merge sort algorithm
	case_sens means case sensitive comparison
	max_size is maximum file size the function can sort in one go.
	if size of file is more than max_size, the function
	splits the file into 2 and recurively sorts.
	Default max_size is 1MB*/
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
			if(!sort_tfile_internal(ifname,ofname,case_sens))return false;
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

		//write half lines to tmp1 and other half to tmp2
		while(atleast_getline(ifile,str))
		{
			if(firstfile)tmp1<<str<<'\n';
			else tmp2<<str<<'\n';
			firstfile=!firstfile;
		}

		//close files
		ifile.close();
		tmp1.close();
		tmp2.close();

		if(!mergesort_tfile(tmpname1+1))return false;
		if(!mergesort_tfile(tmpname2+1))return false;
		if(!merge_tfiles(tmpname1+1,tmpname2+1,ofname))return false;

		std::remove(tmpname1+1);
		std::remove(tmpname2+1);

		return true;
	}
}

#endif	//_INC_EKU_IO_FILE_TSORT