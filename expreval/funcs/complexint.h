#ifndef _INC_EKU_EXPREVAL_FUNCS_COMPLEXINT

#define BINREG(name,priority,func) varop<std::complex<itg> >::op2.push_back(oper<std::complex<itg>,2>(name,priority,func))
#define UNREG(name,priority,func) varop<std::complex<itg> >::op1.push_back(oper<std::complex<itg>,1>(name,priority,func))

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

#undef BINREG
#undef UNREG

#endif	//_INC_EKU_EXPREVAL_FUNCS_COMPLEXINT