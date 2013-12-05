#pragma once
#include "MovimentadorMembro.h"
#include "tipos.h"
using namespace tipos;
class MovimentadorBracoDireito : public MovimentadorMembro
{
private:
	Cronometro  cronometro;
	int indiceAnterior;
	int indiceAtual;
	bool terminado;
	vector<MarcadorPedra *> marcadores;	
	Vetor pos;
public: 

	MovimentadorBracoDireito(vector<MarcadorPedra *> marcadores);
	~MovimentadorBracoDireito();
	virtual void mover(irr::scene::IAnimatedMeshSceneNode * node,tipos::Esqueleto esqueleto) override;
	virtual bool terminou() override;
	virtual void reset() override;
};