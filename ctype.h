#ifndef _INC_EKU_CTYPE
#define _INC_EKU_CTYPE 1

typedef unsigned char uchar;
typedef const char cchar;
typedef const unsigned char ucchar,cuchar;

#include<eku\charlist.h>

inline int isctrl(int);		//control character
inline int isvis(int);		//visible
inline int isarrow(int);	//arrow
inline int isding(int);		//dingbat
inline int istype(int);		//typeable using keyboard
inline int isonkb(int);		//visible on keyboard
inline int ispunc(int);		//punctuation
inline int iscurr(int);		//currency
inline int ismath(int);		//mathematical symbol
inline int ismop(int);		//mathematical opreator
inline int isobrac(int a);	//returnes 1 if a is '(', 2 if a is '{', 3 if a is '[',0 for none of these
inline int iscbrac(int a);	//returnes 1 if a is ')', 2 if a is '}', 3 if a is ']',0 for none of these
inline int isbrac(int);		//combination of isobrac(char) and iscbrac(char)

#ifndef isdigitfunc
inline int isdigit(int);	//numeric digit
#endif

inline int iseng(int);		//english alphabet or number
inline int isgreek(int);	//greek alphabet
inline int isengnum(int);	//english alphabet or number

#ifndef isalphafunc
inline int isalpha(int);	//alphabet
#endif

#ifndef isalnumfunc
inline int isalnum(int);	//alphabet or numeric digit
#endif

inline int iscaps(int);		//capital letter
inline int isengcaps(int);	//english capital letter
inline int issmall(int);	//small letter
inline int isengsmall(int);	//english small letter
inline uchar tocaps(int);	//convert to capital
inline uchar tosmall(int);	//convert to small
inline int isvowel(int);	//vowel
inline int iscons(int);		//consonant
inline int isengvowel(int);	//english vowel
inline int isengcons(int);	//english consonant
inline int isacc(int);		//accent
inline int isaccalpha(int);	//accented alphabet
inline int istrema(int);	//trema accent char
inline int isacute(int);	//acute accent char
inline int isgrave(int);	//grave accent char
inline int iscap(int);		//cap accent char
inline int isa(int);	//a
inline int ise(int);	//e
inline int isi(int);	//i
inline int iso(int);	//o
inline int isu(int);	//u
inline int isblock(int);	//block
inline int ispipe(int);		//pipe

uchar itoengsmall(int);	//converts int a to ath english small letter
uchar itoengcaps(int);	//converts int a to ath english capital letter
uchar digit(int);		//converts int to a char with the same face value
uchar remacc(int);		//removes the accent from a character
uchar makechar(int a,int b);	//makes an accented character from the alphabet a and character b

//--------------------------------------------------------------------------------------------

inline int isctrl(int a)
{
	if((a>=1 && a<=31)|| a==127)return 1;
	else return 0;
}

inline int isvis(int a)
{
	if((a>=6 && a<=10)|| a==13 || a==32 || a==255)return 0;
	else return 1;
}

inline int isarrow(int a)
{
	if(a==24 || a==30)return 1;
	else if(a==17 || a==27)return 2;
	else if(a==25 || a==31)return 3;
	else if(a==16 || a==26)return 4;
	else if(a==18 || a==23 || a==29)return 5;
	else return 0;
}

inline int isding(int a)
{
	if((a>=1 && a<=5)|| a==11 || a==12 ||(a>=14 && a<=31)|| a==127)return 1;
	else return 0;
}

inline int iscurr(int a)
{
	if(a==36 ||(a>=155 && a<=158))return 1;
	else return 0;
}

inline int istype(int a)
{
	if(a>=0 && a<=127)return 1;
	else return 0;
}

inline int isonkb(int a)
{
	if((a>=8 && a<=10)|| a==13 || a==27 ||(a>=32 && a<=127))return 1;
	else return 0;
}

inline int ispunc(int a)
{
	if((a>=32 && a<=34)||(a>=39 && a<=41)||a==44||a==46||a==58||a==59||a==63)return 1;
	else return 0;
}

#ifndef isdigitfunc
#define isdigitfunc 1
inline int isdigit(int a)
{
	if(a>='1' && a<='9')return 1;
	else if(a=='0')return 2;
	else return 0;
}
#endif

inline int ismop(int a)
{
	if(a==246||a==42||a==43||a==45||a==47||a==37||a==94)return 1;
	else if(a==251||a==253||a==33)return 2;
	else return 0;
}

