#pragma once
#include "tecladovirtual.h"
class TecladoNumerico : public TecladoVirtual , public CliqueListener
{
public:
	TecladoNumerico(Vetor posicao);
	~TecladoNumerico(void);

	virtual void onClique(Vetor pos) override;
	virtual void posicaoCaptada(Vetor pos) override;
	virtual bool emCimaDoTeclado(Vetor pos) override;


private:


};

