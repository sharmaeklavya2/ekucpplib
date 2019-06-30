#ifndef _INC_EKU_EXPREVAL_FUNCS_SAVCTDOUBLE

#define BINREG(name,priority,func) varop<savct<dbl> >::op2.push_back(oper<savct<dbl>,2>(name,priority,func))
#define UNREG(name,priority,func) varop<savct<dbl> >::op1.push_back(oper<savct<dbl>,1>(name,priority,func))

#define UN_FUNC_PR 9
#define BIN_FUNC_PR 8

BINREG("+",4,eku_cref::add);
BINREG("-",4,eku_cref::sub);
BINREG("*",5,dot);
BINREG("/",5,divide);
UNREG("+",6,eku_cref::plus);
UNREG("-",6,eku_cref::minus);

UNREG("norm",UN_FUNC_PR,vnorm);
UNREG("abs",UN_FUNC_PR,vabs);
BINREG("dot",BIN_FUNC_PR,dot);
BINREG("cross",BIN_FUNC_PR,cross);
BINREG("ang",BIN_FUNC_PR,ang);

#undef BINREG
#undef UNREG

#endif	//_INC_EKU_EXPREVAL_FUNCS_SAVCTDOUBLE