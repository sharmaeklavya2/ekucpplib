#ifndef _INC_EKU_TRIGO
#define _INC_EKU_TRIGO

#define m_pi 3.1415926535897932385
#define m_e 2.71828182845904523536

inline double rad_to_deg(double a){return a*180/m_pi;}
inline double deg_to_rad(double a){return a*m_pi/180;}

template<class typ>
inline typ csc(typ a){return 1/sin(a);}
template<class typ>
inline typ sec(typ a){return 1/cos(a);}
template<class typ>
inline typ cot(typ a){return tan(m_pi/2-a);}

template<class typ>
inline typ acsc(typ a){return asin(1/a);}
template<class typ>
inline typ asec(typ a){return acos(1/a);}
template<class typ>
inline typ acot(typ a){return m_pi/2-atan(a);}

inline double sind(double a){return sin(deg_to_rad(a));}
inline double cosd(double a){return cos(deg_to_rad(a));}
inline double tand(double a){return tan(deg_to_rad(a));}
inline double cscd(double a){return 1/sin(deg_to_rad(a));}
inline double secd(double a){return 1/cos(deg_to_rad(a));}
inline double cotd(double a){return tan(deg_to_rad(90-a));}

inline double asind(double a){return rad_to_deg(asin(a));}
inline double acosd(double a){return rad_to_deg(asin(a));}
inline double atand(double a){return rad_to_deg(atan(a));}
inline double acscd(double a){return rad_to_deg(asin(1/a));}
inline double asecd(double a){return rad_to_deg(acos(1/a));}
inline double acotd(double a){return rad_to_deg(m_pi/2-atan(a));}

template<class typ>
inline typ csch(typ a){return 1/sinh(a);}
template<class typ>
inline typ sech(typ a){return 1/cosh(a);}
template<class typ>
inline typ coth(typ a){return 1/tanh(a);}

template<class typ>
inline typ asinh(typ a){return log(a+sqrt(a*a+1));}
template<class typ>
inline typ acosh(typ a){return log(a+sqrt(a*a-1));}
template<class typ>
inline typ atanh(typ a){return log((1+a)/(1-a))/2;}
template<class typ>
inline typ asech(typ a){return log((1+sqrt(1-a*a))/a);}
template<class typ>
inline typ acsch(typ a){return log(1/a+sqrt(1+a*a)/fabs(a));}
template<class typ>
inline typ acoth(typ a){return log((a+1)/(a-1))/2;}

#endif //_INC_EKU_TRIGO