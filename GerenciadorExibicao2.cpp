#include "stdafx.h"
#include "GerenciadorExibicao2.h"
#include "tipos.h"
#include "Janela.h"
#include "JanelaNovoJogo.h"
#include "JanelaPrincipal.h"
using namespace tipos;
GerenciadorExibicao2* GerenciadorExibicao2::instancia = NULL;
scene::ISceneManager* GerenciadorExibicao2::manager = NULL;
GerenciadorExibicao2::GerenciadorExibicao2(void)
{
}


GerenciadorExibicao2::~GerenciadorExibicao2(void)
{
}

void GerenciadorExibicao2::novaJanelaExibicao(JanelaExibicao janela)
{
	GerenciadorExibicao2::janelas.push_back(janela);
	iniciarExibicao();
}


void GerenciadorExibicao2::removerUltimaJanela()
{
	janelas.pop_back();
	iniciarExibicao();
}

void GerenciadorExibicao2::iniciarExibicao()
{
	
	Janela * janela=NULL;
	manager->getRootSceneNode()->removeAll();
	

	switch(GerenciadorExibicao2::janelas[GerenciadorExibicao2::janelas.size()-1])
	{
	case JanelaExibicao::Intro_Scene:
		janela=new IntroScene(manager->getRootSceneNode(),manager,0);
		break;
	case JanelaExibicao::Janela_Principal:
		janela=new JanelaPrincipal(manager->getRootSceneNode(),manager,1);
		break;
	case JanelaExibicao::Janela_Novo_Jogo:
		janela=new JanelaNovoJogo(manager->getRootSceneNode(),manager,2);
		break;
	case JanelaExibicao::Janela_Configuracao:
		janela=new JanelaConfiguracao(manager->getRootSceneNode(),manager,3);
		break;
	case JanelaExibicao::Janela_Escolha_Perfil:
		janela=new JanelaEscolhaPerfil(manager->getRootSceneNode(),manager,4);
		break;
	case JanelaExibicao::Janela_Escolha_Personagem:
		//janela=new JanelaEscolhaPersonagem(Perfil,manager->getRootSceneNode(),manager,5);
		break;
	}

	if(janela!=NULL)
	{
		janela->iniciar();
	}
	

}
