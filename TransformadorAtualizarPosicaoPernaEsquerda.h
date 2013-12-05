#pragma once
#include "transformador.h"
using namespace irr;
using namespace scene;
class TransformadorAtualizarPosicaoPernaEsquerda : public Transformador
{
public:
	TransformadorAtualizarPosicaoPernaEsquerda(IAnimatedMeshSceneNode * node);
	~TransformadorAtualizarPosicaoPernaEsquerda(void);
	virtual void transformar(irr::scene::IAnimatedMeshSceneNode * node, tipos::Esqueleto esqueleto) override;
private:
	bool primeiro;
	float distanciaPernaJoelho;
	float distanciaJoelhoPe;
	tipos::Vetor posPe;
};

