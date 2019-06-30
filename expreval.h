#ifndef _INC_EKU_EXPREVAL
#define _INC_EKU_EXPREVAL
//Header File containing functions to interpret mathematical expressions and evaluate them

#include<iostream>
#include<string>
#include<vector>
#include<ctype.h>
#include<exception>
#include<eku\miscdef.h>
#include<eku\math.h>
#include<stdlib.h>

typedef double dbl;
typedef int itg;
#define OP_NAME_SIZE 20
#define f2sc ':'	//format 2 seperating character

char unknown_func_name[OP_NAME_SIZE];

class eku_expreval_unknown_func:public std::exception
{public:
	virtual const char* what()const throw()
	{return "Unknown function";}
}unknown_func;

class eku_expreval_bad_arg:public std::exception
{public:
	virtual const char* what()const throw()
	{return "Argument out of domain";}
}bad_arg;

namespace expreval_mode
{
	bool recursive_eval=true;
	bool loc_var=true;
	bool ask_var=true;
}

#include<eku\expreval\math_mode.h>

template<class dtyp>	//stands for 'double type': variable type used by program
inline dtyp evaluate(std::string& a);	//prototype defined to enable recursivity

//=======================================================================================

#include<eku\expreval\varop.h>
#include<eku\expreval\varop_spec.h>

template<class dtyp>
class varop
{public:
static std::vector<oper<dtyp,3> >	op3;
static std::vector<oper<dtyp,2> >	op2;
static std::vector<oper<dtyp,1> >	op1;
static std::vector<variable<dtyp> >	gvar;
};

template<class dtyp>
std::vector<oper<dtyp,3> >	varop<dtyp>::op3;
template<class dtyp>
std::vector<oper<dtyp,2> >	varop<dtyp>::op2;
template<class dtyp>
std::vector<oper<dtyp,1> >	varop<dtyp>::op1;
template<class dtyp>
std::vector<variable<dtyp> >	varop<dtyp>::gvar;

char delim[]="+-*()/%&|^,!;=";	//(delimiters) seperators in an expression
char bindelimop[]="+-*/%&|^";	//binary delimiting operators
char undelimop[]="+-!";		//unary delimiting operators
char illchar[]="\"#$\':<>?@\\`~";	//illegal characters

//=======================================================================================

#include<eku\expreval\loadfunc.h>
#include<eku\expreval\loadvar.h>
#include<eku\expreval\conv.h>
#include<eku\expreval\expreval.h>
#include<eku\expreval\apply.h>

#endif	//_INC_EKU_EXPREVAL