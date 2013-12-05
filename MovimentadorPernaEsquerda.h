#pragma once
#include "movimentadormembro.h"
#include "tipos.h"
using namespace tipos;
class MovimentadorPernaEsquerda : public MovimentadorMembro
{
private:
	Cronometro  cronometro;
	Vetor pos_1;
	Vetor pos_2;
	vector<MarcadorPedra *> marcadores;
	int indiceAnterior;
	int indiceAtual;
public:
	MovimentadorPernaEsquerda(vector<MarcadorPedra *> marcadores);
	~MovimentadorPernaEsquerda(void);
	virtual void mover(irr::scene::IAnimatedMeshSceneNode * node,tipos::Esqueleto esqueleto) override;
		
	virtual bool terminou() override;
	virtual void reset() override;	
	
};