inline int ismath(int a)
{
	if(ismop(a))return 1;
	else if((a>=60 && a<=62)||a==240||a==242||a==243||a==247)return 2;
	else if(a==40||a==41||a==46||a==91||a==93||a==227||a==228||a==235||a==236||a==239||a==244||a==245||a==248)return 3;
	else if(a==171||a==172)return 4;
	else return 0;
}

inline int isengvowel(int a){
	if(a=='a'||a=='e'||a=='i'||a=='o'||a=='u'||a=='A'||a=='E'||a=='O'||a=='I'||a=='U')return 1;
	else return 0;
}

inline int isvowel(int a)
{
	if(isengvowel(a))return 1;
	else if((a>=129 && a<=134)||(a>=136 && a<=151)||a==153||a==154||(a>=160 && a<=163)||a==166||a==167)return 2;
	else return 0;
}

inline int isobrac(int a)
{
	if(a=='(')return 1;
	else if(a=='{')return 2;
	else if(a=='[')return 3;
	else return 0;
}

inline int iscbrac(int a)
{
	if(a==')')return 1;
	else if(a=='}')return 2;
	else if(a==']')return 3;
	else return 0;
}

inline int isbrac(int a)
{
	if(a=='(' || a==')')return 1;
	else if(a=='{' || a=='}')return 2;
	else if(a=='[' || a==']')return 3;
	else return 0;
}

inline int iseng(int a)
{
	if((a>=65 && a<=90)||(a>=97 && a<=122))return 1;
	else return 0;
}

inline int isgreek(int a)
{
	if((a>=224 && a<=235)||a==237||a==238)return 1;
	else return 0;
}

inline int isaccalpha(int a)
{
	if((a>=128 && a<=144)||(a>=147 && a<=154)||(a>=160 && a<=165))return 1;
	else return 0;
}

#ifndef isalnumfunc
#define isalnumfunc
inline int isalpha(int a)
{
	if(iseng(a)||isgreek(a)||isaccalpha(a))return 1;
	else if(a==145||a==146||a==159||a==166||a==167)return 2;
	else return 0;
}
#endif

#ifndef isalnumfunc
#define isalnumfunc
inline int isalnum(int a){return isalpha(a)+isdigit(a);}
#endif

inline int isengnum(int a){return iseng(a)+isdigit(a);}

inline int iscaps(int a)
{
	if((a>=65 && a<=90)||a==128||(a>=142 && a<=144)||a==146||a==153||a==154||a==165||a==226||a==228||(a>=232 && a<=234))return 1;
	else return 0;
}

inline int isengcaps(int a)
{
	if(a>=65 && a<=90)return 1;
	else return 0;
}

inline int issmall(int a)
{
	if((a>=97 && a<=122)||a==145||(a>=129 && a<=141)||(a>=147 && a<=152)||(a>=159 && a<=164)||a==166||a==167||a==224||a==225||a==227||(a>=229 && a<=231)||a==235||a==237||a==238)return 1;
	else return 0;
}

inline int isengsmall(int a)
{
	if(a>=97 && a<=122)return 1;
	else return 0;
}

inline int isaccent(int a)
{
	if(a==94||a==96||a==126)return 1;
	else return 0;
}

inline int istrema(int a)
{
	if(a==129||a==132||a==137||a==139||a==142||a==148||(a>=152 && a<=154))return 1;
	else return 0;
}

inline int isacute(int a)
{
	if(a==130||a==144||(a>=160 && a<=163))return 1;
	else return 0;
}

inline int isgrave(int a)
{
	if(a==133||a==138||a==141||a==149||a==151)return 1;
	else return 0;
}

inline int iscap(int a)
{
	if(a==131||a==136||a==140||a==147||a==150)return 1;
	else return 0;
}

inline int isa(int a)
{
	if((a>=131 && a<=134)||a==160||a==166||a==97)return 1;
	else if(a==142||a==143||a==65)return 2;
	else return 0;
}

inline int ise(int a)
{
	if(a==130||(a>=136 && a<=138)||a==101)return 1;
	else if(a==69||a==144)return 2;
	else return 0;
}

inline int isi(int a)
{
	if(a==105||a==161||(a>=139 && a<=141))return 1;
	else if(a==73)return 2;
	else return 0;
}

inline int iso(int a)
{
	if(a==111||a==162||(a>=147 && a<=149)||a==167)return 1;
	else if(a==79||a==153)return 2;
	else return 0;
}

