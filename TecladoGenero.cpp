#include "stdafx.h"
#include "TecladoGenero.h"
#include "Configuracoes.h"

TecladoGenero::TecladoGenero(Vetor pos):TecladoVirtual(pos)
{
	Configuracoes * configuracoes = new Configuracoes();
	tipos::configuracoes config = configuracoes->carregarConfigucacoes();

	TecladoGenero::altura = config.resolucao.y;
	TecladoGenero::largura =  config.resolucao.x;
	
	TecladoGenero::qtdX = 2;
	TecladoGenero::qtdY = 1;

	criarTecla("MENINO",0,0,1,Comportamento::GENERO);
	criarTecla("MENINA",1,0,1,Comportamento::GENERO);
}


TecladoGenero::~TecladoGenero(void)
{
}

 bool TecladoGenero::emCimaDoTeclado(Vetor pos) 
 {
	 return foiHabilitado && CalculosUteis::pontoDentroDeArea(pos,posicao,Vetor(largura,altura));
 }

