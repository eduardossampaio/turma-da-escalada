#pragma once
#include "Movimento.h"
#include "tipos.h"
#include "Cronometro.h"


class IdentificadorMovimento
{
public:
	IdentificadorMovimento(void);
	//IdentificadorMovimento(Movimento * movimentos...);
	~IdentificadorMovimento(void);
	
	
	void adicionarMovimento(Movimento * movimento,float tempo);
	EstadoCaptura capturarMovimento(Esqueleto esqueleto);
private:
	typedef struct mv{
		mv(Movimento * movimento_,float tempo_) : movimento(movimento_), tempo(tempo_)
		{}
		Movimento * movimento;
		float		tempo;
	}MovimentoItem;

	vector<MovimentoItem> itens;
	EstadoCaptura verificaEstadoPosicao(Esqueleto e);

	
	int indexAtual;
	Cronometro cronometro;
};

