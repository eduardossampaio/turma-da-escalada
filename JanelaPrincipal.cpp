#include "stdafx.h"

#include "KinectCursor.h"

#include "Janelas.h"
#include "interface.h"

#include <iostream>
using namespace std;
using namespace irr;
using namespace scene;


#include "CaixaMensagemSimNao.h"
#include "CaixaVendaItem.h"



JanelaPrincipal::JanelaPrincipal(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id) : Janela(parent,mgr,id)
{
	

	JanelaPrincipal::fundo = new Imagem(Vetor(),"ui/janela/turma-escalada.png");
	int x=160;
	Botao * novoJogo   = new Botao(Vetor(10,490+x),"ui/botoes/em-branco-normal.png","NOVO JOGO","comic",PEQUENO);
	Botao * carregar   = new Botao(Vetor(270,490+x),"ui/botoes/em-branco-normal.png","CARREGAR","comic",PEQUENO);
	Botao * configurar = new Botao(Vetor(530,490+x),"ui/botoes/em-branco-normal.png","CONFIGURAR","comic",PEQUENO);
	Botao * sair	   = new Botao(Vetor(790,490+x),"ui/botoes/em-branco-normal.png","SAIR","comic",PEQUENO);
	
	cursor = new KinectCursor();

	botoes[0]=novoJogo;
	botoes[1]=carregar;
	botoes[2]=configurar;
	botoes[3]=sair;
	

	
	ISceneManager * m_listener = NULL;
	novoJogo->addListener(new NovoJogoListener(SceneManager));
	carregar->addListener(new CarregarListener(SceneManager));
	configurar->addListener(new ConfigurarListener(SceneManager));
	sair->addListener(new SairListener());

	componentes.push_back(fundo);
	for(int i=0;i<4;i++)
	{
		botoes[i]->setTamanho(Vetor(249,42));
		cursor->adicionarListener(botoes[i]);
		componentes.push_back(botoes[i]);
	}
	
	
	//retirarFocoComponentes();
	//Janela::exibirMensagemSimples("Olá");
	//Janela::exibirMensagemErro("deu merda");

	Configuracoes * dao = new Configuracoes();
		tipos::configuracoes config = dao->carregarConfigucacoes();
		
		int x1 = config.resolucao.x / 5;
		int y1 = config.resolucao.y / 3;
		int x2 = config.resolucao.x - (x1*2);
		int y2 = config.resolucao.y - (y1*2); 

		class SimListener : public CliqueListener
		{
		public:
			virtual void onClique(Vetor pos) override
			{
				printf("clicou sim\n");
			}
			virtual void posicaoCaptada(Vetor pos) override
			{

			}
		};
		class NaoListener : public CliqueListener
		{
		public:
			virtual void onClique(Vetor pos) override
			{
				printf("clicou nao\n");
			}
			virtual void posicaoCaptada(Vetor pos) override
			{

			}
		};

		
}


JanelaPrincipal::~JanelaPrincipal(void)
{
}


void JanelaPrincipal::desenhar()
{

	desenharComponentes();
	cursor->desenhar(SceneManager->getVideoDriver());

	
}

bool JanelaPrincipal::emExecucao()
{
	return IsVisible;
}

