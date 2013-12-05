#include "stdafx.h"
#include "JanelaTesteKinect.h"
#include "irrlicht.h"
#include "Cronometro.h"

#include "CalculosUteis.h"

#include "movimentos.h"
#include "Configuracoes.h"
#include "PersonagemDAO.h"
#include "Avatar.h"


std::string posicoes = "posicoes.txt";


//#include "Kinect.h"
//#include "CPlayer.h"

#include <stdio.h>
#include <sstream>
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

bool criou ;
Cronometro cronometro;
IAnimatedMeshSceneNode* node = NULL;
IdentificadorMovimento * identificador;
IdentificadorMovimento * identificadorSpray;
IdentificadorMovimento * identificadorSprayEsq;
Pose * poseEscaparPedra;
Pose * pose = new PosePause();
bool identificado = false;
bool kinect=false;

IrrlichtDevice * deviceTesteKinect;
Boneco * boneco;

MovimentoSprayEsquerdoPose1 *p1;//=  new MovimentoSprayDireitoPose1();
vector<Mesh_Info> personagens;
Mesh_Info char_mesh;
//IAnimatedMeshSceneNode * node = NULL;
IAnimatedMesh * mesh =NULL;

vector<SMaterial>  materiais;

Avatar * avatar;
//-------------
vector<Esqueleto> esqueletos;
int i=0;
int indiceSubir = 0;
bool subir = true;
Cronometro cronometroParaSubir;


JanelaTesteKinect::JanelaTesteKinect(): Janela(Janela::manager->getRootSceneNode(),Janela::manager,14)
{
        JanelaTesteKinect::sensor = new KinectSensor();
        JanelaTesteKinect::boneco = new Boneco(Vetor());
        criou = false;
        
        identificador = new IdentificadorMovimento();
        identificador->adicionarMovimento(new PosePause(),7);

        identificadorSpray=new IdentificadorMovimento();
        identificadorSpray->adicionarMovimento(new MovimentoSprayDireitoPose1(),1);
        identificadorSpray->adicionarMovimento(new MovimentoSprayDireitoPose2(),1);
        identificadorSpray->adicionarMovimento(new MovimentoSprayDireitoPose1(),1);
        identificadorSpray->adicionarMovimento(new MovimentoSprayDireitoPose2(),1);
        identificadorSpray->adicionarMovimento(new MovimentoSprayDireitoPose1(),1);
        identificadorSpray->adicionarMovimento(new MovimentoSprayDireitoPose2(),1);

        //------------------------------------------------------------------------------
        identificadorSprayEsq=new IdentificadorMovimento();
        identificadorSprayEsq->adicionarMovimento(new MovimentoSprayEsquerdoPose1(),2);
        identificadorSprayEsq->adicionarMovimento(new MovimentoSprayEsquerdoPose2(),2);
        identificadorSprayEsq->adicionarMovimento(new MovimentoSprayEsquerdoPose1(),2);
        identificadorSprayEsq->adicionarMovimento(new MovimentoSprayEsquerdoPose2(),2);
        identificadorSprayEsq->adicionarMovimento(new MovimentoSprayEsquerdoPose1(),2);
        identificadorSprayEsq->adicionarMovimento(new MovimentoSprayEsquerdoPose2(),2);

//      p1=  new MovimentoSprayDireitoPose1();
        p1=  new MovimentoSprayEsquerdoPose1();
        poseEscaparPedra = new PoseEscaparPedra();
        JanelaTesteKinect::primeiro = true;
        /*----------------------*/
        PersonagemDAO * dao = new PersonagemDAO();
        personagens = dao->getPersonagens();
        char_mesh = personagens[0];		
		
        boneco = new Boneco(Vetor(100,300));
        
        
}


