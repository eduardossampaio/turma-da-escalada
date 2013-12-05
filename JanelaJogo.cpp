#include "stdafx.h"
#include "JanelaJogo.h"
#include "FaseDAO.h"
#include "PersonagemDAO.h"
#include "KinectSensor.h"
#include "Transformador.h"
#include "Conversoes.h"
#include "TransformadorAtualizacaoPosicao.h"
#include "TransformadorKinect.h"
#define EIXOYPADRAO 50

//teste 
int x = 0;
int y = 0;
int z = 0;

bool inverteuXY = false;
bool inverteuXZ = false;
bool inverteuYZ = false;
int diffY = 0;
int indiceMembro = 1;
bool subirPersonagem = false;
int  indiceSubir_ = 0;

bool usarKinect = true;
core::vector3df posLuz(10,300,10);
ILightSceneNode * luz ;
Cronometro cronometroSubir;
Transformador * transformadorSubir;
Label * msg;
bool cameraFPS = false;
MovimentadorMembro * moveBraco = NULL;//new MovimentadorBracoDireito(marcadores);
Vetor pontoPeOriginal;
matrix4 mCot;
core::vector3df posCOt;
core::vector3df posMao_;
core::vector3df	posRoot;

Imagem * logoKinect;
bool entrouNoIfDoCume = false;
//float cume = 120;
JanelaJogo::JanelaJogo(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id,Fase_Dados dados) : Janela(parent, mgr, id),dados(dados)
{

	msg=new Label(Vetor(0,0),Vetor(150,30),"teste","comic",TAMANHO::PEQUENO);




	for (int i = 0; i<JanelaJogo::dados.marcadores.size(); i++)
	{
		JanelaJogo::marcadores.push_back(  new MarcadorPedra(dados.marcadores[i]) );
	}
	logoKinect = new Imagem(Vetor(0,0),"ui/icone/kinect-icon.png");


	sensor = KinectSensor::getInstancia();
		//new KinectSensor();

	setarComponentes3D();
}


JanelaJogo::~JanelaJogo(void)
{
}

void JanelaJogo::desenhar()
{

	for (int i = 0; i<JanelaJogo::marcadores.size(); i++)
	{
		SceneManager->getVideoDriver()->setTransform(irr::video::E_TRANSFORMATION_STATE::ETS_WORLD,core::IdentityMatrix);
		Vetor pos = marcadores[i]->getCoordenada();
		float margem = marcadores[i]->getMargem();

		manager->getVideoDriver()->draw3DBox(
			core::aabbox3d<irr::f32>(
			pos.x - margem, pos.y - margem, pos.z - margem,
			pos.x + margem, pos.y + margem, pos.z + margem),
			SColor(255, 0, 0, 0));
	}
	int margem = 1;
	manager->getVideoDriver()->draw3DBox(
			core::aabbox3d<irr::f32>(
			posLuz.X - margem, posLuz.Y - margem, posLuz.Z - margem,
			posLuz.X + margem, posLuz.Y + margem, posLuz.Z + margem),
			SColor(255, 0, 0, 0));



	nodePersonagem->updateAbsolutePosition();
	for (int i = 0; i < nodePersonagem->getJointCount(); i++)
	{
		nodePersonagem->getJointNode(i)->updateAbsolutePosition();		
	}

	if(sensor->getUsuariosAtivos() > 0)
		logoKinect->desenhar(SceneManager->getVideoDriver());

	if (usarKinect)
	{
		if(!entrouNoIfDoCume)
		{
		sensor->processar();
		if (sensor->getUsuariosAtivos() > 0)
		{
			avatar->atualizarPosicao(sensor->capturar());

		}
		}
	}



	if(!cameraFPS)
	{
		///JanelaJogo::camera->setPosition(core::vector3df(6.69, 34.99, 44.50));
		//JanelaJogo::camera->setTarget(core::vector3df(6.90, 38.75, -12));
		//JanelaJogo::camera->setRotation(core::vector3df(356.22, 179.78, 0));
	}//
	IBoneSceneNode * cabeca = nodePersonagem->getJointNode("Head");
	core::vector3df posCabeca = cabeca->getAbsolutePosition();
	desenharComponentes();
	if(posCabeca.Y >= dados.cume && ! entrouNoIfDoCume)
	{
		Janela::exibirMensagemSimples("Parabens voce chegou ao final",new JanelaJogo::BotaoConcluidoListener());
		entrouNoIfDoCume = true;
	}
	if(entrouNoIfDoCume)
	{
		//cursor->atualizar();
		cursor->desenhar(SceneManager->getVideoDriver());
		
		
		
	}
	if(false)
	printf("pos [%f %f %f] [%f %f %f] [%f %f %f]\n",
		camera->getPosition().X,camera->getPosition().Y,camera->getPosition().Z,
		camera->getRotation().X,camera->getRotation().Y,camera->getRotation().Z,
		camera->getTarget().X,camera->getTarget().Y,camera->getTarget().Z );
	atualizaCamera();
}

