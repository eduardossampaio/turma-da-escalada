#pragma once
#include "irrlicht.h"
#include "tipos.h"
using namespace irr;
using namespace core;
using namespace io;
class XMLDAO
{
public:
	XMLDAO(void);
	~XMLDAO(void);
protected:
	tipos::Vetor lerTagComVetor(stringw tag,irr::io::IXMLReader *xml);
	std::string  lerString(irr::io::IXMLReader *xml);
	irr::IrrlichtDevice * getDevice();
};

