#pragma once
#include "Componente.h"
#include <iostream>
using namespace std;
class Imagem : public Componente
{
public:
	Imagem(Vetor posicao,std::string imagem);
	Imagem(std::string imagem);
	~Imagem(void);

	virtual void desenhar(IVideoDriver *driver) override ;
	bool isVisivel();
	void setVisivel(bool visivel);
	Vetor getTamanho();
	void atualizaImagem(std::string nomeImagem);
private:
	bool ativo;
	std::string nomeImagem;
	video::ITexture* images;

};

