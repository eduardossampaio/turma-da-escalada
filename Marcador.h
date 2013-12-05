#pragma once
#include "tipos.h"
#include "Componente.h"
#include "Imagem.h"
#include "CliqueListener.h"
#include "Label.h"
#include "Botao.h"
#include "GerenciadorDeExibicao.h"
#include "JanelaJogo.h"
#include <iostream>
#include <irrlicht.h>
#include "Jogador.h"
#include "JanelaEscolhaFase.h"
using namespace irr;
using namespace scene;

using namespace tipos;
class Marcador : public Componente, public CliqueListener
{
public:
	Marcador(Vetor pos,ISceneManager * mgr,Jogador * jogador,JanelaEscolhaFase * janela);
	~Marcador(void);

	void desenhar(IVideoDriver * driver) override;

	void onClique(Vetor pos) override;
	void posicaoCaptada(Vetor pos) override;

	Vetor posIcone;

private:
	tipos::FaseInfo info;
	Imagem * icone;
	bool emCima;
	bool aberta;
	tipos::configuracoes config;
	//variaveis para o tamanho da caixa
	int margem;
	Vetor inicioCaixa;
	Vetor fimCaixa;
	Jogador * jogador;


	//labels
	Label * nomeFase;
	Label * localizacaoLabel;
	Label * localizacaoTexto;
	Label * informacoes;
	Label * fauna;
	Label * flora;
	Botao * botao;

	class BotaoJogarListener : public CliqueListener
	{
	private :
		Fase_Dados dados;
		ISceneManager * mgr;
		Jogador * jogador;
		JanelaEscolhaFase * janela;
	public:
		BotaoJogarListener(ISceneManager * mgr,Fase_Dados dados,Jogador * jogador,JanelaEscolhaFase * janela):dados(dados),mgr(mgr),jogador(jogador),janela(janela) {}
		void onClique(Vetor pos) override
		{
			
			if(! jogador->getInventario()->contemTipoItem(tipos::tipo_item::CAPACETE))
			{
				
				janela->exibirErro("voce nao pode escalar\nsem capacete");
			}
			else if(! jogador->getInventario()->contemTipoItem(tipos::tipo_item::CORDA))
			{
				janela->exibirErro("voce nao pode escalar\nsem corda");
			}
			else if (! jogador->getInventario()->contemTipoItem(tipos::tipo_item::MAGNESIO))
			{
				janela->exibirErro("voce nao pode escalar\nsem magnesio");
			}
			else if (! jogador->getInventario()->contemTipoItem(tipos::tipo_item::MOSQUETAO))
			{
				janela->exibirErro("voce nao pode escalar\nsem mosquetao");
			}
			else if(! jogador->getInventario()->contemTipoItem(tipos::tipo_item::CADEIRINHA))
			{
				janela->exibirErro("voce nao pode escalar\nsem cadeirinha");
			}
			else if(! jogador->getInventario()->contemTipoItem(tipos::tipo_item::SAPATILHA))
			{
				janela->exibirErro("voce nao pode escalar\nsem sapatilha");
			}
			else
			{				
				printf("tem tudo\n");
				GerenciadorDeExibicao::getGerenciador()->novaJanelaParaExibicao(new JanelaJogo(mgr->getRootSceneNode(),mgr,0,dados));
			}
		}
		void posicaoCaptada(Vetor pos) override
		{

		}
	};
};

