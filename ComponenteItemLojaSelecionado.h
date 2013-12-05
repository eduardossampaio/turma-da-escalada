#pragma once
#include "Componente.h"
#include "CliqueListener.h"
#include "interface.h"
class JanelaLoja2;
/*
		classe de componente para o item selecionado,Irá mostrar as informações do
		item que o usuário escolheu na tela. A partir dele que o jogador irá comprar
		
*/
class ComponenteItemLojaSelecionado : public Componente , public CliqueListener
{
public:
	ComponenteItemLojaSelecionado(JanelaLoja2 * janela,Vetor pos,Vetor tamanho) ;
	~ComponenteItemLojaSelecionado(void);

	virtual void desenhar(IVideoDriver * driver) override;

	virtual void onClique(Vetor pos) override;
	virtual void posicaoCaptada(Vetor pos) override;

	void setItemSelecionado(tipos::Item_loja item);
	void atualizaItemSelecionado();
	tipos::Item_loja getItem();
	int getQuantidade();


	private:
		tipos::Item_loja  item;
		JanelaLoja2 	* janela;
		Vetor	tamanho;
		Vetor	areaBotaoInicio;
		Vetor	areaBotaoFim;
		bool	alinhouBotao ;
		/*-----------------------------------*/

		Label			* informacoes;     
		Label			* labelQtdeTexto;
		NumberSpinner	* qtdeSpinner;
		Botao			* botaoComprar;
		
		
};

