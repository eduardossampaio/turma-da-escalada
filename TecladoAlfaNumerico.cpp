#include "stdafx.h"
#include "TecladoAlfaNumerico.h"
#include "tipos.h"
#include "Tecla.h"
#include <iostream>
#include "CalculosUteis.h"
#include <vector>

#include "Configuracoes.h"

using namespace std;





TecladoAlfaNumerico::TecladoAlfaNumerico(Vetor posicao) : TecladoVirtual(posicao)
{
	
	Configuracoes * configuracoes = new Configuracoes();
	tipos::configuracoes config = configuracoes->carregarConfigucacoes();

	TecladoAlfaNumerico::altura = config.resolucao.y ;//- posicao.y;
	TecladoAlfaNumerico::largura = config.resolucao.x ;//- posicao.x;

	
	TecladoAlfaNumerico::qtdX = 10;
	TecladoAlfaNumerico::qtdY = 5;


	
	criarTecla("1",0,0,1,Comportamento::LETRA);	
	criarTecla("2",1,0,1,Comportamento::LETRA);	
	criarTecla("3",2,0,1,Comportamento::LETRA);	
	criarTecla("4",3,0,1,Comportamento::LETRA);		
	criarTecla("5",4,0,1,Comportamento::LETRA);	
	criarTecla("6",5,0,1,Comportamento::LETRA);		
	criarTecla("7",6,0,1,Comportamento::LETRA);	
	criarTecla("8",7,0,1,Comportamento::LETRA);	
	criarTecla("9",8,0,1,Comportamento::LETRA);	
	criarTecla("0",9,0,1,Comportamento::LETRA);	
	
	criarTecla("q",0,1,1,Comportamento::LETRA);		
	criarTecla("w",1,1,1,Comportamento::LETRA);	
	criarTecla("e",2,1,1,Comportamento::LETRA);	
	criarTecla("r",3,1,1,Comportamento::LETRA);		
	criarTecla("t",4,1,1,Comportamento::LETRA);	
	criarTecla("y",5,1,1,Comportamento::LETRA);		
	criarTecla("u",6,1,1,Comportamento::LETRA);	
	criarTecla("i",7,1,1,Comportamento::LETRA);	
	criarTecla("o",8,1,1,Comportamento::LETRA);	
	criarTecla("p",9,1,1,Comportamento::LETRA);	

	criarTecla("a",0,2,1,Comportamento::LETRA);	
	criarTecla("s",1,2,1,Comportamento::LETRA);	
	criarTecla("d",2,2,1,Comportamento::LETRA);		
	criarTecla("f",3,2,1,Comportamento::LETRA);		
	criarTecla("g",4,2,1,Comportamento::LETRA);	
	criarTecla("h",5,2,1,Comportamento::LETRA);		
	criarTecla("j",6,2,1,Comportamento::LETRA);	
	criarTecla("k",7,2,1,Comportamento::LETRA);	
	criarTecla("l",8,2,1,Comportamento::LETRA);	
	criarTecla("~",9,2,1,Comportamento::LETRA);	

	criarTecla("shift",0,3,2,Comportamento::SHIFT);		
	
	criarTecla("z",2,3,1,Comportamento::LETRA);	
	criarTecla("x",3,3,1,Comportamento::LETRA);	
	criarTecla("c",4,3,1,Comportamento::LETRA);		
	criarTecla("v",5,3,1,Comportamento::LETRA);	
	criarTecla("b",6,3,1,Comportamento::LETRA);	
	criarTecla("n",7,3,1,Comportamento::LETRA);	
	criarTecla("m",8,3,1,Comportamento::LETRA);	
	criarTecla("<-",9,3,1,Comportamento::BACKSPACE);	

	criarTecla(" ",0,4,10,Comportamento::LETRA);	
	

	
	
}


TecladoAlfaNumerico::~TecladoAlfaNumerico(void)
{
}


bool TecladoAlfaNumerico::emCimaDoTeclado(Vetor pos)
{
	return foiHabilitado && CalculosUteis::pontoDentroDeArea(pos,posicao,Vetor(largura,altura));
	//return true;
}

