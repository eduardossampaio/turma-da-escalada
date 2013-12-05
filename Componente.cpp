#include "stdafx.h"
#include "Componente.h"
using namespace tipos;


Componente::Componente(Vetor posicao)
{
	Componente::posicao = posicao;
}


Componente::~Componente(void)
{
}

void Componente::atualizarPosisao(Vetor pos)
{
	Componente::posicao = pos;
}

Vetor Componente::getPosisao()
{
	return Componente::posicao;
}

void Componente::habilitar (bool habilita)
{
	Componente::foiHabilitado = habilita;

}

bool Componente::habilitado()
{
	return Componente::foiHabilitado;
}