#pragma once



#include "Janelas.h"
#include "irrlicht.h"
#include "JanelaEscolhaPerfil.h"
#include "GerenciadorExibicao2.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class JanelaPrincipal : public Janela
{
public:
	JanelaPrincipal(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);
	~JanelaPrincipal(void);

	void desenhar() override ;
	virtual bool emExecucao() override;
private:
	Imagem * fundo;
	Botao * botoes[4];
	

	
	/*
		listener para novo botao novo jogo
	*/
	class NovoJogoListener : public CliqueListener{
	private:
		ISceneManager * manager;
	public:
		NovoJogoListener(ISceneManager * manager):manager(manager){}
		void onClique(Vetor v) {
			printf("clicou novo jogo\n");
			GerenciadorDeExibicao::getGerenciador()->novaJanelaParaExibicao(new JanelaNovoJogo());
			
			
		}
		virtual void posicaoCaptada(tipos::Vetor posicao) override{}
	};
	/*
		listener para novo botao carregar
	*/
	class CarregarListener : public CliqueListener{
	private:
		ISceneManager * manager;
	public:
		CarregarListener(ISceneManager * manager):manager(manager){}
		void onClique(Vetor v) {
			printf("clicou carregar\n");
			
			GerenciadorDeExibicao::getGerenciador()->novaJanelaParaExibicao(new JanelaEscolhaPerfil(manager->getRootSceneNode(),manager,15));
			//GerenciadorExibicao2::getInstancia()->novaJanelaExibicao(JanelaExibicao::Janela_Escolha_Perfil);
		}
		virtual void posicaoCaptada(tipos::Vetor posicao) override{}
	};
	/*
		listener para novo botao configurar
	*/
	class ConfigurarListener : public CliqueListener{
	private:
		ISceneManager * manager;
	public:
		ConfigurarListener(ISceneManager * manager):manager(manager){}
	
		void onClique(Vetor v) {
			printf("clicou configurar\n");
			GerenciadorDeExibicao::getGerenciador()->novaJanelaParaExibicao(new JanelaConfiguracao(manager->getRootSceneNode(),manager,14));
			//GerenciadorExibicao2::getInstancia()->novaJanelaExibicao(JanelaExibicao::Janela_Configuracao);
		}
		virtual void posicaoCaptada(tipos::Vetor posicao) override{}
	};
	/*
		listener para novo botao sair
	*/
	class SairListener : public CliqueListener{

		void onClique(Vetor v) {
			printf("clicou sair\n");
			GerenciadorDeExibicao::getGerenciador()->solicitaSairDoJogo();
		}
		virtual void posicaoCaptada(tipos::Vetor posicao) override{}
	};

};
