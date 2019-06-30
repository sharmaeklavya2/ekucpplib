#ifndef _INC_EKU_EXPREVAL_REFOP

template<>
class oper<dtyp,2>
{public:
	char name[OP_NAME_SIZE];	//name of operator
	short pr;	//priority
	dtyp (*func)(dtyp&,dtyp&);	//function
	dtyp call(dtyp& a,dtyp& b){return (*func)(a,b);}
	oper<dtyp,2>(){}
	oper<dtyp,2>(char* a,int prio,dtyp f(dtyp&,dtyp&)):pr(prio),func(f){strcpy(name,a);}
	oper<dtyp,2>(const oper<dtyp,2>& b):pr(b.pr),func(b.func){strcpy(name,b.name);}
	bool operator==(const char* a){return (strcmp(name,a)==0);}
};

template<>
class oper<dtyp,1>
{public:
	char name[OP_NAME_SIZE];	//name of operator
	short pr;	//priority
	dtyp (*func)(dtyp&);
	dtyp call(dtyp& a){return (*func)(a);}
	oper<dtyp,1>(){}
	oper<dtyp,1>(char* a,int prio,dtyp f(dtyp&)):pr(prio),func(f){strcpy(name,a);}
	oper<dtyp,1>(const oper<dtyp,1>& u):pr(u.pr),func(u.func){strcpy(name,u.name);}
	bool operator==(const char* a){return (strcmp(name,a)==0);}
};

template<>
class oper<dtyp,3>
{public:
	char name[OP_NAME_SIZE];	//name of operator
	short pr;	//priority
	dtyp (*func)(dtyp&,dtyp&,dtyp&);	//function
	dtyp call(dtyp& a,dtyp& b,dtyp& c){return (*func)(a,b,c);}
	oper<dtyp,3>(){}
	oper<dtyp,3>(char* a,int prio,dtyp f(dtyp&,dtyp&,dtyp&)):pr(prio),func(f){strcpy(name,a);}
	oper<dtyp,3>(const oper<dtyp,3>& b):pr(b.pr),func(b.func){strcpy(name,b.name);}
	bool operator==(const char* a){return (strcmp(name,a)==0);}
};

#undef dtyp

#endif	//_INC_EKU_EXPREVAL_REFOP