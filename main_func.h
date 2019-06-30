#ifndef _INC_EKU_MAIN_FUNC
#define _INC_EKU_MAIN_FUNC

#include<iostream>
#include<exception>
#include<eku\time.h>
#define NO_CONT_PROMPT
#include<eku\io\_io.h>

namespace eku
{
//0-parameters--------------------------------------------------------------------
	template<class typ>
	void main_func0(typ f(),const char* res="Result",std::ostream& os=std::cout)
	{
		typ r;
		do
		{
			try
			{
				start();
				r=(*f)();
				stop();
				os<<res<<" :\t"<<r<<std::endl;
				os<<"Time taken :\t"<<showms()<<" ms"<<std::endl;
			}
			catch(std::exception& e){os<<e.what()<<std::endl;}
			catch(...){os<<"Error: An exception was thrown"<<std::endl;}
		}
		while(_cont());
	}

//1-parameter,-pass-by-value------------------------------------------------------
	template<class typr,class typp>
	void main_func1(typr f(typp),const char* name="Param",const char* res="Result",
					std::ostream& os=std::cout,std::istream& is=std::cin)
	{
		typp p;
		do
		{
			try
			{
				os<<"Enter "<<name<<" :\t";
				is>>p;
				typr r;
				start();
				r=(*f)(p);
				stop();
				os<<res<<" :\t"<<r<<std::endl;
				os<<"Time taken :\t"<<showms()<<" ms"<<std::endl;
			}
			catch(std::exception& e){os<<e.what()<<std::endl;}
			catch(...){os<<"Error: An exception was thrown"<<std::endl;}
		}
		while(_cont());
	}

//1-parameter,-pass-by-reference--------------------------------------------------
	template<class typr,class typp>
	void main_func1(typr f(const typp&),const char* name="Param",const char* res="Result",
					std::ostream& os=std::cout,std::istream& is=std::cin)
	{
		typp p;
		do
		{
			try
			{
				os<<"Enter "<<name<<" :\t";
				is>>p;
				typr r;
				start();
				r=(*f)(p);
				stop();
				os<<res<<" :\t"<<r<<std::endl;
				os<<"Time taken :\t"<<showms()<<" ms"<<std::endl;
			}
			catch(std::exception& e){os<<e.what()<<std::endl;}
			catch(...){os<<"Error: An exception was thrown"<<std::endl;}
		}
		while(_cont());
	}

//2-parameters,-pass-by-value-----------------------------------------------------
	template<class typr,class typp1,class typp2>
	void main_func2(typr f(typp1,typp2),const char* name1="Param1",const char* name2="Param2",
					const char* res="Result",std::ostream& os=std::cout,std::istream& is=std::cin)
	{
		typp1 p1;
		typp2 p2;
		do
		{
			try
			{
				os<<"Enter "<<name1<<" :\t";
				is>>p1;
				os<<"Enter "<<name2<<" :\t";
				is>>p2;
				typr r;
				start();
				r=(*f)(p1,p2);
				stop();
				os<<res<<" :\t"<<r<<std::endl;
				os<<"Time taken :\t"<<showms()<<" ms"<<std::endl;
			}
			catch(std::exception& e){os<<e.what()<<std::endl;}
			catch(...){os<<"Error: An exception was thrown"<<std::endl;}
		}
		while(_cont());
	}

//2-parameters,-pass-by-reference-------------------------------------------------
	template<class typr,class typp1,class typp2>
	void main_func2(typr f(const typp1&,const typp2&),const char* name1="Param1",const char* name2="Param2",
					const char* res="Result",std::ostream& os=std::cout,std::istream& is=std::cin)
	{
		typp1 p1;
		typp2 p2;
		do
		{
			try
			{
				os<<"Enter "<<name1<<" :\t";
				is>>p1;
				os<<"Enter "<<name2<<" :\t";
				is>>p2;
				typr r;
				start();
				r=(*f)(p1,p2);
				stop();
				os<<res<<" :\t"<<r<<std::endl;
				os<<"Time taken :\t"<<showms()<<" ms"<<std::endl;
			}
			catch(std::exception& e){os<<e.what()<<std::endl;}
			catch(...){os<<"Error: An exception was thrown"<<std::endl;}
		}
		while(_cont());
	}

//0-parameters,-pointer-to-member-------------------------------------------------
	template<class cls>
	void cmain_func0(void (cls::*f)(),const char* objname="object",const char* res="New object",
						  std::ostream& os=std::cout,std::istream& is=std::cin)
	{
		cls myobj;
		do
		{
			try
			{
				os<<"Enter "<<objname<<" :\t";
				is>>myobj;
				start();
				(myobj.*f)();
				stop();
				os<<res<<" :\t"<<myobj<<std::endl;
				os<<"Time taken :\t"<<showms()<<" ms"<<std::endl;
			}
			catch(std::exception& e){os<<e.what()<<std::endl;}
			catch(...){os<<"Error: An exception was thrown"<<std::endl;}
		}
		while(_cont());
	}

//0-parameters,-pointer-to-const-member-------------------------------------------
	template<class rtyp,class cls>
	void cmain_func0(rtyp (cls::*f)()const,const char* objname="object",const char* res="Result",
						  std::ostream& os=std::cout,std::istream& is=std::cin)
	{
		cls myobj;
		rtyp r;
		do
		{
			try
			{
				os<<"Enter "<<objname<<" :\t";
				is>>myobj;
				start();
				r=(myobj.*f)();
				stop();
				os<<res<<" :\t"<<r<<std::endl;
				os<<"Time taken :\t"<<showms()<<" ms"<<std::endl;
			}
			catch(std::exception& e){os<<e.what()<<std::endl;}
			catch(...){os<<"Error: An exception was thrown"<<std::endl;}
		}
		while(_cont());
	}

//1-parameter,-pointer-to-member--------------------------------------------------
	template<class typp,class cls>
	void cmain_func1(void (cls::*f)(typp),const char* objname="object",const char* param="param",
		const char* res="New object",std::ostream& os=std::cout,std::istream& is=std::cin)
	{
		cls myobj;
		typp p;
		do
		{
			try
			{
				os<<"Enter "<<objname<<" :\t";
				is>>myobj;
				os<<"Enter "<<param<<" :\t";
				is>>p;
				start();
				(myobj.*f)(p);
				stop();
				os<<res<<" :\t"<<myobj<<std::endl;
				os<<"Time taken :\t"<<showms()<<" ms"<<std::endl;
			}
			catch(std::exception& e){os<<e.what()<<std::endl;}
			catch(...){os<<"Error: An exception was thrown"<<std::endl;}
		}
		while(_cont());
	}

//1-parameter,-pointer-to-const-member--------------------------------------------
	template<class rtyp,class typp,class cls>
	void cmain_func1(rtyp (cls::*f)(typp)const,const char* objname="object",const char* param="param",
		const char* res="Result",std::ostream& os=std::cout,std::istream& is=std::cin)
	{
		cls myobj;
		rtyp r;
		typp p;
		do
		{
			try
			{
				os<<"Enter "<<objname<<" :\t";
				is>>myobj;
				os<<"Enter "<<param<<" :\t";
				is>>p;
				start();
				r=(myobj.*f)(p);
				stop();
				os<<res<<" :\t"<<r<<std::endl;
				os<<"Time taken :\t"<<showms()<<" ms"<<std::endl;
			}
			catch(std::exception& e){os<<e.what()<<std::endl;}
			catch(...){os<<"Error: An exception was thrown"<<std::endl;}
		}
		while(_cont());
	}

//1-parameter,-pointer-to-member,-pass-by-reference-------------------------------
	template<class typp,class cls>
	void cmain_func1(void (cls::*f)(const typp&),const char* objname="object",const char* param="param",
		const char* res="New object",std::ostream& os=std::cout,std::istream& is=std::cin)
	{
		cls myobj;
		typp p;
		do
		{
			try
			{
				os<<"Enter "<<objname<<" :\t";
				is>>myobj;
				os<<"Enter "<<param<<" :\t";
				is>>p;
				start();
				(myobj.*f)(p);
				stop();
				os<<res<<" :\t"<<myobj<<std::endl;
				os<<"Time taken :\t"<<showms()<<" ms"<<std::endl;
			}
			catch(std::exception& e){os<<e.what()<<std::endl;}
			catch(...){os<<"Error: An exception was thrown"<<std::endl;}
		}
		while(_cont());
	}

//1-parameter,-pointer-to-const-member,-pass-by-reference-------------------------
	template<class rtyp,class typp,class cls>
	void cmain_func1(rtyp (cls::*f)(const typp&)const,const char* objname="object",const char* param="param",
		const char* res="Result",std::ostream& os=std::cout,std::istream& is=std::cin)
	{
		cls myobj;
		rtyp r;
		typp p;
		do
		{
			try
			{
				os<<"Enter "<<objname<<" :\t";
				is>>myobj;
				os<<"Enter "<<param<<" :\t";
				is>>p;
				start();
				r=(myobj.*f)(p);
				stop();
				os<<res<<" :\t"<<r<<std::endl;
				os<<"Time taken :\t"<<showms()<<" ms"<<std::endl;
			}
			catch(std::exception& e){os<<e.what()<<std::endl;}
			catch(...){os<<"Error: An exception was thrown"<<std::endl;}
		}
		while(_cont());
	}

}

#endif	//_INC_EKU_MAIN_FUNC