#include "stdafx.h"
#include "JanelaEscolhaPersonagem.h"
#include "interface.h"
#include "Configuracoes.h"
#include "PersonagemDAO.h"
using namespace irr;
using namespace core;
using namespace gui;
using namespace video;
using namespace scene;

bool primeiro = true;
JanelaEscolhaPersonagem::JanelaEscolhaPersonagem(Perfil perfil,scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id):Janela(parent,mgr,id)
{
	Configuracoes * configuracoes = new Configuracoes();
	tipos::configuracoes config = configuracoes->carregarConfigucacoes();
	Vetor tela = config.resolucao;

	areaPersonagem.v1.x = 0;
	areaPersonagem.v1.y = 0;
	areaPersonagem.v2.x = tela.x ;
	areaPersonagem.v2.y = tela.y ;

	alinhouPersonagem = false;
	
	JanelaEscolhaPersonagem::perfil			= perfil;
	JanelaEscolhaPersonagem::cursor			= new KinectCursor();
	JanelaEscolhaPersonagem::fundo			= new Imagem(Vetor(),"ui/janela/fundo escolha personagem.jpg");
	JanelaEscolhaPersonagem::selecionado	= 0;
	JanelaEscolhaPersonagem::botaoProximo   = new Botao(Vetor(tela.x-10-64,tela.y/2 - 32)		,"media/icones/proximo.png");
	JanelaEscolhaPersonagem::botaoAnterior  = new Botao(Vetor(10,tela.y/2 - 32)					,"media/icones/anterior.png");

	JanelaEscolhaPersonagem::botaoConfirmar = new Botao(Vetor(tela.x - 10 -250,tela.y - 50 - 10)	,"ui/botoes/em-branco-normal.png","CONFIRMAR","comic",PEQUENO); 
	JanelaEscolhaPersonagem::botaoCancelar  = new Botao(Vetor(10,tela.y - 50 - 10)	,"ui/botoes/em-branco-normal.png","CANCELAR","comic",PEQUENO);
	JanelaEscolhaPersonagem::personagemImg	= new Imagem(Vetor(0,0),"");
	
	JanelaEscolhaPersonagem::cursor->adicionarListener(botaoProximo);
	JanelaEscolhaPersonagem::cursor->adicionarListener(botaoAnterior);
	JanelaEscolhaPersonagem::cursor->adicionarListener(botaoCancelar);
	JanelaEscolhaPersonagem::cursor->adicionarListener(botaoConfirmar);


	JanelaEscolhaPersonagem::botaoProximo->addListener (new botaoProximoCharListener(this));
	JanelaEscolhaPersonagem::botaoAnterior->addListener(new botaoCharAnteriorListener(this));
	JanelaEscolhaPersonagem::botaoCancelar->addListener(new BotaoCancelarListener(this));
	JanelaEscolhaPersonagem::botaoConfirmar->addListener(new BotaoConfirmarListener(this,perfil));

	/*---------------------------------------------------------------------------------------------------------*/
	
	JanelaEscolhaPersonagem::componentes.push_back(fundo);
	
	JanelaEscolhaPersonagem::componentes.push_back(botaoProximo);
	JanelaEscolhaPersonagem::componentes.push_back(botaoAnterior);
	JanelaEscolhaPersonagem::componentes.push_back(botaoConfirmar);
	JanelaEscolhaPersonagem::componentes.push_back(botaoCancelar);
	
	JanelaEscolhaPersonagem::componentes.push_back(cursor->getIcone());
	JanelaEscolhaPersonagem::componentes.push_back(personagemImg);
	
	/*---------------------------------------------------------------------------------------------------------------*/
	PersonagemDAO * dao = new PersonagemDAO();
	personagens = dao->getPersonagens();
	atualizarPersonagem();

}


JanelaEscolhaPersonagem::~JanelaEscolhaPersonagem(void)
{
}

void JanelaEscolhaPersonagem::desenhar()
{

	desenharComponentes();
	cursor->desenhar(SceneManager->getVideoDriver());
	if(!alinhouPersonagem)
	{
		Vetor tamanho_personagem = personagemImg->getTamanho();
		personagemImg->atualizarPosisao(Vetor(
			(areaPersonagem.v2.x - tamanho_personagem.x) /2,
			(areaPersonagem.v2.y - tamanho_personagem.y) /2));
		alinhouPersonagem = true;
	}	

	
}

void JanelaEscolhaPersonagem::mudarProximoPersonagem()
{
	if(JanelaEscolhaPersonagem::selecionado<JanelaEscolhaPersonagem::personagens.size()-1)
		JanelaEscolhaPersonagem::selecionado++;
	atualizarPersonagem();
}
void JanelaEscolhaPersonagem::mudarPersonagemAnterior()
{
	if(JanelaEscolhaPersonagem::selecionado>0)
		JanelaEscolhaPersonagem::selecionado--;
	atualizarPersonagem();
}


void JanelaEscolhaPersonagem::atualizarPersonagem()
{
	JanelaEscolhaPersonagem::personagemImg->atualizaImagem(
		JanelaEscolhaPersonagem::personagens[selecionado].img);
		
		
}

void JanelaEscolhaPersonagem::remover()
{
	
}

Mesh_Info JanelaEscolhaPersonagem::getPersonagem()
{
	return personagens[selecionado];	
}