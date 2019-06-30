#ifndef _INC_EKU_EXPREVAL_LOADVAR

template<class dtyp>
inline void load_var(std::vector<variable<dtyp> >& var)
{
	var.push_back(variable<dtyp>("ans",dtyp(0)));
}

template<>
inline void load_var<dbl>(std::vector<variable<dbl> >& var)
{
	var.push_back(variable<dbl>("ans",0));
	var.push_back(variable<dbl>("pi",m_pi));
	var.push_back(variable<dbl>("e",m_e));
}

#ifdef _COMPLEX_

template<>
inline void load_var<std::complex<dbl> >(std::vector<variable<std::complex<dbl> > >& var)
{
	var.push_back(variable<std::complex<dbl> >("ans",std::complex<dbl>(0,0)));
	var.push_back(variable<std::complex<dbl> >("i",std::complex<dbl>(0,1)));
	var.push_back(variable<std::complex<dbl> >("pi",std::complex<dbl>(m_pi,0)));
	var.push_back(variable<std::complex<dbl> >("e",std::complex<dbl>(m_e,0)));
}

template<>
inline void load_var<std::complex<itg> >(std::vector<variable<std::complex<itg> > >& var)
{
	var.push_back(variable<std::complex<itg> >("ans",std::complex<itg>(0,0)));
	var.push_back(variable<std::complex<itg> >("i",std::complex<itg>(0,1)));
}

#endif	//_COMPLEX_

#ifdef _INC_EKU_CONTAINER_SAVECTOR

template<>
inline void load_var<savct<itg> >(std::vector<variable<savct<itg> > >& var)
{
	var.push_back(variable<savct<itg> >("ans",savct<itg>(0,0)));
	var.push_back(variable<savct<itg> >("i",savct<itg>(0,1)));
	var.push_back(variable<savct<itg> >("j",savct<itg>(0,0,1)));
	var.push_back(variable<savct<itg> >("k",savct<itg>(0,0,0,1)));
}

template<>
inline void load_var<savct<dbl> >(std::vector<variable<savct<dbl> > >& var)
{
	var.push_back(variable<savct<dbl> >("ans",savct<dbl>(0,0)));
	var.push_back(variable<savct<dbl> >("i",savct<dbl>(0,1)));
	var.push_back(variable<savct<dbl> >("j",savct<dbl>(0,0,1)));
	var.push_back(variable<savct<dbl> >("k",savct<dbl>(0,0,0,1)));
	var.push_back(variable<savct<dbl> >("pi",savct<dbl>(m_pi)));
	var.push_back(variable<savct<dbl> >("e",savct<dbl>(m_e)));
}

#endif	//_INC_EKU_CONTAINER_SAVECTOR

#ifdef _INC_EKU_MATRIX_MATRIX
template<>
inline void load_var<matrix<dbl> >(std::vector<variable<matrix<dbl> > >& var)
{
	var.push_back(variable<matrix<dbl> >("ans",0));
	var.push_back(variable<matrix<dbl> >("pi",m_pi));
	var.push_back(variable<matrix<dbl> >("e",m_e));
}
#endif	//_INC_EKU_MATRIX_MATRIX

#endif	//_INC_EKU_EXPREVAL_LOADVAR