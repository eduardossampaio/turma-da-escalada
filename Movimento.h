#pragma once
#include "tipos.h"
using namespace tipos;
enum  EstadoCaptura
{
	IDENTIFICANDO,
	VALIDO,
	INVALIDO
};

class Movimento
{
public:
	Movimento(void);
	~Movimento(void);

	
	

	virtual EstadoCaptura identificar(Esqueleto esqueleto) = 0;
	


};

