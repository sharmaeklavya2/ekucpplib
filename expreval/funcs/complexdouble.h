#ifndef _INC_EKU_EXPREVAL_FUNCS_COMPLEXDOUBLE

#define BINREG(name,priority,func) varop<std::complex<dbl> >::op2.push_back(oper<std::complex<dbl>,2>(name,priority,func))
#define UNREG(name,priority,func) varop<std::complex<dbl> >::op1.push_back(oper<std::complex<dbl>,1>(name,priority,func))
#define BINREG_S(name,priority,func,dcheck) varop<std::complex<dbl> >::op2.push_back(oper<std::complex<dbl>,2>(name,priority,func,dcheck))
#define UNREG_S(name,priority,func,dcheck) varop<std::complex<dbl> >::op1.push_back(oper<std::complex<dbl>,1>(name,priority,func,dcheck))

#define UN_FUNC_PR 9
#define BIN_FUNC_PR 8

BINREG("+",4,eku_cref::add);
BINREG("-",4,eku_cref::sub);
BINREG("*",5,eku_cref::mul);
BINREG("/",5,eku_cref::dvd);
UNREG("+",6,eku_cref::plus);
UNREG("-",6,eku_cref::minus);

UNREG("conj",UN_FUNC_PR,std::conj);
UNREG("abs",UN_FUNC_PR,cabs);
UNREG("norm",UN_FUNC_PR,cnorm);
UNREG("arg",UN_FUNC_PR,carg);
UNREG("real",UN_FUNC_PR,creal);
UNREG("imag",UN_FUNC_PR,cimag);

BINREG("^",6,std::pow);
BINREG("pow",BIN_FUNC_PR,std::pow);
UNREG("sqrt",UN_FUNC_PR,std::sqrt);
UNREG("ln",UN_FUNC_PR,std::log);
UNREG("log",UN_FUNC_PR,std::log10);
UNREG("exp",UN_FUNC_PR,std::exp);
	
if(math_mode<std::complex<dbl> >::trig)
{
	UNREG("sin",UN_FUNC_PR,std::sin);
	UNREG("cos",UN_FUNC_PR,std::cos);
	UNREG("tan",UN_FUNC_PR,std::tan);
	UNREG("cosec",UN_FUNC_PR,ccsc);
	UNREG("csc",UN_FUNC_PR,ccsc);
	UNREG("sec",UN_FUNC_PR,csec);
	UNREG("cot",UN_FUNC_PR,ccot);
}

if(math_mode<std::complex<dbl> >::htrig)
{
	UNREG("sinh",UN_FUNC_PR,std::sinh);
	UNREG("cosh",UN_FUNC_PR,std::cosh);
	UNREG("tanh",UN_FUNC_PR,std::tanh);
	UNREG("cosech",UN_FUNC_PR,ccsch);
	UNREG("csch",UN_FUNC_PR,ccsch);
	UNREG("sech",UN_FUNC_PR,csech);
	UNREG("coth",UN_FUNC_PR,ccoth);
}

/*if(math_mode<std::complex<dbl> >::ihtrig)
{
	UNREG("asinh",UN_FUNC_PR,casinh);
	UNREG("acosh",UN_FUNC_PR,cacosh);
	UNREG("atanh",UN_FUNC_PR,catanh);
	UNREG("acosech",UN_FUNC_PR,cacsch);
	UNREG("acsch",UN_FUNC_PR,cacsch);
	UNREG("asech",UN_FUNC_PR,casech);
	UNREG("acoth",UN_FUNC_PR,cacoth);
}*/

#undef BINREG
#undef UNREG

#endif	//_INC_EKU_EXPREVAL_FUNCS_COMPLEXDOUBLE