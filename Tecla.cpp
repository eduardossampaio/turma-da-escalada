#include "stdafx.h"
#include "Tecla.h"
#include "MouseSensor.h"
using namespace irr;
using namespace gui;
Tecla::Tecla(Vetor pos,Vetor tamanho) : Componente(pos)
{
	Tecla::tamanho = tamanho;
	Tecla::labelTexto = new Label(pos,tamanho,"","comic",TAMANHO::PEQUENO,true,true);
}


Tecla::~Tecla(void)
{
}
Tecla::Tecla(string texto,Vetor pos,Vetor tamanho):Componente(pos)
{
	Tecla::tamanho = tamanho;
	Tecla::texto = texto;
	Tecla::labelTexto = new Label(pos,tamanho,texto,"comic",TAMANHO::PEQUENO,true,true);
}

void Tecla::desenhar(IVideoDriver * driver)
{
	driver->draw2DRectangle(video::SColor(255,190,190,190),core::rect<irr::s32>((int)posicao.x,(int)posicao.y,posicao.x+tamanho.x,posicao.y+tamanho.y));

	labelTexto->desenhar(driver);
		
	
}

void Tecla::setTexto(string texto)
{
	Tecla::texto = texto;
}

string Tecla::getTexto()
{
	return Tecla::texto;
}

void Tecla::onClique(Vetor pos)
{
	 Vetor fim = Vetor(getPosisao().x + getTamanho().x , getPosisao().y + getTamanho().y);
        if(CalculosUteis::pontoDentroDeArea(pos,getPosisao(),fim)){
			if(getComportamento()!=NULL && getAlvo() !=NULL)
                getComportamento()->executarAcaoTecla(getAlvo());
        }
}

void Tecla::posicaoCaptada(Vetor pos)
{

}


Vetor Tecla::getTamanho()
{
	return Tecla::tamanho;
}

Editavel * Tecla::getAlvo()
{
	return Tecla::alvo;
}
void Tecla::setAlvo(Editavel * alvo)
{
	Tecla::alvo = alvo;
}

void Tecla::setComportamento(ComportamentoTecla * comportamento)
{
	Tecla::comportamento = comportamento;

}
ComportamentoTecla * Tecla::getComportamento()
{
	return Tecla::comportamento;

}