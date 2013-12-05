#include "stdafx.h"
#include "ComponenteItemLojaSelecionado.h"
#include "JanelaLoja2.h"

class botaoComprarListener : public CliqueListener
{

	public:
	botaoComprarListener(JanelaLoja2 * janela,ComponenteItemLojaSelecionado * componente):janela(janela),componente(componente){}
	virtual void onClique(Vetor pos) override
	{
		janela->solicitaCompraItem(componente->getItem(),componente->getQuantidade());				
				
	}
	virtual void posicaoCaptada(Vetor pos) override{}
	private:
		JanelaLoja2 * janela;
		ComponenteItemLojaSelecionado * componente;
};

ComponenteItemLojaSelecionado::ComponenteItemLojaSelecionado(JanelaLoja2 * janela,Vetor pos,Vetor tamanho):Componente(pos),tamanho(tamanho),janela(janela)
{
	Vetor dim = Vetor(tamanho.x - pos.x,tamanho.y - pos.y);
			informacoes = new Label(pos,Vetor(dim.x*1.0,dim.y*0.2*3),"","comic",TAMANHO::PEQUENO,true,true);
		
			//quantidade
			labelQtdeTexto = new Label(Vetor(pos.x,pos.y+dim.y*0.2*3),Vetor(dim.x*0.4,dim.y*0.2),"Quantidade:","comic",TAMANHO::PEQUENO,true,true);			
			qtdeSpinner    = new NumberSpinner(Vetor(pos.x+dim.x*0.4,pos.y+dim.y*0.2*3),Vetor(dim.x*0.3,dim.y*0.2)); 
			qtdeSpinner->setMinimo(1);
			//area onde fica o botao
			areaBotaoInicio = Vetor(pos.x,pos.y+dim.y*0.2*4);
			areaBotaoFim    = Vetor (dim.x,dim.y*0.2);

			botaoComprar = new Botao(areaBotaoInicio,"ui/botoes/em-branco-pequeno.png","Comprar","comic",TAMANHO::MEDIO);
			botaoComprar->addListener(new botaoComprarListener(janela,this));
			alinhouBotao = false;
}


ComponenteItemLojaSelecionado::~ComponenteItemLojaSelecionado(void)
{
}

void ComponenteItemLojaSelecionado::onClique(Vetor pos)
{
	qtdeSpinner->onClique(pos);
	botaoComprar->onClique(pos);
}
void ComponenteItemLojaSelecionado::posicaoCaptada(Vetor pos)
{
}

void ComponenteItemLojaSelecionado::setItemSelecionado(tipos::Item_loja item)
{
	ComponenteItemLojaSelecionado::item = item; 
}

//atualiza as informacoes quando o item for selecionado
void ComponenteItemLojaSelecionado::atualizaItemSelecionado()
{		
	informacoes->setTexto(item.descricao);
}

void ComponenteItemLojaSelecionado::desenhar(IVideoDriver * driver)
{
	driver->draw2DRectangle(
			irr::video::SColor(255,245,245,245),
			irr::core::rect<irr::s32>(posicao.x,posicao.y,posicao.x + tamanho.x,posicao.y + tamanho.y));
	informacoes->desenhar(driver);
	labelQtdeTexto->desenhar(driver);
	qtdeSpinner->desenhar(driver);
			

	//botao teste
	driver->draw2DRectangle(
			irr::video::SColor(255,245,245,245),
			irr::core::rect<irr::s32>(
				areaBotaoInicio.x,
				areaBotaoInicio.y,
				areaBotaoInicio.x+areaBotaoFim.x,
				areaBotaoInicio.y + areaBotaoFim.y));
	
	botaoComprar->desenhar(driver);
	if(!alinhouBotao)
	{
		alinhouBotao = true;
		Vetor tam_botao = botaoComprar->getTamanho();
		Vetor dim =  Vetor(areaBotaoFim.x,areaBotaoFim.y);
		botaoComprar->atualizarPosisao(
			Vetor(
			areaBotaoInicio.x + (dim.x-tam_botao.x) /2,
			areaBotaoInicio.y + (dim.y-tam_botao.y) /2));
	}
			
}

tipos::Item_loja ComponenteItemLojaSelecionado::getItem()
{
	return item;
}
int ComponenteItemLojaSelecionado::getQuantidade()
{
	return qtdeSpinner->getValor();
}