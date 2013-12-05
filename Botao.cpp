#include "stdafx.h"
#include "Botao.h"
#include "Imagem.h"
bool primeiroT;
Botao::Botao(Vetor posicao,string imagem):Componente(posicao)
{
	habilitar(true);
	Botao::imagem = new Imagem( posicao,imagem);
	Botao::tamanho = Botao::imagem->getTamanho();
	Botao::comTexto = false;
}

Botao::Botao(Vetor posicao,std::string imagem,std::string texto,std::string fonte,TAMANHO tamanho):Componente(posicao)
{
	habilitar(true);
	Botao::imagem = new Imagem( posicao,imagem);
	Botao::tamanho = Botao::imagem->getTamanho();
	Botao::comTexto = true;
	Botao::label = new Label(posicao,Botao::tamanho,texto,fonte,tamanho,true,true);
}



Botao::~Botao(void)
{
}

void Botao::desenhar(IVideoDriver *driver)
{	
	imagem->atualizarPosisao(getPosisao());
	imagem->desenhar(driver);
	Botao::tamanho=imagem->getTamanho();		
	if(comTexto){
		Botao::label->atualizarPosisao(getPosisao());
		Botao::label->setTamanho(tamanho);
		Botao::label->desenhar(driver);
	}
}



void Botao::setTamanho(Vetor tamanho)
{
	Botao::tamanho = tamanho;
}
Vetor Botao::getTamanho()
{
	return Botao::tamanho;
}
void Botao::onClique(tipos::Vetor v)
{
	if( (v.x>= this->posicao.x && v.x<= (this->tamanho.x + this->posicao.x ) ) && (v.y>= this->posicao.y && v.y<= (this->tamanho.y + this->posicao.y )  ) ){
		clique(v);
	}
}
	

void Botao::clique(Vetor v)
{
	printf("clicou\n");
	for(int i=0 ; i<Botao::listeners.size(); i++){
		Botao::listeners[i]->onClique(v);
	}
	
}
void Botao::addListener(CliqueListener * l)
{
	Botao::listeners.push_back(l);
}

void Botao::posicaoCaptada(Vetor pos)
{

}