void  JanelaJogo::setarComponentes3D()
{
	ISceneManager *manager = SceneManager;


	//manager->getVideoDriver()->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

	//SceneManager->getVideoDriver() ->setFog(video::SColor(0,138,125,81), video::EFT_FOG_LINEAR, 25000, 100000, 30, true, false);
	IAnimatedMesh * cenarioMesh = manager->getMesh(dados.ambiente.arquivo.c_str());
	if (cenarioMesh)
	{
		//manager->getMeshManipulator()->makePlanarTextureMapping(
			//cenarioMesh->getMesh(0), 0.003f);
		IMesh * cenario_tangente_mesh = SceneManager->getMeshManipulator()->createMeshWithTangents(cenarioMesh->getMesh(0));
			//smgr->getMeshManipulator()->
				//createMeshWithTangents(roomMesh->getMesh(0));

		nodeCenario = manager->addMeshSceneNode(cenario_tangente_mesh);
		nodeCenario->setMaterialFlag(EMF_LIGHTING, false);
		nodeCenario->setPosition(core::vector3df(JanelaJogo::dados.ambiente.posicao.x, JanelaJogo::dados.ambiente.posicao.y, JanelaJogo::dados.ambiente.posicao.z));
		nodeCenario->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_BACK_FACE_CULLING,false);
		nodeCenario->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_FRONT_FACE_CULLING,false);
		nodeCenario->setAutomaticCulling(false);
		
	//	nodeCenario->setMaterialFlag(video::EMF_FOG_ENABLE, true);
		//nodeCenario->setMaterialType(video::EMT_SOLID);
		

		nodeCenario->setRotation(core::vector3df(dados.ambiente.rotacao.x, dados.ambiente.rotacao.y, dados.ambiente.rotacao.z));
		int childCount = nodeCenario->getChildren().size();
		nodeCenario->setScale(core::vector3df(dados.ambiente.escala.x, dados.ambiente.escala.x, dados.ambiente.escala.z));

		printf("criou\n");

		for(int i=0;i<nodeCenario->getMaterialCount();i++)
		{
			nodeCenario->getMaterial(i).Shininess = 20.0f;

			nodeCenario->getMaterial(i).SpecularColor.set(255,255,255,255);

			nodeCenario->getMaterial(i).AmbientColor.set(255,255,255,255); 
			nodeCenario->getMaterial(i).DiffuseColor.set(255,255,255,255); 
			nodeCenario->getMaterial(i).EmissiveColor.set(0,0,0,0);
		}


		

	}

	PersonagemDAO * dao = new PersonagemDAO();
	Mesh_Info p = dao->getPersonagens()[0];

	IAnimatedMesh * mesh = SceneManager->getMesh(p.arquivo.c_str());
	if (mesh)
	{
		nodePersonagem = getSceneManager()->addAnimatedMeshSceneNode(mesh);
		
		
		nodePersonagem->setPosition(core::vector3df(dados.personagem.posicao.x, dados.personagem.posicao.y, dados.personagem.posicao.z));
nodePersonagem->setPosition(core::vector3df(dados.personagem.posicao.x, dados.personagem.posicao.y, dados.personagem.posicao.z));
		
		nodePersonagem->setRotation(core::vector3df(dados.personagem.rotacao.x, dados.personagem.rotacao.y, dados.personagem.rotacao.z));

		nodePersonagem->setScale(core::vector3df(p.escala.x * dados.personagem.escala.x, p.escala.y * dados.personagem.escala.y, p.escala.z * dados.personagem.escala.z));

		nodePersonagem->setScale(core::vector3df(p.escala.x * 10, p.escala.y * 10, p.escala.z * 10));
		nodePersonagem->setVisible(true);
		nodePersonagem->setMaterialFlag(EMF_LIGHTING, false);
		//nodePersonagem->setMaterialFlag(video::EMF_FOG_ENABLE, true);


		nodePersonagem->setJointMode(EJUOR_CONTROL);

		avatar = new Avatar(SceneManager, p, marcadores);
		avatar->setNode(nodePersonagem);
		nodePersonagem->updateAbsolutePosition();
		for(int i=0;i<nodePersonagem->getJointCount();i++)
			nodePersonagem->getJointNode(i)->updateAbsolutePosition();
		posRoot = nodePersonagem->getAbsolutePosition();
	}

	//pedras
	luz = SceneManager->addLightSceneNode(0,posLuz,SColorf(0.5f, 1.0f, 0.5f, 0.0f),1000000);