JanelaTesteKinect::~JanelaTesteKinect(void)
{
}
std::string converter(float n)
{
        std::ostringstream buff;
        buff << n;
        return buff.str();
}
void JanelaTesteKinect::desenhar()
{
        
        Mesh_Info p = char_mesh;
        
        if(JanelaTesteKinect::primeiro)
        {
                camera =
                //SceneManager->addCameraSceneNode(0,core::vector3df(30,0,123),core::vector3df(30,0,0));
                SceneManager->addCameraSceneNodeFPS();
				camera->setPosition(core::vector3df(30,0,123));
					
				camera->setTarget(core::vector3df(30,0,0));
                //char_mesh.arquivo="modelos/dwarf.x";
                                // char_mesh.arquivo="modelos/personagem/Bonecos definitivos 23-09-2013/professor2/professor.b3d";
                 mesh = SceneManager->getMesh(char_mesh.arquivo.c_str());
                if(mesh)
                {
						SceneManager->addLightSceneNode(0, core::vector3df(0,0,0), 
						video::SColorf(1.0f, 0.6f, 0.7f, 1.0f), 600.0f);
                        
                        node = SceneManager->addAnimatedMeshSceneNode(mesh);
                        
                        JanelaTesteKinect::sensor->iniciar();
                        
                        node->setPosition(core::vector3df(30,0,-10));
                        node->setRotation(core::vector3df(p.rotacao.x,p.rotacao.y,p.rotacao.z));
                        
						node->addShadowVolumeSceneNode();
						SceneManager->setShadowColor(video::SColor(220,0,0,0));

	
						
						node->setMaterialFlag(video::EMF_NORMALIZE_NORMALS, true);
						
						//node->setScale(core::vector3df(p.escala.x,p.escala.y,p.escala.z));
						node->setScale(core::vector3df(10,10,10));
                                                //node->setScale(core::vector3df(100,100,100));
                        node->setVisible(true);
                        node->setMaterialFlag(EMF_LIGHTING, true);
                                                //node->setMaterialFlag(E_MATERIAL_FLAG::EMF_NORMALIZE_NORMALS,true);
                                                //node->setAutomaticCulling(false);
                                                //node->setAutomaticCulling(EAC_FRUSTUM_SPHERE);
                        
                        //node->setMaterialTexture(1,SceneManager->getVideoDriver()->getTexture("modelos/personagem/crianca1/textures/texture.png"));

                        //JanelaEscolhaPersonagem::nodes.push_back(node);
                        //int matNum = node->getMaterialCount();
                        
                        //SMaterial mat = node->getMaterial(0);
                                                
                                                //node->setJointMode(irr::scene::E_JOINT_UPDATE_ON_RENDER::EJUOR_CONTROL);
                        std::string mao_esquerda_bone_teste				=       "Foot_R";    
						std::string ombro_esquerd_bone_teste			=       "UpLeg_R";
						std::string braco_esqerdo_bone_teste			=       "LoLeg_R";
						irr::scene::IBoneSceneNode * mao		= node->getJointNode(mao_esquerda_bone_teste.c_str());
						irr::scene::IBoneSceneNode * cotovelo	= node->getJointNode(braco_esqerdo_bone_teste.c_str());
						irr::scene::IBoneSceneNode * ombro		= node->getJointNode(ombro_esquerd_bone_teste.c_str());
                        
						irr::core::vector3df rot = ombro->getRotation();
						irr::core::vector3df rot2 = cotovelo->getRotation();
						rot.Y = 90;
					
						rot.Z = 0;
						ombro->setRotation(rot);

						/*********************/
						
						irr::scene::IBoneSceneNode * cotovelo_2	= node->getJointNode("LoLeg_L");
						irr::scene::IBoneSceneNode * ombro_2		= node->getJointNode("UpLeg_L");
                        
						irr::core::vector3df rot_ = ombro_2->getRotation();
						irr::core::vector3df rot2_ = cotovelo_2->getRotation();
						rot_.Y = -90;
					
						rot_.Z = 0;
						ombro_2->setRotation(rot_);
					

                                                node->setJointMode(EJUOR_CONTROL);
                                                
                                                mesh->drop();
                                                avatar = new Avatar(SceneManager,char_mesh,vector<MarcadorPedra*>());

                                                avatar->setNode(node);

                }
                JanelaTesteKinect::primeiro = false;
                Esqueleto e1;
                e1.ombro_direito.x=1;
                e1.ombro_direito.y=1;
                e1.ombro_direito.z=1;
                
                e1.cotovelo_direito.x=3;
                e1.cotovelo_direito.y=3;
                e1.cotovelo_direito.z=1;

                e1.mao_direita.x = 4;
                e1.mao_direita.y = 2;
                e1.mao_direita.z = 0;

                e1.ombro_esquerdo.x=-1;
                e1.ombro_esquerdo.y=-1;
                e1.ombro_esquerdo.z=-1;
                
                e1.cotovelo_esquerdo.x=-3;
                e1.cotovelo_esquerdo.y=-3;
                e1.cotovelo_esquerdo.z=-1;

                e1.mao_esquerda.x = -4;
                e1.mao_esquerda.y = -2;
                e1.mao_esquerda.z = 0;

                /*----------------------------*/
                Esqueleto e2;
                e2.ombro_direito.x=1;
                e2.ombro_direito.y=1;
                e2.ombro_direito.z=1;
                
                e2.cotovelo_direito.x=2;
                e2.cotovelo_direito.y=3;
                e2.cotovelo_direito.z=1;

                e2.mao_direita.x = 4;
                e2.mao_direita.y = 2;
                e2.mao_direita.z = 0;

                e2.ombro_esquerdo.x=1;
                e2.ombro_esquerdo.y=1;
                e2.ombro_esquerdo.z=1;
                
                e2.cotovelo_esquerdo.x=3;
                e2.cotovelo_esquerdo.y=3;
                e2.cotovelo_esquerdo.z=1;

                e2.mao_esquerda.x = 4;
                e2.mao_esquerda.y = 2;
                e2.mao_esquerda.z = 0;

                /*--------------------------------*/
                Esqueleto e3;
                e3.ombro_direito.x=1;
                e3.ombro_direito.y=1;
                e3.ombro_direito.z=1;
                
                e3.cotovelo_direito.x=1;
                e3.cotovelo_direito.y=3;
                e3.cotovelo_direito.z=1;

                e3.mao_direita.x = 4;
                e3.mao_direita.y = 2;
                e3.mao_direita.z = 0;

                e3.ombro_esquerdo.x=1;
                e3.ombro_esquerdo.y=1;
                e3.ombro_esquerdo.z=1;
                
                e3.cotovelo_esquerdo.x=3;
                e3.cotovelo_esquerdo.y=3;
                e3.cotovelo_esquerdo.z=1;

                e3.mao_esquerda.x = 4;
                e3.mao_esquerda.y = 2;
                e3.mao_esquerda.z = 0;


                esqueletos.push_back(e1);
                esqueletos.push_back(e2);
                esqueletos.push_back(e3);
                FILE * file = NULL;
                fopen_s(&file,"bones.txt","w+t");
                for(int i=0;i<node->getJointCount();i++)
                {
                        IBoneSceneNode * bone = node->getJointNode(i);
                                                //bone->setSkinningSpace(irr::scene::E_BONE_SKINNING_SPACE::EBSS_LOCAL);
                        fprintf_s(file,"%d %s\n",i,bone->getName());

                }
                fclose(file);
        }
        else{
                //bool usarKinect = true;
                                bool usarKinectOuArquivo = false;
                                bool usarKinect = false;
                bool salvarNoArquivo = true;
                                bool usarArquivo = ! usarKinect && usarKinectOuArquivo;
                                bool testeSubir = true;
                //bool aquelaClasse = true;
              //  node->setRotation(core::vector3df(180,180,0));    
                if(usarKinect)
                {
                        
                        JanelaTesteKinect::sensor->processar();
                        if(JanelaTesteKinect::sensor->getUsuariosAtivos()>0){
                                //printf("capturado\n");
                                Esqueleto esqueleto = JanelaTesteKinect::sensor->capturar();
                                avatar->atualizarPosicao(esqueleto);
                                boneco->setEsqueleto(esqueleto);
                                boneco->desenhar(SceneManager->getVideoDriver());
                                if(salvarNoArquivo)
                                {
                                                                        bool comIntervalo = false;
                                                                        if(comIntervalo)
                                                                        {
                                                                                /*
                                                if(!cronometro.iniciado())
                                                        cronometro.iniciarContagem();
                                                if(cronometro.getTempoCorridoSegundos()==2){
                                                        atualizaPosBoneco(esqueleto);   
                                                        cronometro.pararContagem();
                                                }
                                                                                                */
                                                                        }
                                                                        else
                                                                        {
                                                                                 atualizaPosBoneco(esqueleto);   
                                                                        }
                                }
                        }

                }

                if(usarArquivo)
                {
                        vector<Esqueleto> esqueletos = JanelaTesteKinect::lerDoArquivo();
                        bool comTempo = false;
                                                //i=495;
                                                //i=10;
                                                //i=180;
                        Esqueleto esqueleto = esqueletos[i];
                        
                        if(!cronometro.iniciado())
                                cronometro.iniciarContagem();
                                                if(comTempo)
                                                {
                                                if(cronometro.getTempoCorridoSegundos()==2){
                                //atualizaPosBoneco(esqueleto); 
                                                        esqueleto=boneco->ajustarEsqueleto(esqueleto);   
                                                        esqueleto=boneco->ajustarEsqueleto(esqueleto);   
                                                        boneco->setEsqueleto(esqueleto);
                                
                                avatar->atualizarPosicao(esqueleto);
                                cronometro.pararContagem();
                                printf("i = %d\n",i);
                                i++;
                                if(i==esqueletos.size())
                                        i=0;
                                                                
                        }
                                                }else{
                                                        //atualizaPosBoneco(esqueleto); 
                                                        //esqueleto = moverBonecoProLado(esqueleto);
                                                        esqueleto=boneco->ajustarEsqueleto(esqueleto);   
                                                        esqueleto=boneco->ajustarEsqueleto(esqueleto);   
                                                        boneco->setEsqueleto(esqueleto);                                
                                                        avatar->atualizarPosicao(esqueleto);
                                                        boneco->desenhar(SceneManager->getVideoDriver());
                                                        
                            //cronometro.pararContagem();
                            printf("i = %d\n",i);
                            i++;
                                                        if(i==esqueletos.size())
                                                                i=0;
                                                }
                                                
                                                
                                                
                                                
                }

                                if(testeSubir)
                                {

                                        if(!cronometroParaSubir.iniciado())
                                                        cronometroParaSubir.iniciarContagem();
                                        if(cronometroParaSubir.getTempoCorridoMiliSegundos() >= 100)
                                                {
                                                        cronometroParaSubir.reiniciarContagem();
                                                        if(indiceSubir<50)
                                                        {
                                                                if(subir)
                                                                {
                                                                        avatar->subirPersonagem(1);
                                                                }else
                                                                {
                                                                        avatar->subirPersonagem(-1);
                                                                }
                                                        }else 
                                                        {
                                                                indiceSubir = 0;
                                                                subir= !subir;
                                                        }
                                                        
                                                        indiceSubir++;

                                                }


                                }
                

                        
                

        }
                /*
                irr::scene::IBoneSceneNode * bone_braco = node->getJointNode("Scene_root_LoArm_L");
                vector3df rot = bone_braco->getRotation();
                rot.X+=10;
                bone_braco->setRotation(rot);
                if(!cronometro.iniciado())
                        cronometro.iniciarContagem();
                if(cronometro.getTempoCorridoSegundos()==2){
                        
                        avatar->atualizarPosicao(esqueletos[i]);
                        i++;
                        if(i==esqueletos.size())
                                i=0;
                        cronometro.pararContagem();
                }*/
                
                
        
        

}

