#pragma once
#include "janela.h"
#include "interface.h"
#include "GerenciadorDeExibicao.h"
#include "Configuracoes.h"
class JanelaConfiguracao : public Janela
{
public:
	JanelaConfiguracao(void);
	JanelaConfiguracao(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id) ;
	~JanelaConfiguracao(void);
	virtual void desenhar() override;
	tipos::configuracoes getConfiguracoes();
private:
	Imagem   * fundo;
	ComboBox * comboResolucao;
	ComboBox * comboCor;
	ComboBox * comboMao;
	CheckBox * checkFullScreen;
	Label	 * labelResolucao;
	Label	 * labelCor;
	Label	 * labelMao;
	Label    * labelFullScreen;
	Botao	 * botaoSalvar;
	Botao	 * botaoCancelar;
	
	void setarComponentes();
	vector<ComboBox * > combos;

	//listeners

	class BotaoCancelarListener : public CliqueListener
	{
		void onClique(Vetor pos)
		{
			printf("cancelar\n");
			
			GerenciadorDeExibicao::getGerenciador()->removerUltimaJanelaExibida();
		}
		void posicaoCaptada(Vetor pos)
		{

		}

	};

	class BotaoSalvarListener : public CliqueListener
	{
	public:
		JanelaConfiguracao * janela;
		BotaoSalvarListener(JanelaConfiguracao * janela): janela(janela){}

		void onClique(Vetor pos)
		{
			printf("salvar\n");
			(new Configuracoes())-> salvarConfiguracoes( janela->getConfiguracoes() );
			
			
			GerenciadorDeExibicao::getGerenciador()->removerUltimaJanelaExibida();
			
		}

		void posicaoCaptada(Vetor pos)
		{

		}


	};

	Botao * teste;
	
};

