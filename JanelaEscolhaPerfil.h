#pragma once
#include "janela.h"
#include "tipos.h"
#include "GerenciadorDeExibicao.h"
#include "JanelaEscolhaFase.h"
#include "CaixaMensagemSimNao.h"
#include "Configuracoes.h"

class JanelaEscolhaPerfil : public Janela
{
public:
	JanelaEscolhaPerfil(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);
	~JanelaEscolhaPerfil(void);

	void desenhar();

	bool emExecucao();
	void selecionaProximoPerfil();
	void selecionaPerfilAnterior();
	void excluirPerfil ();
	Save getPerfilSelecionado();
	//static Save saveExclusao; 

	
private:
	Save getSaveSelecionado();
	void carregaValoresSave();
	
	int				indiceSave;
	video::SColor	corFundo;
	video::SColor	corLetra;
	vector<Save>	saves;
	Vetor			tamanhoTela;
	Botao			* botaoProximo;
	Botao			* botaoAnterior;
	Botao			* botaoCarregar;
	Botao			* botaoCancelar;
	Botao			* botaoExcluir;
	Label			* labelNome;
	Label			* labelNomeTexto;
	Label			* labelIdadeTexto;
	Label			* labelIdade;
	Label			* labelSexoTexto;
	Label			* labelSexo;
	Label			* labelPesoTexto;
	Label			* labelPeso;
	Label			* labelPontosTexto;
	Label			* labelPontos;
	ISceneNode		* node;
	Imagem			* fundo;
	Imagem			* personagem;
	tipos::Area		areaPersonagem;
	bool			alinhouPersonagem;
	   
	class ProximoSaveBotaoListener : public CliqueListener
	{
	public:
		 JanelaEscolhaPerfil * janela;
		ProximoSaveBotaoListener( JanelaEscolhaPerfil * janela):janela(janela){}

		void onClique(Vetor pos) override
		{
			printf("proximo save\n");
			janela->selecionaProximoPerfil();
		}
		void posicaoCaptada(Vetor pos) override{}

	};

	class SaveAnteriorBotaoListener : public CliqueListener
	{
	public:
		JanelaEscolhaPerfil * janela;
		SaveAnteriorBotaoListener(JanelaEscolhaPerfil * janela):janela(janela){}

		void onClique(Vetor pos) override
		{
			printf("save anterior\n");
			janela->selecionaPerfilAnterior();
		}
		void posicaoCaptada(Vetor pos) override{}

	};

	class CarregarBotaoListener : public CliqueListener
	{
	public:
		JanelaEscolhaPerfil * janela;
		CarregarBotaoListener(JanelaEscolhaPerfil * janela):janela(janela){}

		void onClique(Vetor pos) override
		{
			printf("carregar save\n");
			GerenciadorDeExibicao::getGerenciador()->novaJanelaParaExibicao(
				new JanelaEscolhaFase(
				janela->getSceneManager()->getRootSceneNode(),janela->getSceneManager(),15,janela->getPerfilSelecionado()));
			
			
		}
		void posicaoCaptada(Vetor pos) override{}

	};
	void setupComponentes3d();
	
	class CancelarBotaoListener : public CliqueListener
	{
	public:
		void onClique(Vetor pos) override
		{
			
			GerenciadorDeExibicao::getGerenciador()->removerUltimaJanelaExibida();
		}

		void posicaoCaptada(Vetor pos) override{}
	};
	//listener chamado quando o jogador clicar
	//em sim
	class BotaoSimListener : public CliqueListener
	{
	private:
		JanelaEscolhaPerfil * janela;
	public:
	
		BotaoSimListener(JanelaEscolhaPerfil * janela):janela(janela){}
		
		
		

		void onClique(Vetor pos) override
		{
			printf("excluindo perfil\n");
			
			janela->excluirPerfil();

		}
		void posicaoCaptada(Vetor pos) override{}

	};

	class ExcluirBotaoListener : public CliqueListener
	{
	private:
		JanelaEscolhaPerfil * janela;
	public:
		ExcluirBotaoListener(JanelaEscolhaPerfil * janela):janela(janela){}
		void onClique(Vetor pos) override
		{
			
			Configuracoes *c = new Configuracoes();
			tipos::configuracoes config = c->carregarConfigucacoes();
			int x1 = config.resolucao.x / 5;
			int y1 = config.resolucao.y / 3;
			int x2 = config.resolucao.x - (x1*2);
			int y2 = config.resolucao.y - (y1*2); 
			CaixaMensagemSimNao * caixa = new CaixaMensagemSimNao(
				Vetor(x1,y1),
				Vetor(x2,y2),
				"Deseja excluir este perfil? ",
				new BotaoSimListener(janela)
				
				);
				
			janela->exibirMensagem(caixa);
		}
		void posicaoCaptada(Vetor pos) override{}
	private:

	};

	class CLicouSimCaixaExcluirListener : public CliqueListener
	{
	private:
		JanelaEscolhaPerfil * janela;
	public:
		CLicouSimCaixaExcluirListener(JanelaEscolhaPerfil * janela):janela(janela){}
		
		void onClique(Vetor pos) override
		{
			PerfilDao * dao = new PerfilDao();
			
			if (dao->carregarPerfis().size() == 0)
				janela->exibirMensagemErro("Nao existem perfis cadastrados",new JanelaEscolhaPerfil::CancelarBotaoListener());
		}
		void posicaoCaptada(Vetor pos) override
		{
		}
		
		
	};
	
};

