#pragma once
#include "tipos.h"
#include "Focavel.h"
#include <irrlicht.h>
using namespace tipos;
using namespace irr;
using namespace video;
using namespace tipos;

class Componente : public Focavel
{
public:
	Componente(Vetor posicao);
	~Componente(void);
	
	virtual void desenhar(IVideoDriver * driver) = 0;
	
	 void atualizarPosisao(Vetor v);
	 Vetor getPosisao();

	void habilitar(bool habilitar);
	bool habilitado();
protected:
	Vetor posicao;
	bool foiHabilitado;
};

