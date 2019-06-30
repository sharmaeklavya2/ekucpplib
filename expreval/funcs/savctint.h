#ifndef _INC_EKU_EXPREVAL_FUNCS_SAVCTINT

#define BINREG(name,priority,func) varop<savct<itg> >::op2.push_back(oper<savct<itg>,2>(name,priority,func))
#define UNREG(name,priority,func) varop<savct<itg> >::op1.push_back(oper<savct<itg>,1>(name,priority,func))

#define UN_FUNC_PR 9
#define BIN_FUNC_PR 8

BINREG("+",4,eku_cref::add);
BINREG("-",4,eku_cref::sub);
BINREG("*",5,dot);
BINREG("/",5,divide);
UNREG("+",6,eku_cref::plus);
UNREG("-",6,eku_cref::minus);

UNREG("norm",UN_FUNC_PR,vnorm);
BINREG("dot",BIN_FUNC_PR,dot);
BINREG("cross",BIN_FUNC_PR,cross);

#undef BINREG
#undef UNREG

#endif	//_INC_EKU_EXPREVAL_FUNCS_SAVCTINT