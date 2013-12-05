#pragma once
#include "janela.h"
#include "interface.h"
#include "tipos.h"
#include "ItemLoja.h"
class JanelaLoja : public Janela
{
public:
	JanelaLoja(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);
	~JanelaLoja(void);

	void desenhar() override;
	bool emExecucao() override;
private:
	Imagem *fundo;
	Botao *botaoTeste;
	vector<tipos::Item_loja> itensLoja;
	// Contexto local. A classe abaixo n�o sabe nada da classe acima (m�todos e atributos).
	class botaoTesteListener: public CliqueListener{//eventos do bot�o
	public:
		virtual void onClique(tipos::Vetor posicaoCaptada) override {
			printf("clicou");
		} 
		virtual void posicaoCaptada (tipos::Vetor posicaoCaptada) override {
		
		
		} 
	
	};

	

};

