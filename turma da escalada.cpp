#pragma once
#include "stdafx.h"

#include <irrlicht.h>
#define null NULL
#include "Globais.h"

#include "Janelas.h"

#include <stdio.h>

#include "sensores.h"


#include <NiTE.h>
#include "GerenciadorDeExibicao.h"
//#include "GerenciadorExibicao2.h"
#include "Configuracoes.h"
#include "JanelaLoja2.h"


//temporario
#include "MouseSensor.h"
#include "PerfilDao.h"
#include "PersonagemDAO.h"
#include "Avatar.h"
#include "ItemDAO.h"
#include "MarcadorPedra.h"
#include "FaseDAO.h"

using namespace irr;
using namespace std;


#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif


#include "irrlicht.h"
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


int main()
{


	video::E_DRIVER_TYPE driverType;

	printf("Please select the driver you want for this example:\n"\
		" (a) OpenGL 1.5\n (b) Direct3D 9.0c\n (c) Direct3D 8.1\n"\
		" (d) Burning's Software Renderer\n (e) Software Renderer\n"\
		" (f) NullDevice\n (otherKey) exit\n\n");

	char i;
	
	//scanf_s("%c",&i);
	i='a';
	switch(i)
	{
		case 'a': driverType = video::EDT_OPENGL;   break;
		case 'b': driverType = video::EDT_DIRECT3D9;break;
		case 'c': driverType = video::EDT_DIRECT3D8;break;
		case 'd': driverType = video::EDT_BURNINGSVIDEO;break;
		case 'e': driverType = video::EDT_SOFTWARE; break;
		case 'f': driverType = video::EDT_NULL;     break;
		default: return 1;
	}

	
	Configuracoes * conf = new Configuracoes();

	MarcadorPedra * marcador = new MarcadorPedra(Vetor(5,0,5));
	bool dentro = marcador->pontoDentroMarcador(Vetor(4.9,-0.05,4.9));

	
	tipos::configuracoes config = conf->carregarConfigucacoes();

	IrrlichtDevice* device = createDevice(driverType,core::dimension2d<u32>(config.resolucao.x, config.resolucao.y), config.bitsCor, config.fullscreen);
	

	PerfilDao * dao = new PerfilDao();
	

	//dao->criarPerfil(tipos::Save(tipos::Perfil(1,"eduardo","menino1",21,67,Sexo::MASCULINO),0));

	
	if (device == 0)
		return 1; 

	device->setWindowCaption(L"Turma da Escalada");


	
	Globais::setIrrDevice(device);
	Label::setGui(device->getGUIEnvironment());
	
	device->getCursorControl()->setVisible(false);
	//device->getCursorControl()->getPosition();
	
	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	
	Mesh_Info info = Mesh_Info();
	info.arquivo = "modelos/personagem/Bonecos definitivos 23-09-2013/menino1/textures/menino1.x";
	
	
	FaseDAO * faseDAO  = new FaseDAO();
	tipos::Fase_Dados  f =  faseDAO->getFase("fases/parede.xml");
	
	GerenciadorDeExibicao * gerenciador = GerenciadorDeExibicao::getGerenciador();
	GerenciadorExibicao2::setSceneManager(smgr);

	
	tipos::Save s = Save(Perfil(1,"Eduardo","menino1",21,66,Sexo::MASCULINO),0);
	bool teste=false;
	if(!teste)
	{
		//gerenciador->novaJanelaParaExibicao(new IntroScene(smgr->getRootSceneNode(), smgr, 11));
		gerenciador->novaJanelaParaExibicao(new JanelaPrincipal(smgr->getRootSceneNode(),smgr,11));
		//gerenciador->novaJanelaParaExibicao(new JanelaNovoJogo(smgr->getRootSceneNode(),smgr,11));
		
		//JanelaTesteKinect*jtk = new JanelaTesteKinect(); gerenciador->novaJanelaParaExibicao(jtk); device->setEventReceiver(jtk);
		//gerenciador->novaJanelaParaExibicao(new JanelaEscolhaPersonagem(s.perfil,smgr->getRootSceneNode(),smgr,13));
		//gerenciador->novaJanelaParaExibicao(new JanelaConfiguracao(smgr->getRootSceneNode(),smgr,12));
		//gerenciador->novaJanelaParaExibicao(new JanelaEscolhaPerfil(smgr->getRootSceneNode(),smgr,12));
		
		
		//gerenciador->novaJanelaParaExibicao(new JanelaEscolhaFase(smgr->getRootSceneNode(),smgr,13,s));
		
		Jogador * jogador = new Jogador(s);
		//gerenciador->novaJanelaParaExibicao(new JanelaLoja2(jogador,smgr->getRootSceneNode(),smgr,15));
		
		JanelaJogo*janelaJogo=new JanelaJogo(smgr->getRootSceneNode(),smgr,14,f);gerenciador->novaJanelaParaExibicao(janelaJogo);device->setEventReceiver(janelaJogo);
	}
	
	Janela *atual=NULL;
	if(!teste)
	{
		
		 atual = gerenciador->getProximaJanela();
	
	
		atual->iniciar();
	}
	int lastFPS =-1;
	Janela * janela=NULL;
	bool criou1=false;
	bool criou2=false;
	bool criou3=false;
	bool criou4=false;
	Cronometro cronometro;
	int aux=0;
	

	cronometro.iniciarContagem();
	lastFPS =-1;
	while(device->run() && ! GerenciadorDeExibicao::getGerenciador()->sairDoJogo())
        {
               

				
				if(!atual->emExecucao())
				{
					//smgr->getRootSceneNode()->removeChild(atual);
					
					//smgr->getRootSceneNode()->removeAll();
					
					atual = GerenciadorDeExibicao::getGerenciador()->getProximaJanela();
					atual->iniciar();
					
					//atual->iniciar();
					//smgr->getRootSceneNode()->addChild(atual);
				}

				 driver->beginScene(true, true, video::SColor(0,100,100,100));

                smgr->drawAll();
                
               int fps = driver->getFPS();

					if (lastFPS != fps)
					{
						core::stringw str = L"Turma da Escalada";
						str += driver->getName();
						str += " FPS:";
						str += fps;

						device->setWindowCaption(str.c_str());
						lastFPS = fps;
					}

                driver->endScene();
                
        }
	//sensor->finalizar();
	
	return 0;
	

	
}


