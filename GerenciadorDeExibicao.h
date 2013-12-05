#pragma once
#include "Janela.h"
//#include "GerenciadorExibicao2.h"

class GerenciadorExibicao2;

typedef struct t_janela
{
	t_janela(Janela * janela):janela(janela),proximo(NULL)
	{}
	struct t_janela * proximo;
	Janela * janela;
}Janela_cel;


class GerenciadorDeExibicao
{
public:
	GerenciadorDeExibicao(void);
	~GerenciadorDeExibicao(void);

	void novaJanelaParaExibicao(Janela *janela);
	Janela * getProximaJanela();
	void removerUltimaJanelaExibida();
	Janela * getJanelaAtual();

	static GerenciadorDeExibicao * getGerenciador();
	GerenciadorExibicao2 * getGerenciador2();
	void solicitaSairDoJogo();
	bool sairDoJogo();

private :
	static GerenciadorDeExibicao * instancia;
	
	Janela * proximaJanela;
	Janela * antigaJanela;
	
	Janela_cel * ultima;
	Janela_cel * lista;
	Janela_cel * getUltimaJanelaCel();

	vector<Janela *> janelas;
	bool sair;
};


