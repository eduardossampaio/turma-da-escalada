#pragma once
#include "componente.h"
#include "Componente.h"
#include "Botao.h"
#include "Label.h"
#include "Imagem.h"
#include "NumberSpinner.h"
#include "tipos.h"
//define a percentagem onde termina a exibição da image e começa a exibição dos componentes
#define PORCENTAGEM_X 0.3
#define PORCENTAGEM_Y 0.25
using namespace tipos;
class ItemLoja : public Componente , public CliqueListener
{
public:	
	ItemLoja(Vetor posicao,Vetor tamanho,tipos::Item_loja itemLoja);
	~ItemLoja();

	virtual void desenhar(IVideoDriver * driver) override;
	virtual void onClique(Vetor pos) override;
	virtual void posicaoCaptada(Vetor pos) override;
	void atualizarTamanho(Vetor pos);
	
	tipos::Item_loja getItem();
private:
	bool			   alinhado;
	Vetor			   tamanho;
	tipos::Item_loja   item;
	Botao    		 * botaoComprar;
	Imagem	 		 * imagemItem;
	Label    		 * labelNome;
	Label    		 * labelQuantidade;
	Label    		 * labelTotal;
	NumberSpinner  	 * spinner;
	vector<Componente *> componentes;
	

	class BotaoComprarListener : public CliqueListener
	{
	public: 
		
		BotaoComprarListener(ItemLoja * itemloja)
		{
			BotaoComprarListener::itemLoja = itemloja;
		}
		
		void onClique(Vetor pos) override
		{
			printf("conprando: %d %s\n",0,this->itemLoja->getItem().descricao.c_str());
		}
		void posicaoCaptada(Vetor pos) override
		{

		}
	private:
		ItemLoja * itemLoja;

	};


};