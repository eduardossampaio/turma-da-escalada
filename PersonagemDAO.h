#pragma once
#include "tipos.h"
#include "XMLDAO.h"
using namespace tipos;

#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


class PersonagemDAO : XMLDAO
{


public:
	PersonagemDAO(void);
	~PersonagemDAO(void);
	

	vector<Mesh_Info>	getPersonagens();
	tipos::Mesh_Info*	getPersonagem(std::string id);
private:
	std::string arquivo;
	tipos::Vetor lerTagComVetor(stringw tag,irr::io::IXMLReader *xml);
	PersonagemDAO::Mesh_Material letMaterial(stringw tag,irr::io::IXMLReader * xml);
};

