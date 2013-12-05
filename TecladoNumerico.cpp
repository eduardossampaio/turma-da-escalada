#include "stdafx.h"
#include "TecladoNumerico.h"

#include "Configuracoes.h"

TecladoNumerico::TecladoNumerico(Vetor posicao):TecladoVirtual(posicao)
{
	Configuracoes * configuracoes = new Configuracoes();
	tipos::configuracoes config = configuracoes->carregarConfigucacoes();
	altura = config.resolucao.y;
	largura = config.resolucao.x;

	
	

	

	TecladoNumerico::qtdX = 3;
	TecladoNumerico::qtdY = 4;

	criarTecla("1",0,0,1,Comportamento::LETRA);
	criarTecla("2",1,0,1,Comportamento::LETRA);
	criarTecla("3",2,0,1,Comportamento::LETRA);

	criarTecla("4",0,1,1,Comportamento::LETRA);
	criarTecla("5",1,1,1,Comportamento::LETRA);
	criarTecla("6",2,1,1,Comportamento::LETRA);

	criarTecla("7",0,2,1,Comportamento::LETRA);
	criarTecla("8",1,2,1,Comportamento::LETRA);
	criarTecla("9",2,2,1,Comportamento::LETRA);

	criarTecla(".",0,3,1,Comportamento::LETRA);
	criarTecla("0",1,3,1,Comportamento::LETRA);
	criarTecla("<-",2,3,1,Comportamento::BACKSPACE);


}


TecladoNumerico::~TecladoNumerico(void)
{
}

void TecladoNumerico::onClique(Vetor pos)
 {
	 if(foiHabilitado)
	 {
			for(int i=0;i<TecladoNumerico::teclas.size();i++){
				TecladoNumerico::teclas[i]->setAlvo(TecladoVirtual::alvo);
				TecladoNumerico::teclas[i]->onClique(pos);
			}
	}
 }
void TecladoNumerico::posicaoCaptada(Vetor pos) 
{
}
 
bool TecladoNumerico::emCimaDoTeclado(Vetor pos)
{
	return  CalculosUteis::pontoDentroDeArea(pos,posicao,Vetor(largura,altura));
}


