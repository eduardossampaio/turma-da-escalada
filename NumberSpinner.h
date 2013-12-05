#pragma once
#include "tipos.h"
#include "Botao.h"
#include "Label.h"
#include "CliqueListener.h"
#include "Componente.h"
using namespace tipos;
class NumberSpinner : public Componente , public CliqueListener
{
public:
	NumberSpinner(Vetor pos,Vetor tamanho);
	~NumberSpinner();
	
	virtual void desenhar(IVideoDriver * driver) override;
	void setValor(int valor);
	int  getValor();
	void incrementaValor();
	void decrementaValor();
	void onClique(Vetor pos) override;
	void posicaoCaptada(Vetor pos) override;
	int getMinimo();
	void setMinimo(int minimo);
	int getMaximo();
	void setMaximo(int maximo);
	
private:
	Vetor   tamanho;
	Botao * botaoMais;
	Botao * botaoMenos;
	int     valor;
	Label * labelValor;
	bool    alinhado;
	int minimo;
	int maximo;
	
	class BotaoMaisListener : public CliqueListener
	{
	public:
		BotaoMaisListener(NumberSpinner * spinner) : spinner(spinner){}
		void onClique(Vetor pos) override
		{
			printf("incrementa\n");
			spinner->incrementaValor();
		}
		void posicaoCaptada(Vetor pos) override {}
			
	private:
		NumberSpinner * spinner;

	};
	
	class BotaoMenosListener : public CliqueListener
	{
	public:
		BotaoMenosListener(NumberSpinner * spinner) : spinner(spinner){}
		void onClique(Vetor pos) override
		{
			printf("decrementa\n");
			spinner->decrementaValor();
		}
		void posicaoCaptada(Vetor pos) override {}
			
	private:
		NumberSpinner * spinner;

	};

};