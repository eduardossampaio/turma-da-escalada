#include "stdafx.h"
#include "TecladoVirtual.h"


TecladoVirtual::TecladoVirtual(Vetor v):Componente(v)
{
	foiHabilitado = false;
}


TecladoVirtual::~TecladoVirtual(void)
{
}

void TecladoVirtual::desenhar(IVideoDriver * driver)
{
	if (foiHabilitado)
	{
		for (int i = 0; i < TecladoVirtual::teclas.size(); i++)
			TecladoVirtual::teclas[i]->desenhar(driver);
	}
}
void TecladoVirtual::setAlvo(Editavel * alvo)
{
	TecladoVirtual::alvo = alvo;
}

Editavel *TecladoVirtual:: getAlvo()
{
	return TecladoVirtual::alvo;
}
void TecladoVirtual::onClique(Vetor pos)
{
	if(foiHabilitado)
	{
		for(int i=0;i<TecladoVirtual::teclas.size();i++){
			TecladoVirtual::teclas[i]->setAlvo(TecladoVirtual::alvo);
			TecladoVirtual::teclas[i]->onClique(pos);
		}
	}
}
void TecladoVirtual::posicaoCaptada(Vetor pos)
{

}
void TecladoVirtual::criarTecla(std::string texto,int x,int y,int tamanho,Comportamento c)
{
	
	TecladoVirtual::alturaTecla = (altura - posicao.y)/ qtdY ;
	TecladoVirtual::larguraTecla = (largura - posicao.x)/ qtdX ;
	
	Tecla * tecla = new Tecla(
		texto,
		Vetor(posicao.x+(larguraTecla*x)+TECLADO_MARGEM_X/2,posicao.y+(alturaTecla*y)+TECLADO_MARGEM_Y/2),
		Vetor(larguraTecla*tamanho-TECLADO_MARGEM_X,alturaTecla-TECLADO_MARGEM_Y));

	
	//TeclaListener * listener = new TeclaListener(tecla);
	//tecla->setListener(listener);
	if(c==Comportamento::LETRA)
	{
		tecla->setComportamento(new ComportamentoLetra(tecla));
	}
	else if(c==Comportamento::BACKSPACE)
	{
		tecla->setComportamento(new ComportamentoBackSpace());
	}
	else if(c==Comportamento::SHIFT)
	{
		tecla->setComportamento(new ComportamentoShift(&teclas));	
	}
	else if(c==Comportamento::GENERO)
	{
		tecla->setComportamento(new ComportamentoGenero(tecla));
	}

	
	
		
	TecladoVirtual::teclas.push_back(tecla);

}
