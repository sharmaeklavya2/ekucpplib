#ifndef _INC_EKU_EXPREVAL_BYVALUEOP

template<>
class oper<dtyp,1>
{public:
	char name[OP_NAME_SIZE];	//name of operator
	short pr;	//priority
	dtyp (*func)(dtyp);
	bool (*dom)(dtyp);
	dtyp call(dtyp a)const{return (*func)(a);}
	bool is_valid_arg(dtyp a)const{return (dom==NULL)?true:(*dom)(a);}
	oper<dtyp,1>(char* a="\0",int prio=0,dtyp f(dtyp)=NULL,bool d(dtyp)=NULL):
	pr(prio),func(f),dom(d){strcpy(name,a);}
	oper<dtyp,1>(const oper<dtyp,1>& u):pr(u.pr),func(u.func),dom(u.dom){strcpy(name,u.name);}
	bool operator==(const char* a)const{return (strcmp(name,a)==0);}
};

template<>
class oper<dtyp,2>
{public:
	char name[OP_NAME_SIZE];	//name of operator
	short pr;	//priority
	dtyp (*func)(dtyp,dtyp);	//function
	bool (*dom)(dtyp,dtyp);	//function
	dtyp call(dtyp a,dtyp b)const{return (*func)(a,b);}
	bool is_valid_arg(dtyp a,dtyp b)const
	{
		return (dom==NULL)?true:(*dom)(a,b);
	}
	oper<dtyp,2>(char* a="\0",int prio=0,dtyp f(dtyp,dtyp)=NULL,bool d(dtyp,dtyp)=NULL):
	pr(prio),func(f),dom(d)
	{
		strcpy(name,a);
	}
	oper<dtyp,2>(const oper<dtyp,2>& b):pr(b.pr),func(b.func),dom(b.dom){strcpy(name,b.name);}
	bool operator==(const char* a)const{return (strcmp(name,a)==0);}
};

template<>
class oper<dtyp,3>
{public:
	char name[OP_NAME_SIZE];	//name of operator
	short pr;	//priority
	dtyp (*func)(dtyp,dtyp,dtyp);	//function
	bool (*dom)(dtyp,dtyp,dtyp);	//function
	dtyp call(dtyp a,dtyp b,dtyp c)const{return (*func)(a,b,c);}
	bool is_valid_arg(dtyp a,dtyp b,dtyp c)const{return (dom==NULL)?true:(*dom)(a,b,c);}
	oper<dtyp,3>(char* a="\0",int prio=0,dtyp f(dtyp,dtyp,dtyp)=NULL,bool d(dtyp,dtyp,dtyp)=NULL):
	pr(prio),func(f),dom(d){strcpy(name,a);}
	oper<dtyp,3>(const oper<dtyp,3>& b):pr(b.pr),func(b.func),dom(b.dom){strcpy(name,b.name);}
	bool operator==(const char* a)const{return (strcmp(name,a)==0);}
};

#undef dtyp

#endif	//_INC_EKU_EXPREVAL_BYVALUEOP