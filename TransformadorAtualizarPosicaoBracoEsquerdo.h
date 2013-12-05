#pragma once
#include "transformador.h"
#include "tipos.h"
using namespace tipos;
class TransformadorAtualizarPosicaoBracoEsquerdo :public Transformador
{
public:
	TransformadorAtualizarPosicaoBracoEsquerdo(irr::scene::IAnimatedMeshSceneNode * node);
	~TransformadorAtualizarPosicaoBracoEsquerdo(void);
	virtual void transformar(irr::scene::IAnimatedMeshSceneNode * node, tipos::Esqueleto esqueleto) override;
private:
	bool primeiro;
	float distanciaOmbroCotovelo;
	float distanciaCotoveloMao;
	tipos::Vetor posMao;
	tipos::Esqueleto esqueletoRef;
};