inline int isu(int a)
{
	if(a==117||a==129||a==150||a==151||a==163)return 1;
	else if(a==85||a==154)return 2;
	else return 0;
}

inline int isblock(int a)
{
	if((a>=219 && a<=223)||a==254)return 1;
	else if(a>=176 && a<=178)return 2;
	else return 0;
}

inline int ispipe(int a)
{
	if(a>=179 && a<=218)return 1;
	else return 0;
}

inline uchar itoengsmall(int a){return uchar(96+a%26);}
inline uchar itoengcaps(int a){return uchar(64+a%26);}
inline uchar digit(int a){return uchar(48+a%26);}

uchar tosmall(int a)
{
	int b;
	if(isengcaps(a))b=a+32;
	else if(a==128)b=135;
	else if(a==142)b=132;
	else if(a==143)b=134;
	else if(a==144)b=130;
	else if(a==146)b=145;
	else if(a==153)b=148;
	else if(a==154)b=129;
	else if(a==165)b=164;
	else b=a;
	return b;
}

uchar tocaps(int a)
{
	int b;
	if(isengsmall(a))b=a-32;
	else if(a==135)b=128;
	else if(a==132)b=142;
	else if(a==134)b=143;
	else if(a==130)b=144;
	else if(a==145)b=146;
	else if(a==148)b=153;
	else if(a==129)b=154;
	else if(a==164)b=165;
	else b=a;
	return b;
}

uchar remacc(int a)
{
	unsigned char b;
	if(isa(a)==1)b='a';
	else if(isa(a)==2)b='A';
	else if(ise(a)==1)b='e';
	else if(ise(a)==2)b='E';
	else if(isi(a)==1)b='i';
	else if(iso(a)==1)b='o';
	else if(iso(a)==2)b='O';
	else if(isu(a)==1)b='u';
	else if(isu(a)==2)b='U';
	else if(a==128)b='C';
	else if(a==135)b='c';
	else if(a==164)b='n';
	else if(a==165)b='N';
	else if(a==152)b='y';
	else b=a;
	return b;
}

uchar makechar(int a,int b)
{
	if(a=='a'){
		if(b==':'||b=='t')return 132;
		else if(b=='/'||b=='a')return 160;
		else if(b=='\\'||b=='`'||b=='g')return 133;
		else if(b=='^'||b=='c'||b=='r')return 131;
		else if(b==248||b=='d')return 134;
		else if(b=='e')return 145;
		else return a;
	}
	else if(a=='A'){
		if(b==':'||b=='t')return 142;
		else if(b==248||b=='d')return 143;
		else if(b=='E')return 146;
		else return a;
	}
	else if(a=='e'){
		if(b==':'||b=='t')return 137;
		else if(b=='/'||b=='a')return 130;
		else if(b=='\\'||b=='`'||b=='g')return 138;
		else if(b=='^'||b=='c'||b=='r')return 136;
		else return a;
	}
	else if(a=='E' && (b=='/'||b=='a'))return 144;
	else if(a=='i'){
		if(b==':'||b=='t')return 139;
		else if(b=='/'||b=='a')return 161;
		else if(b=='\\'||b=='`'||b=='g')return 141;
		else if(b=='^'||b=='c'||b=='r')return 140;
		else return a;
	}
	else if(a=='o'){
		if(b==':'||b=='t')return 148;
		else if(b=='/'||b=='a')return 162;
		else if(b=='\\'||b=='`'||b=='g')return 149;
		else if(b=='^'||b=='c'||b=='r')return 147;
		else return a;
	}
	else if(a=='O' && (b==':'||b=='t'))return 153;
	else if(a=='u'){
		if(b==':'||b=='t')return 129;
		else if(b=='/'||b=='a')return 163;
		else if(b=='\\'||b=='`'||b=='g')return 151;
		else if(b=='^'||b=='c'||b=='r')return 150;
		else return a;
	}
	else if(a=='U' && (b==':'||b=='t'))return 154;
	else if(a=='c' && (b=='5' || b==5))return 135;
	else if(a=='C' && (b=='5' || b==5))return 128;
	else if(a=='n' && (b=='~'||b=='w'))return 164;
	else if(a=='N' && (b=='~'||b=='w'))return 165;
	else if(a=='y' && (b==':'||b=='t'))return 152;
	else return a;
}

#endif