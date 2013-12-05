#pragma once
#include <irrlicht.h>
#include "tipos.h"
class Transformador
{
public:
	Transformador(void);
	~Transformador(void);

	virtual void transformar(irr::scene::IAnimatedMeshSceneNode * mesh, tipos::Esqueleto esqueleto) = 0;
};