void JanelaTesteKinect::atualizaPosBoneco(Esqueleto e)
{
        //JanelaTesteKinect::boneco->setEsqueleto(e);
        FILE * file =NULL;
                fopen_s(&file,posicoes.c_str(),"a+t");
        fprintf_s(file,"%f %f %f\n",e.abdomen.x,e.abdomen.y,e.abdomen.z);
        fprintf_s(file,"%f %f %f\n",e.cabeca.x,e.cabeca.y,e.cabeca.z);
        fprintf_s(file,"%f %f %f\n",e.cotovelo_direito.x,e.cotovelo_direito.y,e.cotovelo_direito.z);
        fprintf_s(file,"%f %f %f\n",e.cotovelo_esquerdo.x,e.cotovelo_esquerdo.y,e.cotovelo_esquerdo.z);
        fprintf_s(file,"%f %f %f\n",e.joelho_direito.x,e.joelho_direito.y,e.joelho_direito.z);
        fprintf_s(file,"%f %f %f\n",e.joelho_esquerdo.x,e.joelho_esquerdo.y,e.joelho_esquerdo.z);
        fprintf_s(file,"%f %f %f\n",e.mao_direita.x,e.mao_direita.y,e.mao_direita.z);
        fprintf_s(file,"%f %f %f\n",e.mao_esquerda.x,e.mao_esquerda.y,e.mao_esquerda.z);
        fprintf_s(file,"%f %f %f\n",e.ombro_direito.x,e.ombro_direito.y,e.ombro_direito.z);
        fprintf_s(file,"%f %f %f\n",e.ombro_esquerdo.x,e.ombro_esquerdo.y,e.ombro_esquerdo.z);
        fprintf_s(file,"%f %f %f\n",e.pe_direito.x,e.pe_direito.y,e.pe_direito.z);
        fprintf_s(file,"%f %f %f\n",e.pe_esquerdo.x,e.pe_esquerdo.y,e.pe_esquerdo.z);
        fclose(file);
}

