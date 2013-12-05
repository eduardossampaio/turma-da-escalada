#pragma once
#include "janela.h"
#include "interface.h"
#include "tipos.h"
#include "Conversoes.h"
#include "Jogador.h"
#include "PerfilDao.h"
#include "ComponenteItemLojaIcone.h"
#include "ComponenteItemLojaIconeVazio.h"
#include "ComponenteItemLojaSelecionado.h"
#include "CaixaVendaItem.h"
class ComponenteInformacoesJogador;
class JanelaLoja2 : public Janela
{
public:
	JanelaLoja2(Jogador * jogador,scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);
	~JanelaLoja2(void);

	virtual void desenhar() override;
	
	void setItemSelecionado(tipos::Item_loja item);
	tipos::Item_loja getItemSelecionado();
	int getQuatidadeItem();
	
	void comprarItem(tipos::Item_loja,int qtd);
	void venderItem(tipos::Item_loja,int qtd);
	void adicionarListener(CliqueListener * listener);

	void solicitaVendaPerfil();
	void solicitaCompraItem(tipos::Item_loja,int qtd);
private:

	
	

	
	class BotaoComprarListener: public CliqueListener
	{
	public:
		BotaoComprarListener(JanelaLoja2 * janela):janela(janela){}
		virtual void onClique(Vetor pos) override
		{
			janela->comprarItem(janela->getItemSelecionado(),janela->getQuatidadeItem());
		}
		virtual void posicaoCaptada(Vetor pos) override{}
	private:
		JanelaLoja2 * janela;
	};
	
	
	
	//listeners dos botões
	class BotaoProximoItemListener : public CliqueListener
	{
	public:
		BotaoProximoItemListener(JanelaLoja2 * janela):janela(janela){}
		virtual void onClique(Vetor pos) override
		{
			printf("indo para o próximo item\n");
			janela->proximoPaginaItens();
		}
		virtual void posicaoCaptada(Vetor pos) override{}
	private:
		JanelaLoja2 * janela;
	};

	class BotaoItemAnteriorListener : public CliqueListener
	{
	public:
		BotaoItemAnteriorListener(JanelaLoja2 * janela):janela(janela){}
		
		virtual void onClique(Vetor pos) override
		{
			printf("indo para o próximo anterior\n");
			janela->paginaAnteriorItens();
		}
		virtual void posicaoCaptada(Vetor pos) override{}
	private:
		JanelaLoja2 * janela;
	};

	class VenderItemListener : public CliqueListener
	{
	public:
		VenderItemListener(JanelaLoja2 * janela,CaixaVendaItem * caixa):janela(janela),caixa(caixa){}
		
		virtual void onClique(Vetor pos) override
		{
			tipos::Item_loja item = janela->getItemSelecionado();
			int quantidade = caixa->getQuantidadeSelecionada();
			janela->venderItem(item,quantidade);

		}
		virtual void posicaoCaptada(Vetor pos) override{}
	private:
		JanelaLoja2 * janela;
		CaixaVendaItem * caixa;
	};

	

	//atributos privados da classe JanelaLoja2
	vector<tipos::Item_loja>				itens;
	tipos::Item_loja 						item_selecionado;
	Imagem									* imagemSelecionado;
	Vetor 									inicioAreaImagem;	
	Vetor				 					fimAreaImagem;
	int										itens_inicio;
	int										itens_fim;
	bool									alinhouImagem;
	bool									alinhouBotoes;
	vector<ComponenteItemLojaIcone		*> 	icones_itens;
	vector<ComponenteItemLojaIconeVazio *> 	icones_vazios;			
	ComponenteItemLojaSelecionado			* itemSelecionado;
	ComponenteInformacoesJogador			* informacoesJogador;
	tipos::Area								area_botao_voltar;
	tipos::Area								area_botao_proximo;
	tipos::Area								areaDadosItem;
	tipos::Area								areaDadosJogador;
	Botao									*botaoProximo;
	Botao									*botaoAnterior;
	Jogador									*jogador;
	vector<Vetor> obterCoordenadasIcones(Vetor inicio,Vetor fim);
	vector<Vetor> coordenadasIcones;
		
	void selecionarItensParaExibicao();
	void proximoPaginaItens();
	void paginaAnteriorItens();

	

};

