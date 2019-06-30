#ifndef _INC_EKU_EXPREVAL_FUNCS_IMAT

#define BINREG(name,priority,func) varop<matrix<itg> >::op2.push_back(oper<matrix<itg>,2>(name,priority,func))
#define UNREG(name,priority,func) varop<matrix<itg> >::op1.push_back(oper<matrix<itg>,1>(name,priority,func))

#define UN_FUNC_PR 9
#define BIN_FUNC_PR 8

BINREG("+",4,eku_cref::add);
BINREG("-",4,eku_cref::sub);
BINREG("*",5,eku_cref::mul);
BINREG("/",5,dvd_mat);
UNREG("+",6,eku_cref::plus);
UNREG("-",6,eku_cref::minus);

UNREG("trn",UN_FUNC_PR,trn);
UNREG("det",UN_FUNC_PR,det);
UNREG("adj",UN_FUNC_PR,adj);
UNREG("inv",UN_FUNC_PR,inv);
UNREG("I",UN_FUNC_PR,idmat);

BINREG("scalar_mat",BIN_FUNC_PR,scalar_mat);
BINREG("minor",BIN_FUNC_PR,subm);
BINREG("remclm",BIN_FUNC_PR,remclm);
BINREG("remrow",BIN_FUNC_PR,remrow);

#undef BINREG
#undef UNREG

#endif	//_INC_EKU_EXPREVAL_FUNCS_IMAT