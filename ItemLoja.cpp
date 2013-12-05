#include "stdafx.h"
#include "ItemLoja.h"
#include "CalculosUteis.h"
#include "Conversoes.h"

ItemLoja::ItemLoja(Vetor posicao,Vetor tamanho,tipos::Item_loja itemLoja):Componente(posicao)
{

	ItemLoja::item =  itemLoja;
	ItemLoja::tamanho = tamanho;
	ItemLoja::imagemItem  = new Imagem(posicao,itemLoja.caminho);
	ItemLoja::alinhado = false;

	int posicaoX = posicao.x+ (tamanho.x*PORCENTAGEM_X);

	ItemLoja::labelNome=new Label(
								Vetor(posicaoX,posicao.y),
								Vetor(tamanho.x - (tamanho.x*PORCENTAGEM_X),tamanho.y*PORCENTAGEM_Y),
								itemLoja.descricao,"comic",TAMANHO::PEQUENO,true,true);
	
	ItemLoja::labelQuantidade=new Label(
								Vetor(posicaoX,labelNome->getPosisao().y + labelNome->getTamanho().y),
								Vetor( (tamanho.x - (tamanho.x*PORCENTAGEM_X) )/2,tamanho.y*PORCENTAGEM_Y),
								"Quantidade","comic",TAMANHO::PEQUENO);
	
	ItemLoja::spinner   = new NumberSpinner(
								Vetor(posicaoX+ (tamanho.x - (tamanho.x*PORCENTAGEM_X) )/2,labelNome->getPosisao().y+labelNome->getTamanho().y),
								Vetor( (tamanho.x - (tamanho.x*PORCENTAGEM_X) )/2,tamanho.y*PORCENTAGEM_Y)
							);
	
	ItemLoja::labelTotal = new Label(
								Vetor(posicao.x+ (tamanho.x*PORCENTAGEM_X) ,labelQuantidade->getPosisao().y+labelQuantidade->getTamanho().y),
								Vetor(tamanho.x - (tamanho.x*PORCENTAGEM_X),tamanho.y*PORCENTAGEM_Y),
								"Total:","comic",TAMANHO::PEQUENO);
	ItemLoja::botaoComprar = new Botao(
								Vetor(posicao.x+ (tamanho.x*PORCENTAGEM_X) ,labelTotal->getPosisao().y+labelTotal->getTamanho().y),
								"ui/botoes/em-branco-pequeno.png",
								"Comprar",
								"comic",TAMANHO::PEQUENO);
	ItemLoja::botaoComprar->addListener(new BotaoComprarListener(this));
	
	ItemLoja::componentes.push_back(labelNome);
	ItemLoja::componentes.push_back(imagemItem);
	ItemLoja::componentes.push_back(labelQuantidade);
	ItemLoja::componentes.push_back(spinner);
	ItemLoja::componentes.push_back(labelTotal);
	ItemLoja::componentes.push_back(botaoComprar);

}


ItemLoja::~ItemLoja(void)
{
}
void ItemLoja::desenhar(IVideoDriver * driver)
{
	//for(int i=0;i<componentes.size();i++){
	//	componentes[i]->atualizarPosisao(CalculosUteis::somarAtributosVetor(componentes[i]->getPosisao(),getPosisao()));
	//}
	if( habilitado() )
	{
		//desenha o fundo
		driver->draw2DRectangle(
			SColor(255,255,255,255),
			core::rect<s32>(
				(int)ItemLoja::posicao.x,
				(int)ItemLoja::posicao.y,
				(int)ItemLoja::posicao.x +(int)ItemLoja::tamanho.x,
				(int)ItemLoja::posicao.y + (int)ItemLoja::tamanho.y
			)
		);
		int total = ItemLoja::spinner->getValor() * ItemLoja::item.valor;
		ItemLoja::labelTotal->setTexto("Total: "+Conversoes::converteParaString(total));
		for(int i=0;i<componentes.size();i++)
			componentes[i]->desenhar(driver);
		//ItemLoja::imagemItem->desenhar(driver);
	
		if(!alinhado)
		{
			//alinha a imagem
			float diffX = ( ItemLoja::tamanho.x*PORCENTAGEM_X ) - ItemLoja::imagemItem->getTamanho().x ;
			float diffY = ItemLoja::tamanho.y -   ItemLoja::imagemItem->getTamanho().y ;
	
			ItemLoja::imagemItem->atualizarPosisao(
								Vetor(
									ItemLoja::imagemItem->getPosisao().x+(diffX/2),
									ItemLoja::imagemItem->getPosisao().y+(diffY/2)));
		
			//alinha o botão-conferir
			
			diffX = (ItemLoja::tamanho.x-(ItemLoja::tamanho.x*PORCENTAGEM_X) - botaoComprar->getTamanho().x);
			diffY = (ItemLoja::tamanho.y-(ItemLoja::tamanho.y*PORCENTAGEM_Y) - botaoComprar->getTamanho().y);
			diffY = 0;
			ItemLoja::botaoComprar->atualizarPosisao(
											Vetor(
												ItemLoja::botaoComprar->getPosisao().x + (diffX/2),
												ItemLoja::botaoComprar->getPosisao().y + (diffY/2)));
			
			alinhado = true;
		}
	}

}

tipos::Item_loja ItemLoja::getItem()
{
	return ItemLoja::item;

}

void ItemLoja::onClique(Vetor pos)
{
	ItemLoja::botaoComprar->onClique(pos);
	ItemLoja::spinner->onClique(pos);
}
void ItemLoja::posicaoCaptada(Vetor pos)
{

}

void ItemLoja::atualizarTamanho(Vetor tamanho)
{
	ItemLoja::tamanho = tamanho;
}