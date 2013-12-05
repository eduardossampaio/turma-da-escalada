#include "stdafx.h"
#include "CaixaVendaItem.h"
#include "NumberSpinner.h"

CaixaVendaItem::CaixaVendaItem(Vetor pos,Vetor tamanho,std::string msg,CliqueListener * listenerVender ,CliqueListener * listenerSair,int maximo):CaixaMensagem(pos,tamanho)
{
	CaixaVendaItem::texto	=	msg;
	
	CaixaVendaItem::alinhado	=	false;
	const float margem = 10;
	Vetor tamanhoComMargem = Vetor(tamanho.x - (2*margem),tamanho.y - (2*margem));
	CaixaVendaItem::areaTexto.v1.x = pos.x+margem;
	CaixaVendaItem::areaTexto.v1.y = pos.y+margem;
	CaixaVendaItem::areaTexto.v2.x = (pos.x + tamanhoComMargem.x ) - margem;
	CaixaVendaItem::areaTexto.v2.y = (pos.y + tamanhoComMargem.y/3) - margem;
	
	CaixaVendaItem::areaSpinner.v1.x = pos.x+margem ;
	CaixaVendaItem::areaSpinner.v1.y = CaixaVendaItem::areaTexto.v2.y ;
	CaixaVendaItem::areaSpinner.v2.x = (pos.x + tamanhoComMargem.x ) - margem;
	CaixaVendaItem::areaSpinner.v2.y = CaixaVendaItem::areaSpinner.v1.y+ (pos.y + tamanhoComMargem.y/3) - margem;

	CaixaVendaItem::areaBotoes.v1.x =pos.x+margem;
	CaixaVendaItem::areaBotoes.v1.y =CaixaVendaItem::areaSpinner.v2.y;
	CaixaVendaItem::areaBotoes.v2.x = (pos.x + tamanhoComMargem.x ) - margem;
	CaixaVendaItem::areaBotoes.v2.y = CaixaVendaItem::areaBotoes.v1.y+ (pos.y + tamanhoComMargem.y/4) - margem - margem;

	CaixaVendaItem::areaBotaoVender.v1 = areaBotoes.v1;
	CaixaVendaItem::areaBotaoVender.v2 = Vetor( areaBotoes.v2.x/2,areaBotoes.v2.y);

	CaixaVendaItem::areaBotaoSair.v1 = Vetor(  (areaBotoes.v2.x/2),areaBotoes.v1.y);
	CaixaVendaItem::areaBotaoSair.v2 = areaBotoes.v2;
	
	CaixaVendaItem::mensagem = new Label(areaTexto.v1,Vetor(areaTexto.v2.x-areaTexto.v1.x,areaTexto.v2.y-areaTexto.v1.y) ,texto,"comic",TAMANHO::PEQUENO,true,true);
	CaixaVendaItem::spinner = new NumberSpinner(areaSpinner.v1,Vetor (areaSpinner.v2.x - areaSpinner.v1.x,areaSpinner.v2.y - areaSpinner.v1.y)  );

	CaixaVendaItem::spinner->setMinimo(1);
	CaixaVendaItem::spinner->setMaximo(maximo);

	CaixaVendaItem::botaoVender = new Botao(areaBotaoVender.v1,"ui/botoes/em-branco-pequeno.png","Vender","comic",TAMANHO::MEDIO);
	CaixaVendaItem::botaoSair = new Botao(areaBotaoSair.v1,"ui/botoes/em-branco-pequeno.png","Sair","comic",TAMANHO::MEDIO);
	componentes.push_back(mensagem);
	componentes.push_back(spinner);
	componentes.push_back(botaoVender);
	componentes.push_back(botaoSair);

	if(listenerVender)
		botaoVender->addListener(listenerVender);
	if(listenerSair)
		botaoSair->addListener(listenerSair);
	alinhado = false;
}


CaixaVendaItem::~CaixaVendaItem(void)
{
}

void CaixaVendaItem::setListenerFechar(CliqueListener * listener)
{
	botaoSair->addListener(listener);
	botaoVender->addListener(listener);
}
void CaixaVendaItem::ativar()
{
	CliqueListener::ativarFoco();
	Componente::ativarFoco();
	botaoSair->CliqueListener::ativarFoco();
	botaoVender->CliqueListener::ativarFoco();
	spinner->CliqueListener::ativarFoco();
}
void CaixaVendaItem::fechar()
{
	botaoSair->CliqueListener::desativarFoco();
	botaoVender->CliqueListener::desativarFoco();
	spinner->CliqueListener::desativarFoco();
	Componente::desativarFoco();
	CliqueListener::desativarFoco();
}
void CaixaVendaItem::onClique(Vetor pos)
{
	botaoVender->onClique(pos);
	botaoSair->onClique(pos);
	spinner->onClique(pos);
}
void CaixaVendaItem::posicaoCaptada(Vetor pos)
{

}

void CaixaVendaItem::setListenerVender(CliqueListener * listener)
{
	CaixaVendaItem::botaoVender->addListener(listener);
}
void CaixaVendaItem::setListenerSair(CliqueListener * listener)
{
	CaixaVendaItem::botaoSair->addListener(listener);
}

void CaixaVendaItem::desenhar(IVideoDriver * driver)
{

	if(Componente::temFoco() )
	{
		driver->draw2DRectangle(SColor(255,255,0,0),core::rect<s32>(posicao.x,posicao.y,posicao.x+tamanho.x,posicao.y+tamanho.y));
		driver->draw2DRectangle(SColor(255,255,0,255),core::rect<s32>(areaTexto.v1.x,areaTexto.v2.y,areaTexto.v2.x,areaTexto.v2.y));
		for(int i=0;i<componentes.size();i++)
			componentes[i]->desenhar(driver);
		if(!alinhado)
		{
			alinhado = true;
			Vetor tamanhoBotaoVender = botaoVender->getTamanho();
			Vetor tamanhoAreaBotao = Vetor(areaBotaoVender.v2.x - areaBotaoVender.v1.x,areaBotaoVender.v2.y - areaBotaoVender.v1.y);
			Vetor posBotaoVender = botaoVender->getPosisao();
			float x_vender = posBotaoVender.x + ((tamanhoAreaBotao.x - tamanhoBotaoVender.x)/2);
			float y_vender = posBotaoVender.y + ((tamanhoAreaBotao.y - tamanhoBotaoVender.y)/2);
			botaoVender->atualizarPosisao(Vetor(x_vender,y_vender));


			Vetor tamanhoBotaoSair = botaoSair->getTamanho();
			Vetor tamanhoAreaBotaoSair = Vetor(areaBotaoSair.v2.x - areaBotaoSair.v1.x,areaBotaoSair.v2.y - areaBotaoSair.v1.y);
			Vetor posBotaoSair = botaoSair->getPosisao();
			float x_sair = posBotaoSair.x + ((tamanhoAreaBotaoSair.x - tamanhoBotaoSair.x)/2);
			float y_sair = posBotaoSair.y + ((tamanhoAreaBotaoSair.y - tamanhoBotaoSair.y)/2);
			botaoSair->atualizarPosisao(Vetor(x_sair,y_sair));
		}
	}

	
}
int CaixaVendaItem::getQuantidadeSelecionada()
{
	return CaixaVendaItem::spinner->getValor();		
}