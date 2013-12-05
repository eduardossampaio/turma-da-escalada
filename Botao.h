#pragma once
#include "Componente.h"
#include "tipos.h"
#include "Label.h"
#include "CliqueListener.h"
#include "Imagem.h"
#include <iostream>
#include <vector>
using namespace std;
using namespace tipos;

class Botao : public Componente , public CliqueListener
{
public:
	Botao(Vetor posicao,std::string imagem);
	Botao(Vetor posicao,std::string imagem,std::string texto,std::string fonte,TAMANHO tamanho);
	~Botao(void);
	virtual void desenhar(IVideoDriver *driver) override;
	void setTamanho(Vetor tamanho);
	Vetor getTamanho();


	void onClique(tipos::Vetor posicao) override;
	virtual void posicaoCaptada(tipos::Vetor posicao) override;
	void clique(tipos::Vetor pos);

	void addListener(CliqueListener * l);

	//void atualizarPosisao(Vetor pos) override;
	//Vetor getPosisao()override;

private:
	Imagem * imagem;
	bool habilidato;
	Vetor tamanho;
	vector<CliqueListener * > listeners;
	std::string texto;
	bool comTexto;
	Label *label;
};

