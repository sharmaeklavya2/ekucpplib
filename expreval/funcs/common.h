#ifndef _INC_EKU_EXPREVAL_FUNCS_COMMON
//Contains default functions for data types

#define BINREG(name,priority,func) varop<dtyp>::op2.push_back(oper<dtyp,2>(name,priority,func))
#define UNREG(name,priority,func) varop<dtyp>::op1.push_back(oper<dtyp,1>(name,priority,func))

BINREG("+",4,eku::add);
BINREG("-",4,eku::sub);
BINREG("*",5,eku::mul);
UNREG("+",6,eku::plus);
UNREG("-",6,eku::minus);

#undef BINREG
#undef UNREG

#endif	//_INC_EKU_EXPREVAL_FUNCS_COMMON