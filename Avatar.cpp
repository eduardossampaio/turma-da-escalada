#include "stdafx.h"
#include "Avatar.h"
#include "irrlicht.h"
#include "CalculosUteis.h"
#include "TransformadorKinect.h"
#include "TransformadorAtualizacaoPosicao.h"

using namespace irr;
using namespace core;
using namespace gui;
using namespace video;
using namespace scene;

std::string Avatar::root_bone                   =       "Root";
std::string Avatar::scene_root_bone             =       "Scene_root";
std::string Avatar::root_root_bone              =       "Root";
std::string Avatar::quadril_bone                =       "Hips";
std::string Avatar::coxa_esquerda_bone			=       "UpLeg_L";
std::string Avatar::perna_esquerda_bone			=       "LoLeg_L";
std::string Avatar::pe_esquerdo_bone			=       "Foot_L";
std::string Avatar::coxa_direita_bone			=       "UpLeg_R";
std::string Avatar::perna_direita_bone			=       "LoLeg_R";
std::string Avatar::pe_direito_bone             =       "Foot_R";
std::string Avatar::coluna1_bone                =       "Spine1";
std::string Avatar::coluna2_bone                =       "Spine2";
std::string Avatar::ombro_esquerdo_bone			=       "UpArm_L";
std::string Avatar::braco_esquerdo_bone			=       "LoArm_L";
std::string Avatar::mao_esquerda_bone			=       "Hand_L";    
std::string Avatar::ombro_direito_bone			=       "UpArm_R";
std::string Avatar::braco_direito_bone			=       "LoArm_R";
std::string Avatar::mao_direita_bone			=       "Hand_R";
std::string Avatar::pescoco_bone                =       "Neck";
std::string Avatar::cabeca_bone                 =       "Head";



Avatar::Avatar(irr::scene::ISceneManager * mgr,tipos::Mesh_Info info,vector<MarcadorPedra *> marcadores):mgr(mgr),info(info),marcadores(marcadores)
{
        Avatar::esqueleto = esqueleto;
		
		Avatar::bones[0]=Avatar::root_bone;
		Avatar::bones[1]=Avatar::scene_root_bone;
		Avatar::bones[2]=Avatar::root_root_bone;
		Avatar::bones[3]=Avatar::quadril_bone;
		Avatar::bones[4]=Avatar::coxa_esquerda_bone;
		Avatar::bones[5]=Avatar::perna_esquerda_bone;
		Avatar::bones[6]=Avatar::pe_esquerdo_bone;
		Avatar::bones[7]=Avatar::coxa_direita_bone;
		Avatar::bones[8]=Avatar::perna_direita_bone;
		Avatar::bones[9]=Avatar::pe_direito_bone;
		Avatar::bones[10]=Avatar::coluna1_bone;
		Avatar::bones[11]=Avatar::coluna2_bone;
		Avatar::bones[12]=Avatar::ombro_esquerdo_bone;
		Avatar::bones[13]=Avatar::braco_esquerdo_bone;
		Avatar::bones[14]=Avatar::mao_esquerda_bone;
		Avatar::bones[15]=Avatar::ombro_direito_bone;
		Avatar::bones[16]=Avatar::braco_direito_bone;
		Avatar::bones[17]=Avatar::mao_direita_bone;
		Avatar::bones[18]=Avatar::pescoco_bone;
		Avatar::bones[19]=Avatar::cabeca_bone;

		transformadorTeste = new TransformadorKinect(marcadores);
		//transformadorSubir = new TransformadorAtualizacaoPosicao();
        


}


Avatar::~Avatar(void)
{
}

void Avatar::atualizarPosicao(tipos::Esqueleto esqueleto)
{
	core::vector3df v ;
	matrix4 m = matrix4(irr::core::CMatrix4<irr::f32>());
	
	
	transformadorTeste->transformar(node,esqueleto);

}
void Avatar::liberarBracoDireito(bool libera)
{
	Avatar::moveBracoDireito = libera;
}
void Avatar::liberarBracoEsquerdo(bool libera)
{
	Avatar::moveBracoEsquerdo = libera;
}
void Avatar::liberarPernaDireita(bool libera)
{
	Avatar::movePernaDireita = libera;
}
void Avatar::liberarPernaEsquerda(bool libera)
{
	Avatar::movePernaEsquerda = libera;
}
tipos::Esqueleto Avatar::getPosicao()
{
        return Avatar::esqueleto;
}

void Avatar::setNode(irr::scene::IAnimatedMeshSceneNode * node)
{
        Avatar::node = node;
		//node->setScale(core::vector3df(10,10,10));

}
irr::scene::IAnimatedMeshSceneNode * Avatar::getNode()
{
        return Avatar::node;
}

void Avatar::setarAnguloBone(std::string nome_bone,float angulo)
{
//      if(angulo>=0)
//      {

                IBoneSceneNode * bone = node->getJointNode(nome_bone.c_str());  
			if(bone)
			{
                vector3df rot = bone->getRotation();
				rot.Z = angulo;
				bone->setRotation(rot);
               // printf("angulo: %f",angulo);
			}
//      }

}

float Avatar::getAnguloBraco(tipos::Vetor p1,tipos::Vetor p2)
{
	Vetor p1p2 = Vetor(p2.x,p1.y);
	if(p2.y < p1p2.y)
		return CalculosUteis::anguloEntrePontos(p1,p2,p1p2);	
	return - CalculosUteis::anguloEntrePontos(p1,p2,p1p2);	
	
}
void Avatar::setarAnguloBraco(Vetor p1,Vetor p2,std::string nome_bone)
{
	IBoneSceneNode * bone	= node->getJointNode(nome_bone.c_str());
	
	Vetor p1p2 = Vetor(p2.x,p1.y);
	
	vector3df rot = bone->getRotation();
	float angulo = CalculosUteis::anguloEntrePontos(p1,p2,p1p2);
	if(p2.y < p1p2.y)
		rot.Z =  angulo;
	else
		rot.Z = -angulo;
	bone->setRotation(rot);
}

void Avatar::subirPersonagem(float valParaSubir)
{
	
	core::vector3df pos = Avatar::node->getAbsolutePosition();
	pos.Y +=valParaSubir;
	Avatar::node->setPosition(pos);
	node->updateAbsolutePosition();
//	transformadorSubir->transformar(node,esqueleto);
		
}