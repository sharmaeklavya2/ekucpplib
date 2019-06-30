#ifndef _INC_EKU_IO_TAPPED_ISTREAM
#define _INC_EKU_IO_TAPPED_ISTREAM

/*
This header file defines a variant of std::istream
All input operations done with this class are tapped
and written to a file.

#define TAPPED_FILE to a filename to make tapped_cin
#define TAPPED_WFILE to a filename to make tapped_wcin
#define TAPPED_TFILE which will check if UNICODE is defined

#define AUTO_TAP and use namespace std to use cin, wcin to tap

*/

#include<string>
#include<fstream>
#include<iostream>
#include<eku\tchar\tiostream.h>

namespace eku
{
	template<typename elem,typename traits=std::char_traits<elem> >
	class basic_tapped_streambuf:public std::basic_streambuf<elem,traits>
	{
		std::basic_streambuf<elem,traits>* src;
		std::basic_filebuf<elem,traits> tap;
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
		basic_tapped_streambuf(const elem* fname,std::basic_streambuf<elem,traits>* sb):src(sb)
		//source should be std::cin or std::wcin
		{
			tap.open(fname,std::ios::out);
			setg(&ch,&ch+1,&ch+1);	//buffer starts out full
		}

		basic_tapped_streambuf(std::basic_streambuf<elem,traits>* sb):src(sb)
		//source should be std::cin or std::wcin
		{setg(&ch, &ch+1, &ch+1);	/*buffer starts out full*/}

		void open(const elem* fname){tap.open(fname,std::ios::out);}
		bool is_open(){return tap.is_open();}
		void close(){tap.close();}

	};

	template<typename elem,typename traits=std::char_traits<elem> >
	class basic_tapped_istream:public std::basic_istream<elem,traits>
	{
		basic_tapped_streambuf<elem,traits> buf;
	public:
		basic_tapped_istream(const elem* fname,std::basic_streambuf<elem,traits>* sb):
		  std::basic_istream<elem,traits>(&buf),buf(fname,sb){}
		basic_tapped_istream(std::basic_streambuf<elem,traits>* sb):
		  std::basic_istream<elem,traits>(&buf),buf(sb){}

		void open(const elem* fname){buf.open(fname);}
		bool is_open(){return buf.is_open();}
		void close(){buf.close();}
	};

	typedef basic_tapped_streambuf<char>	tapped_streambuf;
	typedef basic_tapped_streambuf<wchar_t>	tapped_wstreambuf;
	typedef basic_tapped_istream<char>	tapped_istream;
	typedef basic_tapped_istream<wchar_t>	tapped_wistream;

#ifndef UNICODE
	typedef tapped_streambuf	tapped_tstreambuf;
	typedef tapped_istream	tapped_tistream;
#else	//UNICODE
	typedef tapped_wstreambuf	tapped_tstreambuf;
	typedef tapped_wistream	tapped_tistream;
#endif	//UNICODE

//Automation

#ifdef TAPPED_TFILE
#ifndef UNICODE
#define TAPPED_FILE TAPPED_TFILE
#else	//UNICODE
#define TAPPED_WFILE TAPPED_TFILE
#endif	//UNICODE
#endif	//TAPPED_TFILE

#ifdef TAPPED_FILE
	tapped_istream tp_cin(TAPPED_FILE,std::cin.rdbuf());
#endif	//TAPPED_FILE

#ifdef TAPPED_WFILE
	tapped_wistream tp_wcin(TAPPED_WFILE,std::wcin.rdbuf());
#endif	//TAPPED_WFILE

#ifndef UNICODE
#define tp_tcin tp_cin
#else	//UNICODE
#define tp_tcin tp_wcin
#endif	//UNICODE

#ifdef AUTO_TAP
#define cin eku::tp_cin
#define wcin	eku::tp_wcin
#define tcin	eku::tp_tcin
#endif	//AUTO_TAP

}

#endif	//_INC_EKU_IO_TAPPED_ISTREAM