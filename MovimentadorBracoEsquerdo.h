#pragma once
#include "MovimentadorMembro.h"
#include "tipos.h"
using namespace tipos;
class MovimentadorBracoEsquerdo : public MovimentadorMembro
{
private:
	Cronometro  cronometro;
	vector<MarcadorPedra *> marcadores;			
	Vetor pos;
	int indiceAnterior;
	int indiceAtual;
	bool terminado;
public:
	
	~MovimentadorBracoEsquerdo(void);
	MovimentadorBracoEsquerdo(vector<MarcadorPedra *> marcadores);
	virtual void mover(irr::scene::IAnimatedMeshSceneNode * node,tipos::Esqueleto esqueleto);
		
		virtual bool terminou() override;
		
		virtual void reset() override;
		
};

