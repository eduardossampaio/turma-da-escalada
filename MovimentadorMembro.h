#pragma once
#include <irrlicht.h>
#include "tipos.h"
#include "MarcadorPedra.h"
using namespace irr;
using namespace scene;
class MovimentadorMembro
{
public:
	MovimentadorMembro(void);
	~MovimentadorMembro(void);


	virtual void mover(irr::scene::IAnimatedMeshSceneNode * node,tipos::Esqueleto esqueleto) = 0;
	virtual bool terminou() = 0;
	virtual void reset() = 0;
protected:

	float getAnguloBraco(tipos::Vetor p1,tipos::Vetor p2);
	void setarAnguloBone(IAnimatedMeshSceneNode * node, std::string nome_bone,float angulo);

	void setarAnguloPerna(IAnimatedMeshSceneNode * node,std::string nome_bone,float angulo)
		;
	bool verificaMembroMarcador(tipos::Vetor posBone,vector<MarcadorPedra*> marcadores);



};

