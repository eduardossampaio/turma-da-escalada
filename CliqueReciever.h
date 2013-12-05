#pragma once
#include "tipos.h"
class CliqueReciever
{
public:
	CliqueReciever(void);
	~CliqueReciever(void);

	virtual void cliqueRecebido(tipos::Vetor vetor) =0;
};

