#pragma once
#include "Componente.h"
#include "tipos.h"
#include "Editavel.h"
#include "Tecla.h"
#include <iostream>
#include <vector>
#include "CliqueListener.h"


#define TECLADO_MARGEM_X 10
#define TECLADO_MARGEM_Y 10

using namespace std;



class TecladoVirtual : public Componente , public CliqueListener
{
public:
	TecladoVirtual(Vetor v);
	~TecladoVirtual(void);
	void setAlvo(Editavel * alvo);
	Editavel * getAlvo();
	virtual bool emCimaDoTeclado(Vetor pos)=0;
	virtual void desenhar(IVideoDriver * driver) override;
	virtual void onClique(Vetor pos) override;
	
	virtual void posicaoCaptada(tipos::Vetor posicao) override;
protected:
	Editavel * alvo;
	vector<Tecla*> teclas;

	float larguraTecla;
	float alturaTecla;

	float altura;
	float largura;

	int qtdX;
	int qtdY;

	enum Comportamento
	{
		LETRA,
		BACKSPACE,
		SHIFT,
		GENERO
		
	};

	void criarTecla(std::string texto,int x,int y,int tamanho,Comportamento c);
	
};

