#pragma once
#include "Transformador.h"
class TransformadorAtualizarPosicaoPernaDireita : public Transformador
{
public:
	TransformadorAtualizarPosicaoPernaDireita(irr::scene::IAnimatedMeshSceneNode * node);
	~TransformadorAtualizarPosicaoPernaDireita(void);
	virtual void transformar(irr::scene::IAnimatedMeshSceneNode * node, tipos::Esqueleto esqueleto) override;
private:
	bool primeiro;
	float distanciaPernaJoelho;
	float distanciaJoelhoPe;
	tipos::Vetor posPe;
};

