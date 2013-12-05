#pragma once
#include "componente.h"
class Boneco :
	public Componente
{
public:
	Boneco(Vetor pos);
	~Boneco(void);

	virtual void desenhar(IVideoDriver * driver) override;

	void setEsqueleto(Esqueleto e);
	Esqueleto getEsqueleto();
	Esqueleto ajustarEsqueleto(Esqueleto esqueleto);
private:
	Esqueleto esqueleto;
};

