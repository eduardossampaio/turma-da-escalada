#pragma once
#include <irrlicht.h>
#include "Janela.h"
using namespace irr;
class IntroScene : public Janela
{
public:
	IntroScene(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);
	~IntroScene(void);
	
	

	virtual void desenhar() override;
	virtual bool emExecucao() override;
};

