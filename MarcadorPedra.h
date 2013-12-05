#pragma once

#include "tipos.h"
#include "Cronometro.h"
class MarcadorPedra
{
public:
	MarcadorPedra(tipos::Vetor posicao);
	~MarcadorPedra(void);

	bool pontoDentroMarcador(tipos::Vetor ponto);
	bool pontoDentroMarcador(tipos::Vetor ponto,float margem);
	void setMargem(float margem);
	float	 getMargem();
	tipos::Vetor getCoordenada();
	void setCoordenada(tipos::Vetor c);
	float getTempo();
private:
	tipos::Vetor coordenada;
	float margem;
	Cronometro cronometro;
};

