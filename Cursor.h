#pragma once
#include "tipos.h"
#include "Componente.h"
#include "CliqueListener.h"
#include <iostream>
#include <vector>
using namespace std;
class Cursor
{
protected:
	tipos::Vetor posicao;
	Componente *icone;
	vector<CliqueListener *> listeners;
	


public:
	Cursor(void);
	~Cursor(void);
	virtual void atualizar() =0;
	tipos::Vetor getPosicao() ;
	void setPosicao(tipos::Vetor pos);
	void adicionarListener(CliqueListener *listener);
	void removerListener(CliqueListener * listener);
	Componente * getIcone();
	void desenhar(IVideoDriver * driver);
	vector<CliqueListener *> getListeners();

	
	

};

