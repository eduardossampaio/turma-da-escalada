#pragma once
#include "componente.h"
#include "tipos.h"
#include <iostream>
#include "Globais.h"
#include "irrlicht.h"

using namespace irr;
using namespace gui;
using namespace std;
using namespace tipos;

enum TAMANHO{
	PEQUENO,
	MEDIO,
	GRANDE
};
class Label : public Componente
{
public:
	Label(Vetor posicao,std::string texto);
	Label(Vetor posicao,Vetor tamanho,std::string texto,std::string fonte,TAMANHO tamanhoFonte);
	Label(Vetor posicao,Vetor tamanho,std::string texto,std::string fonte,TAMANHO tamanhoFonte,bool centralizaHorizontal,bool centralizaVertical);
	Label(Vetor posicao,Vetor tamanho,std::string texto,std::string fonte,TAMANHO tamanhoFonte,bool centralizaHorizontal,bool centralizaVertical,std::string corFonte);
	~Label(void);
	static void setGui(gui::IGUIEnvironment * gui)
	{
		env=gui;

	}
	void	setTexto(std::string texto);
	std::string	getTexto();
	void    setTamanho(Vetor tamanho);
	Vetor   getTamanho();
	void	setCor(SColor cor);
	SColor	getCor();
	virtual void desenhar(IVideoDriver * driver) override;
	void setTamanhoFonte(TAMANHO tamanho);
private:
	Vetor tamanho;
	std::string getCaminhoFonte(std::string fonte,TAMANHO tamanho);
	std::string  texto;
	std::string  fonte;

	bool	centralizaHorizontal;
	bool	centralizaVertical;
	gui::IGUIFont * font ;
	SColor cor;
protected:
	static gui::IGUIEnvironment *env;
};

