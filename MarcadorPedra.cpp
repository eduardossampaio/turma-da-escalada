#include "stdafx.h"
#include "MarcadorPedra.h"


MarcadorPedra::MarcadorPedra(tipos::Vetor posicao)
{
	MarcadorPedra::coordenada	=	posicao;
	MarcadorPedra::margem		=	8;

	
}


MarcadorPedra::~MarcadorPedra(void)
{
}

bool MarcadorPedra::pontoDentroMarcador(tipos::Vetor ponto)
{
	bool dentro =  
		ponto.x > coordenada.x - margem && ponto.x < coordenada.x + margem &&
		ponto.y > coordenada.y - margem && ponto.y < coordenada.y + margem &&
		ponto.z > coordenada.z - margem && ponto.z < coordenada.z + margem ;

	if(dentro)
	{
		if(!cronometro.iniciado())
			cronometro.iniciarContagem();
	}
	else
	{
		cronometro.pararContagem();
	}
	return dentro;
}

float MarcadorPedra::getTempo()
{
	return MarcadorPedra::cronometro.getTempoCorridoSegundos();
}
void MarcadorPedra::setMargem(float margem)
{
	MarcadorPedra::margem = margem;
}
float	MarcadorPedra::getMargem()
{
	return MarcadorPedra::margem;
}
tipos::Vetor MarcadorPedra::getCoordenada()
{
	return MarcadorPedra::coordenada;
}
void MarcadorPedra::setCoordenada(tipos::Vetor c)
{
	MarcadorPedra::coordenada = c;
}
bool MarcadorPedra::pontoDentroMarcador(tipos::Vetor ponto,float margem)
{
	
		
	return false;
}