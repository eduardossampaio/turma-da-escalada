#pragma once
#include "componente.h"
#include <iostream>
#include "Editavel.h"
#include "CliqueListener.h"
#include "CalculosUteis.h"
#include "Globais.h"
#include "Label.h"

class ComportamentoTecla;

using namespace std;
class Tecla :public Componente, public  CliqueListener
{
public:
	Tecla(Vetor pos,Vetor tamanho);
	Tecla(std::string texto,Vetor pos,Vetor tamanho);
	~Tecla(void);

	virtual void desenhar(IVideoDriver * driver) override;
	virtual void onClique(Vetor pos) override;
	virtual void posicaoCaptada(Vetor pos) override;

	void setTexto(std::string texto);
	std::string getTexto();
//	CliqueListener * getListener();
//	void setListener(CliqueListener * listener);
	
	
	Vetor getTamanho();
	Editavel * getAlvo();
	void setAlvo(Editavel * alvo);
	
	void setComportamento(ComportamentoTecla * comportamento);
	ComportamentoTecla * getComportamento();

private:
	std::string texto;
	Editavel * alvo;
	Vetor tamanho;
	//CliqueListener * listener;
	ComportamentoTecla * comportamento;	
	Label * labelTexto;

};




class ComportamentoTecla 
{
public:
	virtual void executarAcaoTecla(Editavel * alvo) =0;

};


class ComportamentoLetra : public ComportamentoTecla
{
public:
	//ComportamentoLetra(std::string  letra):letra(letra)
	ComportamentoLetra(Tecla * tecla):tecla(tecla)
	{
	}
	virtual void executarAcaoTecla(Editavel * alvo) override
	{
		//alvo->addTexto(letra);
		if(alvo)
		{
			alvo->addTexto(tecla->getTexto());
			printf("%s\n",alvo->getTexto().c_str());
		}
	}
private:
	//std::string  letra;
	Tecla * tecla;
};

class ComportamentoShift : public ComportamentoTecla
{
	
public:
	ComportamentoShift(vector<Tecla *> * teclas):teclas(teclas)
	{
	}
	virtual void executarAcaoTecla(Editavel * alvo) override
	{
		for(int i=0;i<teclas->size();i++)
		{
			if(CalculosUteis::stringTodaEmMaiusculo((*teclas)[i]->getTexto()))
				(*teclas)[i]->setTexto(CalculosUteis::transformaStringMinusculo((*teclas)[i]->getTexto()));
			else
				(*teclas)[i]->setTexto(CalculosUteis::transformaStringMaisuculo((*teclas)[i]->getTexto()));
		}
	}
	void setTeclas(vector<Tecla*> * teclas)		
	{
		ComportamentoShift::teclas = teclas;
	}
private:
	vector<Tecla *> * teclas;
};

class ComportamentoBackSpace : public ComportamentoTecla
{
public:
	virtual void executarAcaoTecla(Editavel * alvo) override
	{
		if(alvo->getTexto().length()>0)
		{
			std::string texto = alvo->getTexto();
			std::string novo =texto.substr(0,texto.length()-1);
			//printf("%s\n",texto.c_str());
			alvo->setTexto(novo);
		}
			
	}

};

class ComportamentoGenero : public ComportamentoTecla
{
public:
	ComportamentoGenero(Tecla *tecla):tecla(tecla){}
	
	virtual void executarAcaoTecla(Editavel * alvo) override
	{
		alvo->setTexto(tecla->getTexto());
	}
private:
	Tecla * tecla;
};