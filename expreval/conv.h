#ifndef _INC_EKU_EXPREVAL_CONV
#define _INC_EKU_EXPREVAL_CONV
//Functions to convert text to evaluation type for use in 'dtyp eval<dtyp>(std::string&)'

#include<boost\lexical_cast.hpp>

template<class totyp>
inline totyp expreval_conv(char* from)
{return boost::lexical_cast<totyp>(from);}

#ifdef _COMPLEX_

template<>
inline std::complex<dbl> expreval_conv<std::complex<dbl> >(char* from)
{return std::complex<dbl>(boost::lexical_cast<dbl>(from),0);}

template<>
inline std::complex<itg> expreval_conv<std::complex<itg> >(char* from)
{return std::complex<itg>(boost::lexical_cast<itg>(from),0);}

#endif //_COMPLEX_

#ifdef _INC_EKU_CONTAINER_SAVECTOR

template<>
inline savct<dbl> expreval_conv<savct<dbl> >(char* from)
{return savct<dbl>(boost::lexical_cast<dbl>(from));}

template<>
inline savct<itg> expreval_conv<savct<itg> >(char* from)
{return savct<itg>(boost::lexical_cast<itg>(from));}

#endif	//_INC_EKU_CONTAINER_SAVECTOR

template<>
inline bool expreval_conv<bool>(char* a)
{return (a[0]=='t' || a[0]=='1' || a[0]=='y');}

#ifdef _INC_EKU_MATRIX_MATRIX

template<>
inline matrix<dbl> expreval_conv<matrix<dbl> >(char* from)
{return matrix<dbl>(boost::lexical_cast<dbl>(from));}

template<>
inline matrix<itg> expreval_conv<matrix<itg> >(char* from)
{return matrix<itg>(boost::lexical_cast<itg>(from));}

#endif	//_INC_EKU_MATRIX_MATRIX

#endif	//_INC_EKU_EXPREVAL_CONV