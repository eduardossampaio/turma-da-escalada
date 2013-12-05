#pragma once
#include "tecladovirtual.h"
class TecladoGenero :public TecladoVirtual
{
public:
	TecladoGenero(Vetor posicao) ;
	~TecladoGenero(void);
	virtual bool emCimaDoTeclado(Vetor pos) override;

	
};

