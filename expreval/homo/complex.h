#ifndef _INC_EKU_EXPREVAL_HOMO_COMPLEX
#define _INC_EKU_EXPREVAL_HOMO_COMPLEX

template<class typ>
std::complex<typ> cabs(const std::complex<typ>& c)
{return std::complex<typ>(std::abs(c),0);}

template<class typ>
std::complex<typ> carg(const std::complex<typ>& c)
{return std::complex<typ>(std::arg(c),0);}

template<class typ>
std::complex<typ> cnorm(const std::complex<typ>& c)
{return std::complex<typ>(std::norm(c),0);}

template<class typ>
std::complex<typ> creal(const std::complex<typ>& c)
{return std::complex<typ>(std::real(c),0);}

template<class typ>
std::complex<typ> cimag(const std::complex<typ>& c)
{return std::complex<typ>(std::imag(c),0);}

template<class typ>
inline std::complex<typ> ccsc(const std::complex<typ>& a){return typ(1)/std::sin(a);}
template<class typ>
inline std::complex<typ> csec(const std::complex<typ>& a){return typ(1)/std::cos(a);}
template<class typ>
inline std::complex<typ> ccot(const std::complex<typ>& a){return std::tan(m_pi/2-a);}

template<class typ>
inline std::complex<typ> ccsch(const std::complex<typ>& a){return typ(1)/std::sinh(a);}
template<class typ>
inline std::complex<typ> csech(const std::complex<typ>& a){return typ(1)/std::cosh(a);}
template<class typ>
inline std::complex<typ> ccoth(const std::complex<typ>& a){return typ(1)/std::tanh(a);}

/*template<class typ>
inline std::complex<typ> casinh(const std::complex<typ>& a)
{return std::log(std::operator+(a,std::sqrt(a*a+1)));}

template<class typ>
inline std::complex<typ> cacosh(const std::complex<typ>& a)
{return std::log(a+std::sqrt(a*a-1));}

template<class typ>
inline std::complex<typ> catanh(const std::complex<typ>& a)
{return std::log((1+a)/(1-a))/2;}

template<class typ>
inline std::complex<typ> casech(const std::complex<typ>& a)
{return std::log((1+std::sqrt(1-a*a))/a);}

template<class typ>
inline std::complex<typ> cacsch(const std::complex<typ>& a)
{return std::log(1/a+std::sqrt(1+a*a)/std::abs(a));}

template<class typ>
inline std::complex<typ> cacoth(const std::complex<typ>& a)
{return std::log((a+1)/(a-1))/2;}*/

#endif	//_INC_EKU_EXPREVAL_HOMO_COMPLEX