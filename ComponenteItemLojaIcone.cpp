#include "stdafx.h"
#include "ComponenteItemLojaIcone.h"
#include "JanelaLoja2.h"

ComponenteItemLojaIcone::ComponenteItemLojaIcone(JanelaLoja2 * janela,Vetor pos,Vetor tamanho,tipos::Item_loja item):Componente(pos),item(item),janela(janela),tamanho(tamanho)
{
	ComponenteItemLojaIcone::imagem = new Imagem(pos,item.caminho);			
	alinhado = false;
}


ComponenteItemLojaIcone::~ComponenteItemLojaIcone(void)
{
}

void ComponenteItemLojaIcone::desenhar(IVideoDriver * driver)
{
	if(habilitado())
	{
		//driver->draw2DRectangle(
			//irr::video::SColor(255,0,0,255),
			//irr::core::rect<irr::s32>(posicao.x,posicao.y,posicao.x + tamanho.x,posicao.y + tamanho.y));
		//linha de cima
		//driver->draw2DLine(irr::core::vector2d<s32>(posicao.x,posicao.y),irr::core::vector2d<s32>(posicao.x+tamanho.x,posicao.y));
		//linha da esquerda
		//driver->draw2DLine(irr::core::vector2d<s32>(posicao.x,posicao.y),irr::core::vector2d<s32>(posicao.x,posicao.y+tamanho.y));		
		ComponenteItemLojaIcone::imagem->desenhar(driver);
		if(!alinhado)
		{
			alinhado = true;
			Vetor tam_img = ComponenteItemLojaIcone::imagem->getTamanho();
			Vetor posicao = ComponenteItemLojaIcone::imagem->getPosisao();
			posicao.x += (tamanho.x-tam_img.x) / 2;
			posicao.y += (tamanho.y-tam_img.y) / 2;
			ComponenteItemLojaIcone::imagem->atualizarPosisao(posicao);
		}
	}
}

void ComponenteItemLojaIcone::onClique(Vetor pos)
{
	if(foiHabilitado && CalculosUteis::pontoDentroDeArea(pos,posicao,CalculosUteis::somarAtributosVetor(posicao,tamanho)))
	{
		printf("clicou %s\n",item.descricao.c_str());
		//seleciona o item na janela
		ComponenteItemLojaIcone::janela->setItemSelecionado(item);
	}
}
void ComponenteItemLojaIcone::posicaoCaptada(Vetor pos)
{

}