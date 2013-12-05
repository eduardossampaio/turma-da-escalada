#pragma once
#include "movimentadormembro.h"
#include "Transformador.h"
#include "Pose.h"
#include "tipos.h"
using namespace tipos;
class MovimentadorSubirPersonagem :
	public MovimentadorMembro
{
	private:
		bool primeiro;
		bool terminado;
		Pose * pose;
		Vetor posicaoJoelhoAnterior;
		Vetor posicaoJoelho;
		Transformador * transformadorSubir;
		int passos;
		float tempo;
		int indice;
		Cronometro cronometro ;
		int margem;
		vector<MarcadorPedra *> marcadores;			
public:
	MovimentadorSubirPersonagem(vector<MarcadorPedra *> marcadores);
	~MovimentadorSubirPersonagem(void);
	virtual void mover(irr::scene::IAnimatedMeshSceneNode * node,tipos::Esqueleto esqueleto) override;
	virtual bool terminou() override;
	virtual void reset() override;
};

