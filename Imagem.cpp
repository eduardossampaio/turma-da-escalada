#include "stdafx.h"
#include "Imagem.h"
#include "tipos.h"
#include <irrlicht.h>
using namespace irr;

Imagem::Imagem(Vetor posicao,string imagem) : Componente(posicao)
{
	Imagem::nomeImagem = imagem;
	Imagem::ativo = true;
	habilitar(true);
}

Imagem::Imagem(string imagem) : Componente(Vetor())
{
	Imagem::nomeImagem = imagem;
	Imagem::ativo = true;
	habilitar(true);
	
}

void Imagem::atualizaImagem(std::string nomeImagem)
{
	Imagem::nomeImagem = nomeImagem;
}



Imagem::~Imagem(void)
{
}

void Imagem::desenhar(IVideoDriver *driver)
{
	
	
	Vetor p = Imagem::posicao;		
	
	
	
	if(ativo)
	{
		images=driver->getTexture(Imagem::nomeImagem.c_str());
		driver->draw2DImage(images,irr::core::vector2d<s32>(p.x,p.y));
		
	}
	
}

Vetor Imagem::getTamanho()
{
	if(images!=NULL)
		return Vetor(images->getSize().Width,images->getSize().Height);
	return Vetor();
}
bool Imagem::isVisivel()
{
	return Imagem::ativo;
}

void Imagem::setVisivel(bool visivel)
{
	Imagem::ativo = visivel;
}
