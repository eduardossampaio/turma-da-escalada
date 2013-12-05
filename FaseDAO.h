#pragma once
#include "tipos.h"
#include "XMLDAO.h"
class FaseDAO : XMLDAO
{
public:
	FaseDAO(void);
	~FaseDAO(void);
	tipos::Fase_Dados getFase(std::string arquivo);
};

