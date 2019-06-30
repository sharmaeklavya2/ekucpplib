#ifndef _INC_EKU_EXPREVAL_FUNCS_DOUBLE

#define REG3(name,priority,func) varop<dbl>::op3.push_back(oper<dbl,3>(name,priority,func))
#define REG2(name,priority,func) varop<dbl>::op2.push_back(oper<dbl,2>(name,priority,func))
#define REG1(name,priority,func) varop<dbl>::op1.push_back(oper<dbl,1>(name,priority,func))

#define REG3_S(name,priority,func,dcheck) varop<dbl>::op3.push_back(oper<dbl,3>(name,priority,func,dcheck))
#define REG2_S(name,priority,func,dcheck) varop<dbl>::op2.push_back(oper<dbl,2>(name,priority,func,dcheck))
#define REG1_S(name,priority,func,dcheck) varop<dbl>::op1.push_back(oper<dbl,1>(name,priority,func,dcheck))

#define UN_FUNC_PR 9
#define BIN_FUNC_PR 8

REG2("+",4,eku::add);
REG2("-",4,eku::sub);
REG2("*",5,eku::mul);
REG2_S("/",5,eku::dvd,eku::dvd_ckeck);
REG2("%",5,fmod);
REG1("+",6,eku::plus);
REG1("-",6,eku::minus);

if(!math_mode<dbl>::bitwise)REG2_S("^",6,pow,eku::pow_ckeck);
REG2_S("pow",BIN_FUNC_PR,pow,eku::pow_ckeck);
REG1("!",7,pi_func);
REG1("sqrt",UN_FUNC_PR,sqrt);
REG1("abs",UN_FUNC_PR,fabs);
REG1("ln",UN_FUNC_PR,log);
REG1("log",UN_FUNC_PR,log10);
REG1("exp",UN_FUNC_PR,exp);
	
if(math_mode<dbl>::trig)
{
	REG1("sin",UN_FUNC_PR,sin);
	REG1("cos",UN_FUNC_PR,cos);
	REG1("tan",UN_FUNC_PR,tan);
	REG1("cosec",UN_FUNC_PR,csc);
	REG1("csc",UN_FUNC_PR,csc);
	REG1("sec",UN_FUNC_PR,sec);
	REG1("cot",UN_FUNC_PR,cot);
}

if(math_mode<dbl>::itrig)
{
	REG1("asin",UN_FUNC_PR,asin);
	REG1("acos",UN_FUNC_PR,acos);
	REG1("atan",UN_FUNC_PR,atan);
	REG1("acosec",UN_FUNC_PR,acsc);
	REG1("acsc",UN_FUNC_PR,acsc);
	REG1("asec",UN_FUNC_PR,asec);
	REG1("acot",UN_FUNC_PR,acot);
}

if(math_mode<dbl>::dtrig)
{
	REG1("sind",UN_FUNC_PR,sind);
	REG1("cosd",UN_FUNC_PR,cosd);
	REG1("tand",UN_FUNC_PR,tand);
	REG1("cosecd",UN_FUNC_PR,cscd);
	REG1("cscd",UN_FUNC_PR,cscd);
	REG1("secd",UN_FUNC_PR,secd);
	REG1("cotd",UN_FUNC_PR,cotd);
}

if(math_mode<dbl>::ditrig)
{
	REG1("asind",UN_FUNC_PR,asind);
	REG1("acosd",UN_FUNC_PR,acosd);
	REG1("atand",UN_FUNC_PR,atand);
	REG1("acosecd",UN_FUNC_PR,acscd);
	REG1("acscd",UN_FUNC_PR,acscd);
	REG1("asecd",UN_FUNC_PR,asecd);
	REG1("acotd",UN_FUNC_PR,acotd);
}

if(math_mode<dbl>::htrig)
{
	REG1("sinh",UN_FUNC_PR,sinh);
	REG1("cosh",UN_FUNC_PR,cosh);
	REG1("tanh",UN_FUNC_PR,tanh);
	REG1("cosech",UN_FUNC_PR,csch);
	REG1("csch",UN_FUNC_PR,csch);
	REG1("sech",UN_FUNC_PR,sech);
	REG1("coth",UN_FUNC_PR,coth);
}

if(math_mode<dbl>::ihtrig)
{
	REG1("asinh",UN_FUNC_PR,asinh);
	REG1("acosh",UN_FUNC_PR,acosh);
	REG1("atanh",UN_FUNC_PR,atanh);
	REG1("acosech",UN_FUNC_PR,acsch);
	REG1("acsch",UN_FUNC_PR,acsch);
	REG1("asech",UN_FUNC_PR,asech);
	REG1("acoth",UN_FUNC_PR,acoth);
}

if(math_mode<dbl>::factor)
{
	REG2("c",BIN_FUNC_PR,combi);
	REG2("p",BIN_FUNC_PR,permu);
	REG2("hcf",BIN_FUNC_PR,hcf);
	REG2("lcm",BIN_FUNC_PR,lcm);
	REG3("hcf",BIN_FUNC_PR,hcf3);
	REG3("lcm",BIN_FUNC_PR,lcm3);
	REG1("prime",UN_FUNC_PR,prime);
}

if(math_mode<dbl>::bitwise)
{
	REG2("|",1,eku::band);
	REG2("^",2,eku::bor);
	REG2("&",3,eku::bxor);
}

if(math_mode<dbl>::piece_def)
{
	REG1("nearint",UN_FUNC_PR,nearint);
	REG1("sgn",UN_FUNC_PR,sgn<double>);
	REG1("floor",UN_FUNC_PR,floor);
	REG1("ceil",UN_FUNC_PR,ceil);
}

#undef REG3
#undef REG2
#undef REG1

#undef REG3_S
#undef REG2_S
#undef REG1_S

#endif	//_INC_EKU_EXPREVAL_FUNCS_DOUBLE