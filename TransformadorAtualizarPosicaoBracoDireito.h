#pragma once
#include "transformador.h"
#include <irrlicht.h>
using namespace irr;
using namespace scene;
class TransformadorAtualizarPosicaoBracoDireito : public Transformador
{
public:
	TransformadorAtualizarPosicaoBracoDireito(IAnimatedMeshSceneNode * node);
	~TransformadorAtualizarPosicaoBracoDireito(void);
	virtual void transformar(irr::scene::IAnimatedMeshSceneNode * node, tipos::Esqueleto esqueleto) override;
private:
	bool primeiro;
	float distanciaOmbroCotovelo;
	float distanciaCotoveloMao;
	tipos::Vetor posMao;
	tipos::Vetor posCotovelo;
	tipos::Vetor posOmbro;
	IAnimatedMeshSceneNode * node;
	tipos::Esqueleto esqueletoRef;
};