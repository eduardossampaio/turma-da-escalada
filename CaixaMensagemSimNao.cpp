#include "stdafx.h"
#include "CaixaMensagemSimNao.h"


CaixaMensagemSimNao::CaixaMensagemSimNao(Vetor pos,Vetor tamanho,std::string msg,CliqueListener * listenerSim ,CliqueListener * listenerNao ): CaixaMensagem(pos,tamanho)
{
	CaixaMensagemSimNao::texto	=	msg;
	
	CaixaMensagemSimNao::alinhado	=	false;
	
	const int margem_x = tamanho.x*0.05;

	int x = pos.x+margem_x ;
	int y = pos.y+(tamanho.y*0.2) ;


	CaixaMensagemSimNao::mensagem = new Label(
		Vetor(pos.x+margem_x,pos.y+margem_x),
		Vetor(tamanho.x- margem_x*2 ,tamanho.y*0.5),//tamanho
		texto,"comic",TAMANHO::PEQUENO,true,true);
	
	
	CaixaMensagemSimNao::areaBotoes.v1 = Vetor(pos.x+margem_x,(pos.y + pos.y*0.5)+margem_x);
	CaixaMensagemSimNao::areaBotoes.v2 = Vetor(pos.x-margem_x+tamanho.x  ,pos.y +tamanho.y-margem_x);
	
	CaixaMensagemSimNao::areaBotaoSim.v1 = Vetor(areaBotoes.v1.x,areaBotoes.v1.y);
	CaixaMensagemSimNao::areaBotaoSim.v2 = Vetor(areaBotoes.v1.x +(areaBotoes.v2.x-areaBotoes.v1.x) / 2,areaBotoes.v2.y);
	
	CaixaMensagemSimNao::areaBotaoNao.v1 = Vetor(areaBotoes.v1.x +(areaBotoes.v2.x-areaBotoes.v1.x) / 2,areaBotoes.v1.y);
	CaixaMensagemSimNao::areaBotaoNao.v2 = Vetor(areaBotoes.v2.x,areaBotoes.v2.y);

	CaixaMensagemSimNao::botaoSim=new Botao(
		areaBotaoSim.v1,
		"ui/botoes/em-branco-pequeno.png","SIM","comic",	TAMANHO::GRANDE
	);
	
	CaixaMensagemSimNao::botaoNao=new Botao(
		areaBotaoNao.v1,
		"ui/botoes/em-branco-pequeno.png","NAO","comic",	TAMANHO::GRANDE
	);
	
	if(listenerSim) 
		botaoSim->addListener(listenerSim);
	
	if(listenerNao) 
		botaoNao->addListener(listenerNao);

	componentes.push_back(mensagem);							
	componentes.push_back(botaoSim);
	componentes.push_back(botaoNao);

	CaixaMensagemSimNao::fechou = true;
}


CaixaMensagemSimNao::~CaixaMensagemSimNao(void)
{
}

void CaixaMensagemSimNao::setListenerFechar(CliqueListener * listener)
{
	CaixaMensagemSimNao::botaoSim->addListener(listener);
	CaixaMensagemSimNao::botaoNao->addListener(listener);
}
void CaixaMensagemSimNao::ativar()
{
	CaixaMensagemSimNao::Componente::ativarFoco();
	CaixaMensagemSimNao::CliqueListener::ativarFoco();

	CaixaMensagemSimNao::botaoSim->Componente::ativarFoco();
	CaixaMensagemSimNao::botaoSim->CliqueListener::ativarFoco();

	CaixaMensagemSimNao::botaoNao->Componente::ativarFoco();
	CaixaMensagemSimNao::botaoNao->CliqueListener::ativarFoco();

	CaixaMensagemSimNao::fechou = false;

}
void CaixaMensagemSimNao::fechar()
{
	CaixaMensagemSimNao::Componente::desativarFoco();
	CaixaMensagemSimNao::CliqueListener::desativarFoco();

	CaixaMensagemSimNao::botaoSim->Componente::desativarFoco();
	CaixaMensagemSimNao::botaoSim->CliqueListener::desativarFoco();

	CaixaMensagemSimNao::botaoNao->Componente::desativarFoco();
	CaixaMensagemSimNao::botaoNao->CliqueListener::desativarFoco();

	CaixaMensagemSimNao::fechou = true;
}
void CaixaMensagemSimNao::onClique(Vetor pos) 
{
	CaixaMensagemSimNao::botaoSim->onClique(pos);
	CaixaMensagemSimNao::botaoNao->onClique(pos);
}
void CaixaMensagemSimNao::posicaoCaptada(Vetor pos)
{

}

void CaixaMensagemSimNao::desenhar(IVideoDriver * driver)
{
	if(!fechou )
	{

		driver->draw2DRectangle(SColor(255,245,245,245),core::rect<s32>(posicao.x,posicao.y,posicao.x+tamanho.x,posicao.y+tamanho.y));



	
		for(int i=0;i<componentes.size();i++)
			componentes[i]->desenhar(driver);
		if(!alinhado)
		{
			alinhado = true;
			Vetor tamanhoBotaoSim = CaixaMensagemSimNao::botaoSim->getTamanho();		
			Vetor posicaoBotaoSim = CaixaMensagemSimNao::botaoSim->getPosisao();

			Vetor tamanhoBotaoNao = CaixaMensagemSimNao::botaoNao->getTamanho();		
			Vetor posicaoBotaoNao = CaixaMensagemSimNao::botaoNao->getPosisao();

			int x1 = posicaoBotaoSim.x+ (areaBotaoSim.v2.x - areaBotaoSim.v1.x - tamanhoBotaoSim.x)/2;
			int y1 = posicaoBotaoSim.y+ (areaBotaoSim.v2.y - areaBotaoSim.v1.y - tamanhoBotaoSim.y)/2;
		
			int x2 = posicaoBotaoNao.x+ (areaBotaoNao.v2.x - areaBotaoNao.v1.x - tamanhoBotaoNao.x)/2;
			int y2 = posicaoBotaoNao.y+ (areaBotaoNao.v2.y - areaBotaoNao.v1.y - tamanhoBotaoNao.y)/2;

			CaixaMensagemSimNao::botaoSim->atualizarPosisao(Vetor( x1,y1 ));
			CaixaMensagemSimNao::botaoNao->atualizarPosisao(Vetor( x2,y2 ));
		}
	}
}