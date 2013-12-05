#pragma once
#include "Janela.h"
#include "tipos.h"
#include "irrlicht.h"
#include "MarcadorPedra.h"
#include "Avatar.h"
#include "GerenciadorDeExibicao.h"
using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
using namespace tipos;
class JanelaJogo : public Janela , public IEventReceiver
{
public:
	JanelaJogo(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id,Fase_Dados dados);
	~JanelaJogo(void);
	virtual void desenhar() override;
	
	virtual bool OnEvent(const SEvent& event) override;
	

	Fase_Dados dados;
private:
	void setarComponentes3D();
	
	ICameraSceneNode * camera;

	vector<MarcadorPedra *> marcadores;

	void atualizaCamera();
	IMeshSceneNode *nodeCenario;
	IAnimatedMeshSceneNode *nodePersonagem;

	Avatar * avatar;

	Sensor * sensor;
	//Cursor * cursor;
	class BotaoConcluidoListener : public CliqueListener
	{
	public:
		void posicaoCaptada(Vetor pos) override{}
		void onClique(Vetor pos) override
		{
			GerenciadorDeExibicao::getGerenciador()->removerUltimaJanelaExibida();
		}
	};
	
	
};

