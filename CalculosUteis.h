#pragma once
#include "tipos.h"
#include <math.h>
using namespace tipos;
class CalculosUteis
{
public:
	CalculosUteis(void);
	~CalculosUteis(void);

	static inline float anguloEntrePontos(Vetor ponto1,Vetor ponto2)
	{				
		float angulo  = atan( (ponto1.y / ponto1.x ) - atan( ponto2.y / ponto2.x ) );
		return irr::core::radToDeg( angulo );

	}
	static inline float anguloEntrePontos(Vetor ponto1,Vetor ponto2,Vetor ponto3)
	{				
		float m1 = ( ponto2.y - ponto1.y ) / ( ponto2.x - ponto1.x );
		float m2 = ( ponto3.y - ponto1.y ) / ( ponto3.x - ponto1.x );
		float tg = abs( (m1-m2) / ( 1 + m1 * m2) );
		//float tg = ( (m1-m2) / ( 1 + m1 * m2) );
		return irr::core::radToDeg (atan(tg) );
	}
	static inline bool estaDentroDoRange(float anguloObtido,float anguloRef,float range)
	{
		return  ( (anguloObtido>= (anguloRef-range) ) && (anguloObtido <= (anguloRef+range)) );
	
	}
	static inline bool pontoDentroDeArea(Vetor ponto,Vetor inicio,Vetor fim)
	{
		return ponto.x>= inicio.x && ponto.x<=fim.x && ponto.y>=inicio.y && ponto.y<=fim.y;
	}

	static inline bool stringTodaEmMaiusculo(std::string str)
	{
		for(int i=0;i<str.length();i++)
			if(islower(str[i]))
				return false;
		return true;
		
	}

	static inline float distanciaEntrePontos(Vetor p1,Vetor p2)
	{
		return sqrt (pow((p2.x-p1.x),2)+ pow ((p2.y-p1.y),2));
	}

	static inline bool stringTodaEmMinusculo(std::string str)
	{
		for(int i=0;i<str.length();i++)
			if(isupper(str[i]))
				return false;
		return true;
		
	}
	static inline std::string transformaStringMaisuculo(std::string str)
	{
		std::string nova;
		for(int i=0;i<str.length();i++)
			nova+=toupper(str[i]);
		
		return nova;
	}

	static inline std::string transformaStringMinusculo(std::string str)
	{
		std::string nova;
		for(int i=0;i<str.length();i++)
			nova+=tolower(str[i]);
		
		return nova;
	}

	static inline Vetor somarAtributosVetor(Vetor v1,Vetor v2)
	{
		return Vetor(v1.x + v2.x,v1.y + v2.y ,v1.z + v2.z);
	}

	

};