vector<Esqueleto> JanelaTesteKinect::lerDoArquivo()
{
        vector<Esqueleto> esqueletos;

        FILE * file =NULL;
        fopen_s(&file,posicoes.c_str(),"rt");
        while(!feof(file))
        {
                Esqueleto e;
                fscanf_s(file,"%f %f %f\n",&e.abdomen.x,&e.abdomen.y,&e.abdomen.z);
                fscanf_s(file,"%f %f %f\n",&e.cabeca.x,&e.cabeca.y,&e.cabeca.z);
                fscanf_s(file,"%f %f %f\n",&e.cotovelo_direito.x,&e.cotovelo_direito.y,&e.cotovelo_direito.z);
                fscanf_s(file,"%f %f %f\n",&e.cotovelo_esquerdo.x,&e.cotovelo_esquerdo.y,&e.cotovelo_esquerdo.z);
                fscanf_s(file,"%f %f %f\n",&e.joelho_direito.x,&e.joelho_direito.y,&e.joelho_direito.z);
                fscanf_s(file,"%f %f %f\n",&e.joelho_esquerdo.x,&e.joelho_esquerdo.y,&e.joelho_esquerdo.z);
                fscanf_s(file,"%f %f %f\n",&e.mao_direita.x,&e.mao_direita.y,&e.mao_direita.z);
                fscanf_s(file,"%f %f %f\n",&e.mao_esquerda.x,&e.mao_esquerda.y,&e.mao_esquerda.z);
                fscanf_s(file,"%f %f %f\n",&e.ombro_direito.x,&e.ombro_direito.y,&e.ombro_direito.z);
                fscanf_s(file,"%f %f %f\n",&e.ombro_esquerdo.x,&e.ombro_esquerdo.y,&e.ombro_esquerdo.z);
                fscanf_s(file,"%f %f %f\n",&e.pe_direito.x,&e.pe_direito.y,&e.pe_direito.z);
                fscanf_s(file,"%f %f %f\n",&e.pe_esquerdo.x,&e.pe_esquerdo.y,&e.pe_esquerdo.z);
                esqueletos.push_back(e);
        }
        fclose(file);

        return esqueletos;
}

