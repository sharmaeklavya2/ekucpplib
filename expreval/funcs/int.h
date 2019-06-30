#ifndef _INC_EKU_EXPREVAL_FUNCS_INT

#define BINREG(name,priority,func) varop<itg>::op2.push_back(oper<itg,2>(name,priority,func))
#define UNREG(name,priority,func) varop<itg>::op1.push_back(oper<itg,1>(name,priority,func))

#define UN_FUNC_PR 9
#define BIN_FUNC_PR 8
BINREG("+",4,eku::add);
BINREG("-",4,eku::sub);
BINREG("*",5,eku::mul);
BINREG("/",5,eku::dvd);
BINREG("%",5,eku::mod);
UNREG("+",6,eku::plus);
UNREG("-",6,eku::minus);

//if(!math_mode<itg>::bitwise)BINREG("^",6,pow);
//BINREG("pow",BIN_FUNC_PR,pow);
UNREG("!",7,fact);
UNREG("abs",UN_FUNC_PR,abs);
BINREG("pow",BIN_FUNC_PR,ipow<int>);

if(math_mode<itg>::factor)
{
	BINREG("c",BIN_FUNC_PR,combi);
	BINREG("p",BIN_FUNC_PR,permu);
	BINREG("hcf",BIN_FUNC_PR,hcf);
	BINREG("lcm",BIN_FUNC_PR,lcm);
	UNREG("prime",UN_FUNC_PR,prime);
}

if(math_mode<itg>::bitwise)
{
	BINREG("|",1,eku::band);
	BINREG("^",2,eku::bor);
	BINREG("&",3,eku::bxor);
}

if(math_mode<itg>::piece_def){}

#undef BINREG
#undef UNREG

#endif	//_INC_EKU_EXPREVAL_FUNCS_INT