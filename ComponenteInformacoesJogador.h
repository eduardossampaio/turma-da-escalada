#pragma once
#include "componente.h"
#include "Jogador.h"
#include "interface.h"
#include "PerfilDao.h"
#include "GerenciadorDeExibicao.h"
#include "JanelaLoja2.h"
class ComponenteInformacoesJogador :public Componente
{
public:
	ComponenteInformacoesJogador(Vetor posicao,Vetor tamanho,Jogador * jogador,JanelaLoja2 *loja);
	~ComponenteInformacoesJogador(void);

	void desenhar(IVideoDriver * driver) override;

	void atualizarDados();

	Botao * getBotaoSair();
	Botao * getBotaoVender();
private:
	Vetor tamanho;
	Jogador * jogador;
	Area areaMoedas;
	Area areaMochila;
	Area areaBotaoSair;
	Imagem	* moedaImagem;
	Imagem	* mochilaImagem;
	Botao	* botaoSair;
	Botao   * botaoVender;
	Label	* labelMoeda;
	Label	* labelMochila;
	bool alinhou;
	JanelaLoja2 *loja;

	class VoltarListener : public CliqueListener
	{

	public:

		void onClique(Vetor pos) override
		{
			GerenciadorDeExibicao::getGerenciador()->removerUltimaJanelaExibida();

		}
		void posicaoCaptada(Vetor pos) override
		{

		}
	};
	class VenderListener: public CliqueListener
	{
	public:
		VenderListener(Jogador * jogador,JanelaLoja2 * janela):jogador(jogador),janela(janela){}
		void onClique(Vetor pos) override
		{
			//janela->comprarItem(janela->getItemSelecionado(),janela->getQuatidadeItem());
			janela->solicitaVendaPerfil();

		}
		void posicaoCaptada(Vetor pos) override
		{

		}

	private:
		Jogador * jogador;
		JanelaLoja2 * janela;
	};

	
};

