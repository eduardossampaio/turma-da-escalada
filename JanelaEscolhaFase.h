#pragma once
#include "janela.h"
#include "interface.h"

#include "tipos.h"
#include "GerenciadorDeExibicao.h"
#include "Jogador.h"
#include "JanelaLoja2.h"
class Marcador;
class JanelaEscolhaFase :
	public Janela
{
public:
	JanelaEscolhaFase(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id,tipos::Save perfil);
	~JanelaEscolhaFase(void);

	void desenhar() override;
	bool emExecucao() override;
	tipos::Save getPerfil();
	Jogador * getJogador();
	void exibirErro(std::string msg);
private:
	Imagem * fundo;
	Botao  * botaoJogar;
	Botao  * botaoLoja;
	Botao  * botaoVoltar;
	Marcador * marcador;
	tipos::Save perfil;
	Jogador * jogador;
	class BotaoLojaListener : public CliqueListener{
	private:
		JanelaEscolhaFase * janela;

	public:
		BotaoLojaListener(JanelaEscolhaFase * janela) : janela(janela) {}
		void onClique(Vetor pos ) override
		{
			printf("indo pra loja gastar dinheiro\n");
			GerenciadorDeExibicao::getGerenciador()->novaJanelaParaExibicao(
				new JanelaLoja2(
					janela->getJogador(), 
					janela->getSceneManager()->getRootSceneNode(),
					janela->getSceneManager(),10));
			
		}
		void posicaoCaptada(Vetor pos) override
		{

		}
	};

	class BotaoVoltarListener : public CliqueListener{
	public:
		void onClique(Vetor pos ) override
		{
			printf("voltando\n");
			GerenciadorDeExibicao::getGerenciador()->removerUltimaJanelaExibida();
		}
		void posicaoCaptada(Vetor pos) override
		{

		}
	};

};

