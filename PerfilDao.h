#pragma once
#include "tipos.h"
#include <iostream>
using namespace tipos;
class PerfilDao
{
public:
	PerfilDao(void);
	~PerfilDao(void);
	void criarPerfil(Save save);
	vector<Save> carregarPerfis();
	void atualizarPerfil(Save save);
	int  gerarIdPersonagem();
	void excluirPerfil(Save save);
	bool PerfilDao::isExistPerfil(Save save);
private:
	std::string arq;
	std::string arq_metadata;
	void novaTag(irr::io::IXMLWriter * writer, wstring tag,std::string val);
	void salvarPerfilXML(irr::io::IXMLWriter * writer,Save save);
	

	typedef struct s_metadata
	{
		int id;
	}Metadata;

	Metadata	lerMetadata();
	void		salvarMetadata(Metadata data);

};