//	SceneManager->setAmbientLight(video::SColorf(0.3,0.3,0.3,1));
	//video::SColorf(0.5f, 1.0f, 0.5f, 0.0f), 800.0f)
	//luz->setDebugDataVisible( scene::EDS_BBOX );
	//luz->setVisible(true);
	
	for(int i=0;i<marcadores.size();i++)
	{

		Vetor posPersonagem = Vetor(0,0,0);
		IAnimatedMesh * mesh	= SceneManager->getMesh("modelos/terreno/Pedra tipo 1/pedra.obj");
		IAnimatedMeshSceneNode * nodePedra = SceneManager->addAnimatedMeshSceneNode(mesh);
		nodePedra->setPosition(
			core::vector3df(
			marcadores[i]->getCoordenada().x + posPersonagem.x,
			marcadores[i]->getCoordenada().y + posPersonagem.y,
			marcadores[i]->getCoordenada().z + posPersonagem.z
			));
		nodePedra->setScale(core::vector3df(10,10,10));
	}


	//irr::core::list<ISceneNode * node> *nodes =
	;
	for each ( ISceneNode * node_ in SceneManager->getRootSceneNode()->getChildren())
	{
		node_->setAutomaticCulling(EAC_OFF);
		nodePersonagem->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_BACK_FACE_CULLING,false);
		nodePersonagem->setMaterialFlag(video::E_MATERIAL_FLAG::EMF_FRONT_FACE_CULLING,false);
	}

	if (cameraFPS)
		JanelaJogo::camera = manager->addCameraSceneNodeFPS();
	else{
		JanelaJogo::camera =
			manager->addCameraSceneNode();


		
		
		JanelaJogo::camera->setPosition(core::vector3df(dados.camera.posicao.x, dados.camera.posicao.y, dados.camera.posicao.z));
		JanelaJogo::camera->setRotation(core::vector3df(dados.camera.rotacao.x, dados.camera.rotacao.y, dados.camera.rotacao.z));
		JanelaJogo::camera->setTarget(core::vector3df(dados.camera.lookat.x, dados.camera.lookat.y, dados.camera.lookat.z));
		JanelaJogo::camera->setVisible(true);
	}

	if (!sensor->ativo())
		sensor->iniciar();
	//cursor = new KinectCursor();
	JanelaJogo::cursor = new KinectCursor();
}
void JanelaJogo::atualizaCamera()
{
	core::vector3df pos = nodePersonagem->getAbsolutePosition();
	float diff =  pos.Y -posRoot.Y ;
	if(diff!=0)
	{
		printf("diff %f\n",diff);
		core::vector3df posCamera = camera->getAbsolutePosition();
		core::vector3df lookat = camera->getTarget();
		posCamera.Y += diff;
		lookat.Y +=diff;
		camera->setPosition(posCamera);
		camera->setTarget(lookat);
		posRoot = pos;
	}
}
bool JanelaJogo::OnEvent(const SEvent& event)
{
	if(cameraFPS)
		camera->OnEvent(event);
	core::vector3df rot;
	Vetor pos;

	std::string mao_esquerda_bone_teste				=       "Hand_R";    
	std::string ombro_esquerd_bone_teste			=       "UpArm_R";
	std::string braco_esqerdo_bone_teste			=       "LoArm_R";

	IBoneSceneNode * ombroDir = nodePersonagem->getJointNode("UpArm_R");
	IBoneSceneNode * cotDir = nodePersonagem->getJointNode("LoArm_R");

	IBoneSceneNode * ombroEsq = nodePersonagem->getJointNode("UpArm_L");;
	IBoneSceneNode * cotEsq = nodePersonagem->getJointNode("LoArm_L");

	IBoneSceneNode * pernaDir = nodePersonagem->getJointNode("UpLeg_R");
	IBoneSceneNode * joelhoDir = nodePersonagem->getJointNode("LoLeg_R");

	IBoneSceneNode * pernaEsq = nodePersonagem->getJointNode("UpLeg_L");
	IBoneSceneNode * joelhoEsq = nodePersonagem->getJointNode("LoLeg_L");

	IBoneSceneNode * root = nodePersonagem->getJointNode("Root");

	core::vector3df rotBracoDir;
	core::vector3df rotBracoEsq;
	core::vector3df rotPernaDir;
	core::vector3df rotPernaEsq;

	core::vector3df posBracoEsq;
	core::vector3df posBracoDir;


	Vetor posJoelho;
	core::vector3df rotCoxa;
	Vetor posPe;
	float angulo;
	if (event.EventType == EET_KEY_INPUT_EVENT)
	{
		if (event.KeyInput.PressedDown)
		{

			switch (event.KeyInput.Key)
			{
			case KEY_KEY_0:
				transformadorSubir = new TransformadorAtualizacaoPosicao(nodePersonagem);
				break;
			case KEY_KEY_1:
					rotCoxa = nodePersonagem->getAbsolutePosition();
					rotCoxa.Y +=1;
					nodePersonagem->setPosition(rotCoxa);
					nodePersonagem->updateAbsolutePosition();

					for(int i=0;i<nodePersonagem->getJointCount();i++)
						nodePersonagem->getJointNode(i)->updateAbsolutePosition();
					transformadorSubir->transformar(nodePersonagem,tipos::Esqueleto());
					break;
				break;
			case KEY_KEY_Q:
				rotBracoDir = ombroDir->getRotation();
				rotBracoDir.Y+=2;
				ombroDir->setRotation(rotBracoDir);
				//	printf("rot %f %f %f\n",rotBracoDir.X,rotBracoDir.Y,rotBracoDir.Z);
				break;
			case KEY_KEY_W:
				rotBracoDir = ombroDir->getRotation();
				rotBracoDir.Y-=2;
				ombroDir->setRotation(rotBracoDir);
				//	printf("rot %f %f %f\n",rotBracoDir.X,rotBracoDir.Y,rotBracoDir.Z);
				break;
			case KEY_KEY_E:
				rotBracoDir = cotDir->getRotation();
				rotBracoDir.Y+=2;
				cotDir->setRotation(rotBracoDir);
				//	printf("rot %f %f %f\n",rotBracoDir.X,rotBracoDir.Y,rotBracoDir.Z);
				break;
			case KEY_KEY_R:
				rotBracoDir = cotDir->getRotation();
				rotBracoDir.Y-=2;
				cotDir->setRotation(rotBracoDir);
				//	printf("rot %f %f %f\n",rotBracoDir.X,rotBracoDir.Y,rotBracoDir.Z);
				break;
			case KEY_KEY_T:
				rotBracoEsq = ombroEsq->getRotation();
				rotBracoEsq.Y+=2;
				ombroEsq->setRotation(rotBracoEsq);
				printf(" rot %f %f %f\n",rotBracoEsq.X,rotBracoEsq.Y,rotBracoEsq.Z);
				break;
			case KEY_KEY_Y:
				rotBracoEsq = ombroEsq->getRotation();
				rotBracoEsq.Y-=2;
				ombroEsq->setRotation(rotBracoEsq);
				printf(" rot %f %f %f\n",rotBracoEsq.X,rotBracoEsq.Y,rotBracoEsq.Z);
				break;
			case KEY_KEY_U:
				rotBracoEsq = cotEsq->getRotation();
				rotBracoEsq.Y+=2;
				cotEsq->setRotation(rotBracoEsq);
				printf(" rot %f %f %f\n",rotBracoEsq.X,rotBracoEsq.Y,rotBracoEsq.Z);
				break;
			case KEY_KEY_I:
				rotBracoEsq = cotEsq->getRotation();
				rotBracoEsq.Y-=2;
				cotEsq->setRotation(rotBracoEsq);
				printf(" rot %f %f %f\n",rotBracoEsq.X,rotBracoEsq.Y,rotBracoEsq.Z);
				break;

			case KEY_KEY_A:
				rotCoxa = pernaDir->getRotation();
				rotCoxa.Y+=2;
				rotCoxa.Z = 0;
				//rotCoxa.X = 180;
				pernaDir->setRotation(rotCoxa);
				break;
			case KEY_KEY_S:
				rotCoxa = pernaDir->getRotation();
				rotCoxa.Y-=2;
				rotCoxa.Z = 0;
				//rotCoxa.X = 180;
				pernaDir->setRotation(rotCoxa);
				break;
			case KEY_KEY_D:
				rotCoxa = joelhoDir->getRotation();
				rotCoxa.Y+=2;
				rotCoxa.Z = 180;
				joelhoDir->setRotation(rotCoxa);

				break;
			case KEY_KEY_F:				
				rotCoxa = joelhoDir->getRotation();
				rotCoxa.Y-=2;
				rotCoxa.Z = 180;
				joelhoDir->setRotation(rotCoxa);


				break;
			case KEY_KEY_G:
				rotCoxa = pernaEsq->getRotation();
				rotCoxa.Y+=2;
				rotCoxa.Z = 0;

				pernaEsq->setRotation(rotCoxa);
				break;
			case KEY_KEY_H:
				rotCoxa = pernaEsq->getRotation();
				rotCoxa.Y-=2;
				rotCoxa.Z = 0;

				pernaEsq->setRotation(rotCoxa);
				break;
			case KEY_KEY_J:
				rotCoxa = joelhoEsq->getRotation();
				rotCoxa.Y+=2;
				rotCoxa.Z = 180;
				joelhoEsq->setRotation(rotCoxa);
				break;
			case KEY_KEY_K:
				rotCoxa = joelhoEsq->getRotation();
				rotCoxa.Y-=2;
				rotCoxa.Z = 180;
				joelhoEsq->setRotation(rotCoxa);
				break;


			case KEY_KEY_Z:
				posLuz.Y ++;
				luz->setPosition(posLuz);
				printf("luz: %f %f %f\n",posLuz.X,posLuz.Y,posLuz.Z);
				break;
			case KEY_KEY_X:
				posLuz.Y --;
				luz->setPosition(posLuz);
				printf("luz: %f %f %f\n",posLuz.X,posLuz.Y,posLuz.Z);
				break;
			case KEY_KEY_C:
				posLuz.Z ++;
				luz->setPosition(posLuz);
				printf("luz: %f %f %f\n",posLuz.X,posLuz.Y,posLuz.Z);
				break;
			case KEY_KEY_V:
				posLuz.Z --;
				luz->setPosition(posLuz);
				printf("luz: %f %f %f\n",posLuz.X,posLuz.Y,posLuz.Z);
				break;
			case KEY_KEY_B:
				luz->setRadius(luz->getRadius() * 10);
				break;
			case KEY_KEY_N:
				luz->setRadius(luz->getRadius() / 10);
				break;
				case KEY_SPACE:
					FILE * marcadoresArq;
					fopen_s(&marcadoresArq, "marcadores-pos.txt", "wt");
					for (int i = 0; i<marcadores.size(); i++)
					{
						tipos::Vetor v = marcadores[i]->getCoordenada();
						fprintf_s(marcadoresArq, "<marcador>\n");
						fprintf_s(marcadoresArq, "\t<x>%f</x>\n", v.x);
						fprintf_s(marcadoresArq, "\t<y>%f</y>\n", v.y);
						fprintf_s(marcadoresArq, "\t<z>%f</z>\n", v.z);
						fprintf_s(marcadoresArq, "</marcador>\n");
					}
					
					fclose(marcadoresArq);
				case KEY_KEY_L:
					for (int i = 0; i<marcadores.size(); i++)
					{
						tipos::Vetor v = marcadores[i]->getCoordenada();
						v.z++;
						marcadores[i]->setCoordenada(v);
					}
					break;
				case KEY_KEY_M:
					for (int i = 0; i<marcadores.size(); i++)
					{
						tipos::Vetor v = marcadores[i]->getCoordenada();
						v.z--;
						marcadores[i]->setCoordenada(v);
					}
					break;
				case KEY_KEY_5:
					posCOt =  nodePersonagem->getAbsolutePosition();
					posCOt.Z++;
					nodePersonagem->setPosition(posCOt);
					printf("personagem %f %f %f\n",posCOt.X,posCOt.Y,posCOt.Z);
					break;
				case KEY_KEY_6:
					posCOt =  nodePersonagem->getAbsolutePosition();
					posCOt.Z--;
					nodePersonagem->setPosition(posCOt);
					printf("personagem %f %f %f\n",posCOt.X,posCOt.Y,posCOt.Z);
					break;
			}
			

		}

	}





	return true;
}

