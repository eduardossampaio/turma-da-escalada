#include "stdafx.h"
#include "TeclaListener.h"
#include "CalculosUteis.h"
#include <iostream>
#include <string>

TeclaListener::TeclaListener(Tecla * tecla)
{
	TeclaListener::tecla = tecla;
}


TeclaListener::~TeclaListener(void)
{
}

void TeclaListener::onClique(tipos::Vetor posicao)
{
	Vetor fim = Vetor(tecla->getPosisao().x + tecla->getTamanho().x , tecla->getPosisao().y + tecla->getTamanho().y);
	if(CalculosUteis::pontoDentroDeArea(posicao,tecla->getPosisao(),fim)){
		cout << "clicado: "<< tecla->getTexto()<<endl;
		tecla->getComportamento()->executarAcaoTecla(tecla->getAlvo());
	}
	
}
void TeclaListener::posicaoCaptada(tipos::Vetor posicao)
{

}