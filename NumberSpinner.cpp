#include "stdafx.h"
#include "NumberSpinner.h"
#include "Conversoes.h"

NumberSpinner::NumberSpinner(Vetor pos,Vetor tamanho) : Componente (pos)
{

	NumberSpinner::botaoMais  = new Botao(pos,"ui/spinner/seta_cima.png");
	//NumberSpinner::botaoMenos = new Botao(Vetor(pos.x,pos.y+(tamanho.y/2)),"ui/spinner/seta_baixo.png");
	NumberSpinner::botaoMenos = new Botao(pos,"ui/spinner/seta_baixo.png");
	NumberSpinner::tamanho	  = tamanho;
	NumberSpinner::valor      = 0;
	NumberSpinner::labelValor = new Label(posicao,tamanho,""+NumberSpinner::valor,"comic",TAMANHO::MEDIO);
	NumberSpinner::alinhado   = false;
	NumberSpinner::botaoMais->addListener(new NumberSpinner::BotaoMaisListener(this));
	NumberSpinner::botaoMenos->addListener(new NumberSpinner::BotaoMenosListener(this));
	NumberSpinner::minimo = -99;
	NumberSpinner::maximo = 99;

}

NumberSpinner::~NumberSpinner()
{

}

void NumberSpinner::desenhar(IVideoDriver * driver)
{
	
	//desenha uma caixa para o componente
	driver->draw2DRectangle(
		SColor(255,255,255,255),
		core::rect<s32>(
			(int)NumberSpinner::posicao.x,
			(int)NumberSpinner::posicao.y,
			(int)NumberSpinner::posicao.x + NumberSpinner::tamanho.x,
			(int)NumberSpinner::posicao.y + NumberSpinner::tamanho.y
		)
	);

	std::string texto = Conversoes::converteParaString(NumberSpinner::valor);
	
	NumberSpinner::labelValor->setTexto(texto);
	NumberSpinner::botaoMais->desenhar(driver);
	NumberSpinner::botaoMenos->desenhar(driver);
	NumberSpinner::labelValor->desenhar(driver);
	if(!alinhado)
	{
		alinhado = true;
		Vetor posicaoBotaoMais  = NumberSpinner::botaoMais->getPosisao();
		Vetor posicaoBotaoMenos = NumberSpinner::botaoMenos->getPosisao();
		Vetor tamanhoBotaoMais  = NumberSpinner::botaoMais->getTamanho();
		Vetor tamanhoBotaoMenos = NumberSpinner::botaoMais->getTamanho();
		Vetor posicao			= NumberSpinner::getPosisao();
		//colocar o botao mais no lado direito 
		NumberSpinner::botaoMais->atualizarPosisao(
							Vetor(
								NumberSpinner::posicao.x + NumberSpinner::tamanho.x - tamanhoBotaoMais.x,
								posicao.y
							)
		);
	
		//coloca o botao menos no lado direito e abaixo do botão mais
		NumberSpinner::botaoMenos->atualizarPosisao(
							Vetor(
									NumberSpinner::posicao.x+NumberSpinner::tamanho.x - tamanhoBotaoMenos.x,
									posicao.y+ tamanhoBotaoMais.y
							)
		);
		//atualiza Valor na label

		//limita o tamanho para a label não passar dos botões
		/*
		NumberSpinner::labelValor->setTamanho(
							Vetor(
									NumberSpinner::labelValor->getTamanho().x - tamanhoBotaoMais.x,
									NumberSpinner::labelValor->getTamanho().y
							)
		);*/
	}
	

	
	
}

void NumberSpinner::onClique(Vetor pos)
{
	NumberSpinner::botaoMais->onClique(pos);
	NumberSpinner::botaoMenos->onClique(pos);
	
}
void NumberSpinner::posicaoCaptada(Vetor pos)
{
	
}
void NumberSpinner::setValor(int valor)
{
	NumberSpinner::valor = valor;
}
int NumberSpinner::getValor()
{
	return NumberSpinner::valor ;
	
}

void NumberSpinner::incrementaValor()
{
	if(valor<maximo)
		NumberSpinner::valor++;
}
void NumberSpinner::decrementaValor()
{
	if(valor>minimo)
		NumberSpinner::valor--;
}

int NumberSpinner::getMinimo()
{
	return NumberSpinner::minimo;
}
void NumberSpinner::setMinimo(int minimo)
{
	NumberSpinner::minimo = minimo;
	if(valor<minimo)
		valor = minimo;
}
int NumberSpinner::getMaximo()
{
	return NumberSpinner::maximo;
}
void NumberSpinner::setMaximo(int maximo)
{
	NumberSpinner::maximo = maximo;
	if(valor>maximo)
		valor = maximo;
}