#include "stdafx.h"
#include "validaUteis.h"
#include <iostream>


validaUteis::validaUteis(void)
{
}


validaUteis::~validaUteis(void)
{
}


  int  validaString (std::string str,int tamanhoMin, int tamanhoMax) {
	if (str.length() < tamanhoMin || str.length() > tamanhoMax) 
			return 0; // validado
	return 1; // invalido
}




  int  validaInteiro (int inteiro,int valorMin, int valorMax) {
	if (inteiro < valorMin || inteiro > valorMax) 
			return 0; // validado
		return 1;  // invalido
}


  int  validaDouble (double valor,double valorMin, double valorMax) {
	if (valor < valorMin || valor > valorMax) 
			return false; // validado
		return true;// invalido
}


  


