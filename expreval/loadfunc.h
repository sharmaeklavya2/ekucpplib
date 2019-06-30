#ifndef _INC_EKU_EXPREVAL_LOADFUNC

#include<eku\expreval\homo\real.h>
#include<eku\expreval\homo\bool.h>

#ifdef _COMPLEX_
#include<eku\expreval\homo\complex.h>
#endif	//_COMPLEX_

#ifdef _INC_EKU_CONTAINER_SAVECTOR
#include<eku\expreval\homo\savector.h>
#endif	//_INC_EKU_CONTAINER_SAVECTOR

#ifdef _INC_EKU_MATRIX_MATRIX
#include<eku\expreval\homo\matrix.h>
#endif	//_INC_EKU_MATRIX_MATRIX

template<class dtyp>
void load_func()
{
	varop<dtyp>::op1.clear();varop<dtyp>::op2.clear();varop<dtyp>::op3.clear();
#include<eku\expreval\funcs\common.h>
}

template<>
void load_func<dbl>()
{
	varop<dbl>::op1.clear();varop<dbl>::op2.clear();varop<dbl>::op3.clear();
#include<eku\expreval\funcs\double.h>
}

template<>
void load_func<itg>()
{
	varop<itg>::op1.clear();varop<itg>::op2.clear();varop<itg>::op3.clear();
#include<eku\expreval\funcs\int.h>
}

#ifdef _COMPLEX_
template<>
void load_func<std::complex<itg> >()
{
	varop<std::complex<itg> >::op1.clear();
	varop<std::complex<itg> >::op2.clear();
	varop<std::complex<itg> >::op3.clear();
#include<eku\expreval\funcs\complexint.h>
}

template<>
void load_func<std::complex<dbl> >()
{
	varop<std::complex<dbl> >::op1.clear();
	varop<std::complex<dbl> >::op2.clear();
	varop<std::complex<dbl> >::op3.clear();
#include<eku\expreval\funcs\complexdouble.h>
}

#endif	//_COMPLEX_

template<>
void load_func<bool>()
{
	varop<bool>::op1.clear();varop<bool>::op2.clear();varop<bool>::op3.clear();
#include<eku\expreval\funcs\bool.h>
}

#ifdef _INC_EKU_CONTAINER_SAVECTOR

template<>
void load_func<savct<itg> >()
{
	varop<savct<itg> >::op1.clear();
	varop<savct<itg> >::op2.clear();
	varop<savct<itg> >::op3.clear();
#include<eku\expreval\funcs\savctint.h>
}

template<>
void load_func<savct<dbl> >()
{
	varop<savct<dbl> >::op1.clear();
	varop<savct<dbl> >::op2.clear();
	varop<savct<dbl> >::op3.clear();
#include<eku\expreval\funcs\savctdouble.h>
}

#endif	//_INC_EKU_CONTAINER_SAVECTOR

#ifdef _INC_EKU_MATRIX_MATRIX

template<>
void load_func<matrix<itg> >()
{
	varop<matrix<itg> >::op1.clear();
	varop<matrix<itg> >::op2.clear();
	varop<matrix<itg> >::op3.clear();
#include<eku\expreval\funcs\imat.h>
}

template<>
void load_func<matrix<dbl> >()
{
	varop<matrix<dbl> >::op1.clear();
	varop<matrix<dbl> >::op2.clear();
	varop<matrix<dbl> >::op3.clear();
#include<eku\expreval\funcs\dmat.h>
}

#endif	//_INC_EKU_MATRIX_MATRIX

#endif	//_INC_EKU_EXPREVAL_LOADFUNC