#ifndef _INC_EKU_IO_BFILE
#define _INC_EKU_IO_BFILE

#include<fstream>

namespace eku
{
	template<class typ>
	//read binary data from input stream and display it appropriately
	void read_from_bfile(std::istream& ifile,std::ostream& os)
	{
		int i;typ obj;
		for(i=1;ifile.read((elem*)&obj,sizeof(typ));++i)
		{os<<i<<"th elem = "<<obj<<endl;}
	}

	template<class typ>
	//read data from input stream and paste binarily to ofile
	void write_to_bfile(std::ostream& ofile,int n,std::istream& is)
	{
		int i,n;typ obj;
		for(i=1;i<=n;i++)
		{
			cout<<"Enter "<<i<<"th elem:\n";
			is>>obj;
			ofile.write((char*)&obj,sizeof(typ));
		}
	}

	template<class typ>
	//read binary data from file and display it appropriately
	bool read_from_bfilename(const char* fname,std::ostream& os)
	{
		ifstream ifile(fname,ios::binary);
		if(!ifile.is_open())
		{os<<"Error: Couldn't open file"<<endl;return false;}
		read_from_bfile<typ>(ifile,os);
		ifile.close();
		return true;
	}

	template<class typ>
	bool write_to_bfilename(const char* fname,int n,std::istream& is)
	{
		ofstream ofile(fname,ios::binary);
		if(!ofile.is_open())
		{std::cerr<<"Error: Couldn't open file"<<endl;return false;}
		write_to_bfile<typ>(ofile,n,is);
		ofile.close();
		return true;
	}
	bool concat_files(const char* ifname1,const char* ifname2,const char* ofname)
	{
		std::ifstream ifile1(ifname1,std::ios::binary);
		std::ifstream ifile2(ifname2,std::ios::binary);
		std::ofstream ofile(ofname,std::ios::binary);
		if(!ifile1.is_open() || !ifile2.is_open() || !ofile.is_open())return false;
		ofile<<ifile1.rdbuf()<<ifile2.rdbuf();
		return true;
	}
}

#endif	//_INC_EKU_IO_BFILE