#ifndef _INC_EKU_IO_DTAPPED_ISTREAM
#define _INC_EKU_IO_DTAPPED_ISTREAM

/*
This header file defines a variant of std::istream
All input operations done with this class are tapped
and written to a file.

This header file is different from <eku\io\tapped_istream.h>,
which does not use a temporary file

#define DTAPPED_FILE to a filename to make dtapped_cin
#define DTAPPED_WFILE to a filename to make dtapped_wcin
#define DTAPPED_TFILE which will check if UNICODE is defined

#define AUTO_DTAP and use namespace std to use cin,wcin to tap

*/

#include<string>
#include<cstring>
#include<fstream>
#include<iostream>
#include<cstdio>
#include<eku\tchar\tiostream.h>

namespace eku
{
	template<typename elem,typename traits=std::char_traits<elem> >
	class basic_dtapped_streambuf:public std::basic_streambuf<elem,traits>
	{
		const static unsigned int file_name_size=256;
		std::basic_streambuf<elem,traits>* src;
		std::basic_filebuf<elem,traits> tap;
		elem temp[file_name_size];
		elem final[file_name_size];
		elem ch;	//single-byte buffer

	protected:
		typename traits::int_type underflow()
		{
			typename traits::int_type n=src->sbumpc();	//read one char from the source
			if(n!=EOF)
			{
				ch=n;
				setg(&ch,&ch,&ch+1);
				tap.sputc(ch);	//log it
			}
			return n;
		}

	public:
		basic_dtapped_streambuf(const elem* tempfname,const elem* finalfname,
			std::basic_streambuf<elem,traits>* sb):src(sb)
		//source should be std::cin or std::wcin
		{
			std::strcpy(temp,tempfname);
			std::strcpy(final,finalfname);
			tap.open(temp,std::ios::out);
			setg(&ch,&ch+1,&ch+1);	//buffer starts out full
		}

		basic_dtapped_streambuf(std::basic_streambuf<elem,traits>* sb):src(sb)
		//source should be std::cin or std::wcin
		{setg(&ch, &ch+1, &ch+1);	/*buffer starts out full*/}

		~basic_dtapped_streambuf(){tap.close();std::rename(temp,final);}

		void open(const elem* tempfname,const elem* finalfname)
		{
			std::strcpy(temp,tempfname);
			std::strcpy(final,finalfname);
			tap.open(temp,std::ios::out);
		}

		bool is_open(){return tap.is_open();}
		
		void close()
		{
			tap.close();
			std::rename(oldfilename,newfilename);
		}

	};

	template<typename elem,typename traits=std::char_traits<elem> >
	class basic_dtapped_istream:public std::basic_istream<elem,traits>
	{
		basic_dtapped_streambuf<elem,traits> buf;
	public:
		basic_dtapped_istream(const elem* tempfname,const elem* finalfname,std::basic_streambuf<elem,traits>* sb):
		  std::basic_istream<elem,traits>(&buf),buf(tempfname,finalfname,sb){}
		basic_dtapped_istream(std::basic_streambuf<elem,traits>* sb):
		  std::basic_istream<elem,traits>(&buf),buf(sb){}

		bool is_open(){return buf.is_open();}
	};

	typedef basic_dtapped_streambuf<char>	dtapped_streambuf;
	typedef basic_dtapped_streambuf<wchar_t>	dtapped_wstreambuf;
	typedef basic_dtapped_istream<char>	dtapped_istream;
	typedef basic_dtapped_istream<wchar_t>	dtapped_wistream;

#ifndef UNICODE
	typedef dtapped_streambuf	dtapped_tstreambuf;
	typedef dtapped_istream	dtapped_tistream;
#else	//UNICODE
	typedef dtapped_wstreambuf	dtapped_tstreambuf;
	typedef dtapped_wistream	dtapped_tistream;
#endif	//UNICODE

//Automation

#ifdef TAPPED_TEMP_TFILE
#ifndef UNICODE
#define TAPPED_TEMP_FILE TAPPED_TEMP_TFILE
#else	//UNICODE
#define TAPPED_TEMP_WFILE TAPPED_TEMP_TFILE
#endif	//UNICODE
#endif	//TAPPED_TEMP_TFILE

#ifdef TAPPED_FINAL_TFILE
#ifndef UNICODE
#define TAPPED_FINAL_FILE TAPPED_FINAL_TFILE
#else	//UNICODE
#define TAPPED_FINAL_WFILE TAPPED_FINAL_TFILE
#endif	//UNICODE
#endif	//TAPPED_FINAL_TFILE

#if defined(TAPPED_TEMP_FILE) && defined(TAPPED_FINAL_FILE)
	dtapped_istream tp_cin(TAPPED_TEMP_FILE,TAPPED_FINAL_FILE,std::cin.rdbuf());
#endif	//defined(TAPPED_TEMP_FILE) && defined(TAPPED_FINAL_FILE)

#if defined(TAPPED_TEMP_WFILE) && defined(TAPPED_FINAL_WFILE)
	dtapped_wistream tp_wcin(TAPPED_TEMP_WFILE,TAPPED_FINAL_WFILE,std::cin.rdbuf());
#endif	//defined(TAPPED_TEMP_WFILE) && defined(TAPPED_FINAL_WFILE)

#ifndef UNICODE
#define dtp_tcin dtp_cin
#else	//UNICODE
#define dtp_tcin dtp_wcin
#endif	//UNICODE

#ifdef AUTO_DTAP
#define cin eku::dtp_cin
#define wcin	eku::dtp_wcin
#define tcin	eku::dtp_tcin
#endif	//AUTO_DTAP

}

#endif	//_INC_EKU_IO_DTAPPED_ISTREAM