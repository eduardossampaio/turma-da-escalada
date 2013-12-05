#pragma once

//#include "JanelaNovoJogo.h"
//#include "JanelaPrincipal.h"

#include "irrlicht.h"
//#include "Janela.h"
#include <iostream>
#include <vector>
#include "tipos.h"

using namespace irr;
using namespace std;



class GerenciadorExibicao2
{

public:
	GerenciadorExibicao2(void);
	~GerenciadorExibicao2(void);
	
	
	
	void novaJanelaExibicao(tipos::JanelaExibicao janela);
	void removerUltimaJanela();

	static GerenciadorExibicao2* getInstancia()
	{
		if(GerenciadorExibicao2::instancia==NULL)
			GerenciadorExibicao2::instancia = new GerenciadorExibicao2();
		return GerenciadorExibicao2::instancia;
	}
	static void setSceneManager(scene::ISceneManager * manager)
	{
		GerenciadorExibicao2::manager = manager;
	}
private:
	
	static GerenciadorExibicao2 * instancia;
	static scene::ISceneManager * manager;
	void iniciarExibicao();
	vector<tipos::JanelaExibicao> janelas;
};

