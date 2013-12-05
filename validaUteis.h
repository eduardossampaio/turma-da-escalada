#pragma once
#include "irrlicht.h"
#include <iostream>
#include "Janela.h"
#include "JanelaEscolhaPersonagem.h"
#include "CaixaTexto.h"

using namespace std;
class validaUteis
{
public:
	validaUteis(void);
	~validaUteis(void);

	 int  validaString (std::string str,int tamanhoMin, int tamanhoMax);
	 int  validaInteiro (int inteiro,int valorMin, int valorMax);
	 int  validaDouble (double valor,double valorMin, double valorMax);
	
/*
// evento do botao Validar
class botaoValidar : public CliqueListener {
	private:
	//ISceneManager * manager;
	JanelaNovoJogo * janela;

	public:
	virtual void onClique(Vetor pos) override {
		std::string listaMensagens;
		Perfil perfil = janela->getPerfil();
		if (perfil.nome.length() < 1 || perfil.nome.length() > 200) {
			listaMensagens.append("Nome invalido. Insira um nome de 1 a 200 caracteres !");
			tipos::flag = true;
		}
		
		if (perfil.idade < 6 || perfil.idade > 12) {
			listaMensagens.append("Idade invalida. A idade deve estar entre 6 a 12 anos!");
			tipos::flag = true;
		}
		
		if(perfil.peso < 20) {
			listaMensagens.append("Peso invalido. O peso deve estar no minimo com 20 kg.");
			tipos::flag = true;
		}
		
		if(perfil.sexo != MASCULINO || perfil.sexo != FEMININO) { // sexo
			listaMensagens.append("Sexo invalido. Deve escolher o sexo feminino ou masculino");
			tipos::flag = true;
		}
		//janela->
		
	}
}
*/



};
