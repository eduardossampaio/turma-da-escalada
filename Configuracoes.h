#pragma once
#include "tipos.h"
/*
	classe representando as cconfigura��es do jogo. Os dados s�o lidos e armazenados em 
	um arquivo xml

*/
class Configuracoes
{
public:
	Configuracoes(void);
	~Configuracoes(void);
	/*
		salva as configura��es em um arquivo xml
	*/
	void salvarConfiguracoes(tipos::configuracoes config);
	/*
		carrega as configuracoes do arquivo xml
	*/
	tipos::configuracoes carregarConfigucacoes();

	std::vector<tipos::Vetor> carregarResolucoes();

private:
	std::string arq;
	std::string metadata;
	irr::IrrlichtDevice *device;
};

