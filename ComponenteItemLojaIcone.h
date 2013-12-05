#pragma once
#include "componente.h"
#include "interface.h"
//#include "JanelaLoja2.h"
class JanelaLoja2 ;
/*
		essa classe é um componente de item da loja na parte de baixo da loja.
		Serve apenas para exibir um icone nas opções de itens e setar o item 
		selecionado	
*/
class ComponenteItemLojaIcone : public Componente , public CliqueListener
{
public:
	ComponenteItemLojaIcone(JanelaLoja2 * janela,Vetor pos,Vetor tamanho,tipos::Item_loja item);
	~ComponenteItemLojaIcone(void);
	virtual void desenhar(IVideoDriver * driver) override;
	virtual void onClique(Vetor pos) override;
	virtual void posicaoCaptada(Vetor pos) override;
private:
		Vetor tamanho;
		tipos::Item_loja item;
		Imagem  * imagem;
		JanelaLoja2 * janela;
		bool alinhado;
};

