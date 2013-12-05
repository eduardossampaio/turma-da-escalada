#pragma once
#include "tipos.h"
#include <sstream>
class Conversoes
{
public:
	Conversoes(void);
	~Conversoes(void);
	/*
		converte um wchar_t * para int 
	*/
	static inline int converteParaInt(const wchar_t * c)
	{
		
		return atoi(converteParaChar(c));
	}


	static inline int converteParaInt(std::string  c)
	{
		
		return atoi(c.c_str());
	}

	static inline float converteParaFloat(std::string  c)
	{
		
		return atof(c.c_str());
	}
	static inline float converteParaFloat(const wchar_t * c)
	{
		
		return atof(converteParaChar(c));
	}

	/*
		converte um wchar_t * para char *
	*/
	static inline char* converteParaChar(const wchar_t * c)
	{

		int tempTam =  sizeof(char) * (wcslen(c) + 1);
		char *temp = (char *)malloc( tempTam);				
		int tam= sizeof(wchar_t) * (wcslen(c) + 1);
		size_t convertido;
		wcstombs_s(&convertido,temp,tempTam,c,tam);
		return temp;

	}
	/*
		converte uma string em wchar_t* para bool
		caso string seja 'true' retorna true,outro caso retorna false
	*/
	static inline bool converteParaBool(const wchar_t * c)
	{
		return strcmp(converteParaChar(c),"true")==0;
	}

	static inline const void converteParaWChar(wchar_t ** fim, int i)
	{				
		wchar_t vOut [12];
		_itow_s(i,vOut,sizeof(vOut)/2,10);
		//fim = &vOut;
	}
	static inline const wchar_t * converteParaWChar(char * c)
	{
		const size_t cSize = strlen(c)+1;
		size_t tamanho;
		int tam= sizeof(wchar_t) * (strlen(c) + 1);
		wchar_t* wc = new wchar_t[cSize];
//
		mbstowcs_s(&tamanho,wc,tam,c,cSize);

		int t=0;

		return wc;		
	}


	static inline void converteParaChar(char **dest,int i)
	{
		std::stringstream strs;
		strs << i;
		std::string temp_str = strs.str();
		char* char_type = (char*) temp_str.c_str();
		//return char_type;
		dest = &char_type;
		
	}
	static inline std::string converteParaString(int i)
	{
		ostringstream convert;   // stream used for the conversion
		convert << i;      // insert the textual representation of 'Number' in the characters in the stream
		return  convert.str(); // s
	}
	static inline std::string converteParaString(bool i)
	{
		return i == true ? "true" : "false";
	}
	static inline std::string converteParaString(float i)
	{
		ostringstream convert;   // stream used for the conversion
		convert << i;      // insert the textual representation of 'Number' in the characters in the stream
		return  convert.str(); // s
	}
};