bool JanelaTesteKinect::OnEvent(const SEvent& event)
{
        core::vector3df rot;
		if(camera)
			camera->OnEvent(event);
        /*
        switch (event.KeyInput.Key)
        {
        case KEY_KEY_Q:
                printf("q\n");
                rot =  node->getRotation();
                rot.X+=5;
                node->setRotation(rot);
                break;
        case KEY_KEY_W:
                printf("w\n");
                rot =  node->getRotation();
                rot.X-=5;
                node->setRotation(rot);
                break;

        case KEY_KEY_A:
                printf("A\n");
                rot =  node->getRotation();
                rot.Y+=5;
                node->setRotation(rot);
                break;

        case KEY_KEY_S:
                printf("w\n");
                rot =  node->getRotation();
                rot.Y-=5;
                node->setRotation(rot);
                break;

        case KEY_KEY_Z:
                printf("Z\n");
                rot =  node->getRotation();
                rot.Z+=5;
                node->setRotation(rot);
                break;

        case KEY_KEY_X:
                printf("X\n");
                rot =  node->getRotation();
                rot.Z-=5;
                node->setRotation(rot);
                break;

        }
        rot =  node->getRotation();
        printf("%f,%f,%f\n",rot.X,rot.Y,rot.Z);
        */
        return true;
}

tipos::Esqueleto JanelaTesteKinect::moverBonecoProLado(tipos::Esqueleto esqueleto)
{
        int menorX = 999999999999;
        Vetor ** joints =  esqueleto.getJoints();
        for(int i=0;i<esqueleto.qtd;i++)
        {
                if(joints[i]->x<menorX)
                        menorX = joints[i]->x;

        }
        menorX = - menorX;
        for(int i=0;i<esqueleto.qtd;i++)
        {
                joints[i]->x += menorX;                 

        }
        return esqueleto;
}