#pragma once
#include "transformador.h"
#include "tipos.h"
#include <irrlicht.h>
using namespace irr;
using namespace scene;
class TransformadorAtualizacaoPosicao :
	public Transformador
{
public:
	TransformadorAtualizacaoPosicao(IAnimatedMeshSceneNode * node);
	~TransformadorAtualizacaoPosicao(void);

	virtual void transformar(irr::scene::IAnimatedMeshSceneNode * mesh, tipos::Esqueleto esqueleto) override;
private:
	Transformador * transformadorBracoEsquerdo;
	Transformador * transformadorBracoDireito;
	Transformador * transformadorPernaDireita;
	Transformador * transformadorPernaEsquerda;


};

