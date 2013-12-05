#include "stdafx.h"
#include "Label.h"
#include <Irrlicht.h>
#include "MouseSensor.h"
#include "Conversoes.h"



gui::IGUIEnvironment * Label::env = NULL;

Label::Label(Vetor posicao,string texto):Componente(posicao)
{
	Label::texto = texto;
	//rever isso aqui
	font = env->getFont("media/fontes/myfont.xml");
	centralizaHorizontal = false;
	centralizaVertical	 = false;
	foiHabilitado = true;
	cor=SColor(255,245,245,245); // cor preta
}

Label::Label(Vetor posicao,Vetor tamanho,string texto,string fonte,TAMANHO tamanhoFonte):Componente(posicao)
{
	Label::texto = texto;
	Label::tamanho = tamanho;
	Label::fonte = fonte;
	std::string caminhoFonte = getCaminhoFonte(fonte,tamanhoFonte);		
	font = env->getFont(caminhoFonte.c_str());
	centralizaHorizontal = false;
	centralizaVertical	 = false;
	cor=SColor(255,0,0,0); // cor preta

}
Label::Label(Vetor posicao,Vetor tamanho,string texto,string fonte,TAMANHO tamanhoFonte,bool centralizaHorizontal,bool centralizaVertical):Componente(posicao)
{
	Label::texto = texto;
	Label::tamanho = tamanho;
	std::string caminhoFonte = getCaminhoFonte(fonte,tamanhoFonte);		
	font = env->getFont(caminhoFonte.c_str());
	Label::centralizaHorizontal = centralizaHorizontal;
	Label::centralizaVertical	 = centralizaVertical;
	cor=SColor(255,0,0,0); // cor preta
	
	Label::fonte = fonte;
}
// A cor é passada como string formada pelo codigo hexadecimal. Exemplo : 000000000
Label::Label(Vetor posicao,Vetor tamanho,string texto,string fonte,TAMANHO tamanhoFonte,bool centralizaHorizontal,bool centralizaVertical,string corFonte):Componente(posicao)
{
	Label::texto = texto;
	Label::tamanho = tamanho;
	std::string caminhoFonte = getCaminhoFonte(fonte,tamanhoFonte);		
	font = env->getFont(caminhoFonte.c_str());
	Label::centralizaHorizontal = centralizaHorizontal;
	Label::centralizaVertical	 = centralizaVertical;
	//cor=SColor(255,0,0,0); // cor preta
	if (corFonte.length() == 9) { // Protecao
		cor=SColor(255,Conversoes::converteParaInt(corFonte.substr(0,3)),
		Conversoes::converteParaInt(corFonte.substr(3,3)),
	    Conversoes::converteParaInt(corFonte.substr(6,3)));
	}
	else
		cor=SColor(255,0,0,0); // cor padrao e petra
	Label::fonte = fonte;
	
}





Label::~Label(void)
{
}

void Label::setTexto(string texto)
{
	Label::texto = texto;
}
string	Label::getTexto()
{
	return Label::texto;
}

void Label::setTamanhoFonte(TAMANHO tamanho)
{
	std::string caminhoFonte = getCaminhoFonte(fonte,tamanho);		
	font = env->getFont(caminhoFonte.c_str());
}
void Label::desenhar(IVideoDriver * driver)
{
	// Codigo problamatica. Problema ao desenhar qualquer label.
	/*
	core::rect<s32> clip = core::rect<s32>(Label::getPosisao().x,Label::getPosisao().y,Label::getPosisao().x+tamanho.x,Label::getPosisao().y+tamanho.y);
	font->draw(
		Label::texto.c_str(),
		core::rect<s32>(Label::getPosisao().x,Label::getPosisao().y,Label::getPosisao().x+tamanho.x,Label::getPosisao().y+tamanho.y),
		cor
		,Label::centralizaVertical		
		,Label::centralizaHorizontal,
		&clip
		);
	*/ 

	// Novo codigo arrumado : desenhando qualquer label. Bruna e Roger.
	font->draw(
		Label::texto.c_str(),
		core::rect<s32>(Label::getPosisao().x,Label::getPosisao().y,Label::getPosisao().x+tamanho.x,Label::getPosisao().y+tamanho.y),
		cor
		,Label::centralizaVertical		
		,Label::centralizaHorizontal
		);
	
}

std::string Label::getCaminhoFonte(std::string fonte,TAMANHO tamanho)
{
	std::string caminho;
	caminho="media/fontes/";
	caminho+=fonte;
	if(tamanho == TAMANHO::PEQUENO)
		caminho+="/pequeno/";
	else if(tamanho == TAMANHO::MEDIO)
		caminho+="/medio/";
	if(tamanho == TAMANHO::GRANDE)
		caminho+="/grande/";
	caminho+=fonte;
	caminho+=".xml";
	return caminho;
}

void Label::setTamanho(Vetor tamanho)
{
	Label::tamanho = tamanho;
}
Vetor Label::getTamanho()
{
	return Label::tamanho;
}

void Label::setCor(SColor cor)
{
	Label::cor = cor;
}

SColor Label::getCor()
{
	return Label::cor;
}