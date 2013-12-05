#include "stdafx.h"
#include "CheckBox.h"


CheckBox::CheckBox(Vetor pos):Componente(pos)
{	
	CheckBox::imagemSelecionado   = new Imagem(pos,"media/icones/checked_checkbox.png");
	CheckBox::imagemDeselecionado = new Imagem(pos,"media/icones/unchecked_checkbox.png");	
	selecionado = false; 

}

CheckBox::CheckBox(Vetor pos,string checkboxSelecionado,string checkBoxDeselecionado):Componente(pos)
{
	CheckBox::imagemSelecionado   = new Imagem(pos,checkboxSelecionado);
	CheckBox::imagemDeselecionado = new Imagem(pos,checkBoxDeselecionado);
	selecionado = false;
}

CheckBox::~CheckBox(void)
{
}

bool CheckBox::estaSelecionado()
{
	return CheckBox::selecionado;
}

void CheckBox::desenhar(IVideoDriver * driver)
{
	if(selecionado)
		imagemParaDesenhar = imagemSelecionado;
	else
		imagemParaDesenhar = imagemDeselecionado;

	imagemParaDesenhar->desenhar(driver);
}

void CheckBox::onClique(Vetor pos)
{
	Vetor vFinal = 	CalculosUteis::somarAtributosVetor(imagemParaDesenhar->getPosisao(),imagemParaDesenhar->getTamanho());
	
	if(CalculosUteis::pontoDentroDeArea(pos,CheckBox::imagemParaDesenhar->getPosisao(),vFinal))

		CheckBox::selecionado = ! CheckBox::selecionado;
		
}
void CheckBox::posicaoCaptada(Vetor pos)
{

}

void CheckBox::selecionar(bool selecionar)
{
	CheckBox::selecionado = selecionar;
}