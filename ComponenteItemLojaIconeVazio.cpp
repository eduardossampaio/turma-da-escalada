#include "stdafx.h"
#include "ComponenteItemLojaIconeVazio.h"


ComponenteItemLojaIconeVazio::ComponenteItemLojaIconeVazio(Vetor pos,Vetor tamanho): Componente(pos),tamanho(tamanho)
{
}


ComponenteItemLojaIconeVazio::~ComponenteItemLojaIconeVazio(void)
{
}

void ComponenteItemLojaIconeVazio::desenhar(IVideoDriver * driver) 
{		
	if(foiHabilitado)
	{
		//desenhar um quadrado cinza
		driver->draw2DRectangle(
			irr::video::SColor(255,169,169,169),
			irr::core::rect<irr::s32>(posicao.x,posicao.y,posicao.x + tamanho.x,posicao.y + tamanho.y));
		//linha de cima
		driver->draw2DLine(irr::core::vector2d<s32>(posicao.x,posicao.y),irr::core::vector2d<s32>(posicao.x+tamanho.x,posicao.y));
		//linha de baixo
		//driver->draw2DLine(irr::core::vector2d<s32>(posicao.x,posicao.y+tamanho.y),irr::core::vector2d<s32>(posicao.x+tamanho.x,posicao.y+tamanho.y));
		//linha da esquerda
		driver->draw2DLine(irr::core::vector2d<s32>(posicao.x,posicao.y),irr::core::vector2d<s32>(posicao.x,posicao.y+tamanho.y));
	}
}