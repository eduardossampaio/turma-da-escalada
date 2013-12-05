#pragma once

#include "Tecla.h"
class TeclaListener :public CliqueListener
{
public:
	TeclaListener(Tecla * tecla);
	~TeclaListener(void);

	virtual void onClique(tipos::Vetor posicao) override;
	virtual void posicaoCaptada(tipos::Vetor posicao) override;
private:
	Tecla * tecla;
};

