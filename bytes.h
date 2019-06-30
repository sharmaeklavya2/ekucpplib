#ifndef _INC_EKU_BYTES
#define _INC_EKU_BYTES

//#include<cstddef>

/*This header is used to extract bytes, words and dwords out of higher size data types
Eg. getting hiword of a dword or a lobyte of a word
It can also combine smaller data types to make higher data types.
Eg. 2 dwords can be combined to make a qword, 4 bytes to make a word
The header uses unions as its basis.
The union classes have also been provided with member functions and constructors
the union classes take their size (in bytes) as a template parameter*/

#ifdef MSVC
typedef uint8_t uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
#endif	//MSVC

namespace eku
{

	template<int size>
	union bytes{};

	template<>
	union bytes<1>
	{public:
		uint8_t byte[1];
		bytes(uint8_t a){byte[0]=a;}
		operator uint8_t()const{return byte[0];}
	};

	template<>
	union bytes<2>
	{public:
		uint16_t word[1];
		uint8_t byte[2];
		//byte[0] has lobyte and byte[1] has hibyte
		bytes(uint16_t a){word[0]=a;}
		bytes(uint8_t hibyte,int lobyte)
		{byte[1]=hibyte;byte[0]=lobyte;}
		operator uint16_t()const{return word[0];}
		bytes<1> hibyte()const{return byte[1];}
		bytes<1> lobyte()const{return byte[0];}
		bytes<1> hi()const{return byte[1];}
		bytes<1> lo()const{return byte[0];}
	};

	template<>
	union bytes<4>
	{public:
		uint32_t dword[1];
		uint16_t word[2];
		uint8_t byte[4];

		bytes(uint8_t a,uint8_t b,uint8_t c,uint8_t d)
		{byte[3]=a;byte[2]=b;byte[1]=c;byte[0]=d;}
		bytes(uint16_t hiword,uint16_t loword)
		{word[1]=hiword;word[0]=loword;}
		bytes(uint32_t a){dword[0]=a;}
		operator uint32_t()const{return dword[0];}
		bytes<2> hiword()const{return word[1];}
		bytes<2> loword()const{return word[0];}
		bytes<2> hi()const{return word[1];}
		bytes<2> lo()const{return word[0];}
	};

	template<>
	union bytes<8>
	{public:
		uint64_t qword[1];
		uint32_t dword[2];
		uint16_t word[4];
		uint8_t byte[8];

		bytes(uint16_t a,uint16_t b,uint16_t c,uint16_t d)
		{word[3]=a;word[2]=b;word[1]=c;word[0]=d;}
		bytes(uint32_t hidword,uint32_t lodword)
		{dword[1]=hidword;dword[0]=lodword;}
		bytes(uint64_t a){qword[0]=a;}
		operator uint64_t()const{return qword[0];}
		bytes<4> hidword()const{return dword[1];}
		bytes<4> lodword()const{return dword[0];}
		bytes<4> hi()const{return dword[1];}
		bytes<4> lo()const{return dword[0];}
	};

}	//end of namespace eku

#endif	//_INC_EKU_BYTES
