#ifndef _INC_EKU_EXPREVAL_VAROP

#include<eku\expreval\homo\real.h>

template<class dtyp,int noa>	//noa - no. of arguments
class oper{};

template<class dtyp>
class oper<dtyp,1>
{public:
	char name[OP_NAME_SIZE];	//name of operator
	short pr;	//priority
	dtyp (*func)(const dtyp&);
	bool (*dom)(const dtyp&);
	dtyp call(const dtyp& a)const{return (*func)(a);}
	bool is_valid_arg(const dtyp& a)const{return (dom==NULL)?true:(*dom)(a);}
	oper<dtyp,1>(char* a="\0",int prio=0,dtyp f(const dtyp&)=NULL,bool d(const dtyp&)=NULL):
	pr(prio),func(f),dom(d){strcpy(name,a);}
	oper<dtyp,1>(const oper<dtyp,1>& u):pr(u.pr),func(u.func),dom(u.dom){strcpy(name,u.name);}
	bool operator==(const char* a)const{return (strcmp(name,a)==0);}
};

template<class dtyp>
class oper<dtyp,2>
{public:
	char name[OP_NAME_SIZE];	//name of operator
	short pr;	//priority
	dtyp (*func)(const dtyp&,const dtyp&);	//function
	bool (*dom)(const dtyp&,const dtyp&);	//function
	dtyp call(const dtyp& a,const dtyp& b)const{return (*func)(a,b);}
	bool is_valid_arg(const dtyp& a,const dtyp& b)const{return (dom==NULL)?true:(*dom)(a,b);}
	oper<dtyp,2>(char* a="\0",int prio=0,dtyp f(const dtyp&,const dtyp&)=NULL,bool d(const dtyp&,const dtyp&)=NULL):
	pr(prio),func(f),dom(d){strcpy(name,a);}
	oper<dtyp,2>(const oper<dtyp,2>& b):pr(b.pr),func(b.func),dom(b.dom){strcpy(name,b.name);}
	bool operator==(const char* a)const{return (strcmp(name,a)==0);}
};

template<class dtyp>
class oper<dtyp,3>
{public:
	char name[OP_NAME_SIZE];	//name of operator
	short pr;	//priority
	dtyp (*func)(const dtyp&,const dtyp&,const dtyp&);	//function
	bool (*dom)(const dtyp&,const dtyp&,const dtyp&);	//function
	dtyp call(const dtyp& a,const dtyp& b,const dtyp& c)const{return (*func)(a,b,c);}
	bool is_valid_arg(const dtyp& a,const dtyp& b,const dtyp& c)const{return (dom==NULL)?true:(*dom)(a,b,c);}
	oper<dtyp,3>(char* a="\0",int prio=0,dtyp f(const dtyp&,const dtyp&,const dtyp&)=NULL,bool d(const dtyp&,const dtyp&,const dtyp&)=NULL):
	pr(prio),func(f),dom(d){strcpy(name,a);}
	oper<dtyp,3>(const oper<dtyp,3>& b):pr(b.pr),func(b.func),dom(b.dom){strcpy(name,b.name);}
	bool operator==(const char* a)const{return (strcmp(name,a)==0);}
};

template<class dtyp>
class variable
{public:
	char name[OP_NAME_SIZE];
	dtyp val;
	variable():val(0){}
	variable(char* a,dtyp value=0):val(value){strcpy(name,a);}
	variable(const variable& v):val(v.val){strcpy(name,v.name);}
	bool operator==(variable& v){return (strcmp(name,v.name)==0 && val==v.val);}
	bool operator==(const char* str){return (strcmp(name,str)==0);}
	bool operator!=(const char* str){return (strcmp(name,str)!=0);}
};

class cstr_wrap
{public:
	char a[OP_NAME_SIZE];
	char& operator[](unsigned n){return a[n];}
	cstr_wrap(char* str){strcpy(a,str);}
	cstr_wrap(std::string& str){strcpy(a,str.c_str());}
	cstr_wrap(const cstr_wrap& c){strcpy(a,c.a);}
	void operator=(char* str){strcpy(a,str);}
	void operator=(std::string& str){strcpy(a,str.c_str());}
	bool operator==(char* str){return (strcmp(a,str)==0);}
	bool operator==(std::string& str){return str==a;}
	bool operator!=(char* str){return (strcmp(a,str)!=0);}
	bool operator!=(std::string& str){return !(str==a);}
};

#endif	//_INC_EKU_EXPREVAL_VAROP