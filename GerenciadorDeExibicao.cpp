#include "stdafx.h"
#include "GerenciadorDeExibicao.h"
#include "GerenciadorExibicao2.h"
GerenciadorDeExibicao * GerenciadorDeExibicao::instancia = NULL;


GerenciadorDeExibicao::GerenciadorDeExibicao(void)
{
        lista = NULL;
		sair = false;
}


GerenciadorDeExibicao::~GerenciadorDeExibicao(void)
{
}

GerenciadorDeExibicao * GerenciadorDeExibicao::getGerenciador()
{
        if(GerenciadorDeExibicao::instancia == NULL)
                GerenciadorDeExibicao::instancia = new GerenciadorDeExibicao();
        return GerenciadorDeExibicao::instancia;
}

void GerenciadorDeExibicao::novaJanelaParaExibicao(Janela *janela)
{
	Janela * janela_atual = getJanelaAtual();
	if(janela_atual!=NULL)
		janela_atual->setVisible(false);
	GerenciadorDeExibicao::janelas.push_back(janela);
        
}
GerenciadorExibicao2 * GerenciadorDeExibicao::getGerenciador2()
{
  return GerenciadorExibicao2::getInstancia();
}
Janela * GerenciadorDeExibicao::getJanelaAtual()
{
	if(GerenciadorDeExibicao::janelas.size()>0)
		return GerenciadorDeExibicao::janelas[GerenciadorDeExibicao::janelas.size()-1];
	return NULL;
}
void GerenciadorDeExibicao::removerUltimaJanelaExibida()
{
	if(GerenciadorDeExibicao::janelas.size()>0)
	{
		Janela * janela = GerenciadorDeExibicao::janelas[GerenciadorDeExibicao::janelas.size()-1];
		janela->setVisible(false);
		
		GerenciadorDeExibicao::janelas.pop_back();
		
	}
}

Janela * GerenciadorDeExibicao::getProximaJanela()
{
	return GerenciadorDeExibicao::getJanelaAtual();
}

void GerenciadorDeExibicao::solicitaSairDoJogo()
{
	sair = true;
}
bool GerenciadorDeExibicao::sairDoJogo()
{
	return GerenciadorDeExibicao::sair;
}