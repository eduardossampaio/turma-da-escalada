#pragma once
#include "tipos.h"
#include "Focavel.h"
class CliqueListener : public Focavel
{
public:
	CliqueListener(void);
	~CliqueListener(void);
	virtual void onClique(tipos::Vetor posicao)=0;
	virtual void posicaoCaptada(tipos::Vetor posicao)=0;
};

