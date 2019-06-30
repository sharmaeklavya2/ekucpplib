#ifndef _INC_EKU_EXPREVAL_FUNCS_BOOL

#define BINREG(name,priority,func) varop<bool>::op2.push_back(oper<bool,2>(name,priority,func))
#define UNREG(name,priority,func) varop<bool>::op1.push_back(oper<bool,1>(name,priority,func))

BINREG("+",1,eku_bool::or);
BINREG("*",2,eku_bool::and);
UNREG("!",4,eku_bool::not);
BINREG("^",3,eku_bool::xor);

#undef BINREG
#undef UNREG

#endif	//_INC_EKU_EXPREVAL_FUNCS_BOOL