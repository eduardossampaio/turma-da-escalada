#pragma once
#include "tecladovirtual.h"
class TecladoAlfaNumerico : public TecladoVirtual
{
public:
	TecladoAlfaNumerico(Vetor pos);
	~TecladoAlfaNumerico(void);


	virtual bool emCimaDoTeclado(Vetor pos) override;

	
private:

	
	
};