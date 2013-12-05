#include "stdafx.h"
#include "CaixaTexto.h"
#include "irrlicht.h"
#include "Globais.h"
using namespace irr;

CaixaTexto::CaixaTexto(Vetor pos,Vetor tamanho) : Componente(pos)
{
	CaixaTexto::tamanho = tamanho;
	CaixaTexto::selecionado = false;
}


CaixaTexto::~CaixaTexto(void)
{
}


string CaixaTexto::getTexto()
{
	return CaixaTexto::texto;
}
void  CaixaTexto::setTexto(string texto)
{
	CaixaTexto::texto = texto;
}
void CaixaTexto::addTexto(string texto)
{
	CaixaTexto::texto+=texto;
}
void CaixaTexto::apagaTexto()
{
	CaixaTexto::texto="";
}

void CaixaTexto::desenhar(video::IVideoDriver * driver)
{
	if(!CaixaTexto::cronometroCursor.iniciado())
		cronometroCursor.iniciarContagem();	
	
	driver->draw2DRectangle(video::SColor(255,245,245,245),core::rect<irr::s32>((int)posicao.x,(int)posicao.y,posicao.x+tamanho.x,posicao.y+tamanho.y));
	
	std::string mostrar=CaixaTexto::texto;
	int tempo = cronometroCursor.getTempoCorridoSegundos() ;
	if (tempo % 2 ==0 && estaSelecionado())
		mostrar+="|";
	
	Globais::getIrrDevice()->getGUIEnvironment()->getFont("media/fontes/myfont.xml")->draw(
		mostrar.c_str(),
		core::rect<irr::s32>((int)posicao.x,(int)posicao.y,posicao.x+tamanho.x,posicao.y+tamanho.y),
		video::SColor(255,0,0,0),
		false,
		true
		);
}

bool CaixaTexto::posicaoDentroCaixa(Vetor v)
{
	return
		( (posicao.x<= v.x && posicao.x + tamanho.x>= v.x ) &&
		  (posicao.y<= v.y && posicao.y + tamanho.y>= v.y ));
}

void CaixaTexto::setSelecionado(bool selecionado)
{
	printf("selecionado :%d\n",selecionado);
	CaixaTexto::selecionado = selecionado;
	
}
	

bool CaixaTexto::estaSelecionado()
{
	return CaixaTexto::selecionado;
}

TecladoVirtual * CaixaTexto::getTeclado()
{
	return CaixaTexto::teclado;
}

void CaixaTexto::setTeclado(TecladoVirtual * teclado)
{
	CaixaTexto::teclado = teclado;

}