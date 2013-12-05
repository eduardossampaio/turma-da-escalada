#include "stdafx.h"
#include "CaixaMensagemSimple.h"
#include "Janela.h"


CaixaMensagemSimple::CaixaMensagemSimple(Vetor pos,Vetor tamanho,std::string texto,tipoMensagem tipoMensagem):CaixaMensagem(pos,tamanho)
{
	//CaixaMensagemSimple::tamanho	=	tamanho;
	CaixaMensagemSimple::texto	=	texto;
	CaixaMensagemSimple::tipo		=	tipoMensagem;
	CaixaMensagemSimple::alinhado	=	false;
	
	const int margem_x = tamanho.x*0.05;

	int x = pos.x+margem_x ;
	int y = pos.y+(tamanho.y*0.2) ;
	bool temImagem = !tipoMensagem == tipoMensagem::NORMAL;
	if(tipoMensagem == tipoMensagem::ALERTA)
		CaixaMensagemSimple::imagem = new Imagem(Vetor(x,y),"ui/mensagem/alerta.png");
	else if (tipoMensagem == tipoMensagem::ERRO)
		CaixaMensagemSimple::imagem = new Imagem(Vetor(x,y),"ui/mensagem/erro.png");
	
	
	
	//colocar para se a mensagem sem imagem(mensagem comum) depois
	//este é para quando tive imagem
	CaixaMensagemSimple::labelMensagem = new Label(
									Vetor(pos.x+(tamanho.x*0.2),pos.y+(tamanho.y*0.2)),
									//Vetor(tamanho.x-margem_x,tamanho.y*0.4),//tamanho
									Vetor(tamanho.x- (pos.x+(tamanho.x*0.2)) ,tamanho.y*0.4),//tamanho
									texto,
									"comic",
									TAMANHO::PEQUENO,
									true,true);
	CaixaMensagemSimple::botao=new Botao(
								Vetor(pos.x+(tamanho.x*0.2),tamanho.y+pos.y-(tamanho.y*0.2)),
								"ui/botoes/em-branco-pequeno.png",
								"OK",
								"comic",								
								TAMANHO::GRANDE
								);
	
	
	
	//CaixaMensagem::botao->addListener(new BotaoListener());
	if(temImagem)
		componentes.push_back(imagem);
	componentes.push_back(labelMensagem);							
	componentes.push_back(botao);

	// Acrescentando o listener
	CaixaMensagemSimple::botao->addListener(new BotaoOKListener());

}

Botao * CaixaMensagemSimple::getBotaoOK()
{
	return CaixaMensagemSimple::botao;
}
CaixaMensagemSimple::~CaixaMensagemSimple(void)
{
}

void CaixaMensagemSimple::setBotaoOKListener(CliqueListener * listener)
{
	CaixaMensagemSimple::botao->addListener(listener);
}


void CaixaMensagemSimple::setListenerFechar(CliqueListener * listener)
{
	CaixaMensagemSimple::botao->addListener(listener);
}

void CaixaMensagemSimple::fechar()
{
	CaixaMensagemSimple::Componente::desativarFoco();
	CaixaMensagemSimple::CliqueListener::desativarFoco();
	CaixaMensagemSimple::botao->Componente::desativarFoco();
	CaixaMensagemSimple::botao->CliqueListener::desativarFoco();
	fechou = true;
}

void CaixaMensagemSimple::onClique(Vetor pos)
{
	CaixaMensagemSimple::botao->onClique(pos);
}
void CaixaMensagemSimple::posicaoCaptada(Vetor pos)
{

}
void CaixaMensagemSimple::ativar()
{
	Componente::ativarFoco();
	CliqueListener::ativarFoco();
	CaixaMensagemSimple::botao->::Componente::ativarFoco();
	CaixaMensagemSimple::botao->::CliqueListener::ativarFoco();
	fechou = false;
}


void CaixaMensagemSimple::desenhar(IVideoDriver * driver)
{

	if(!fechou)
	{
	
		driver->draw2DRectangle(SColor(255,245,245,245),core::rect<s32>(posicao.x,posicao.y,posicao.x+tamanho.x,posicao.y+tamanho.y));
		for(int i=0;i<componentes.size();i++)
			componentes[i]->desenhar(driver);
	
		if(!alinhado)
		{
			alinhado = true;
			Vetor tamanho		= CaixaMensagemSimple::botao->getTamanho();
			Vetor tamanhoLabel	= CaixaMensagemSimple::labelMensagem->getTamanho();
			Vetor posicao = CaixaMensagemSimple::botao->getPosisao();

			CaixaMensagemSimple::botao->atualizarPosisao(
				Vetor(
					posicao.x + (tamanhoLabel.x/2) - (tamanho.x/2),
					posicao.y
				//		+ (CaixaMensagem::tamanho.y-tamanhoLabel.y)/2
				));
		
		}
	}
}

