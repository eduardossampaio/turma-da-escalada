#include "stdafx.h"
#include "MovimentadorMembro.h"
#include "CalculosUteis.h"
using namespace core;
using namespace tipos;

MovimentadorMembro::MovimentadorMembro(void)
{
}


MovimentadorMembro::~MovimentadorMembro(void)
{
}



float MovimentadorMembro::getAnguloBraco(tipos::Vetor p1,tipos::Vetor p2)
{
	Vetor p1p2 = Vetor(p2.x,p1.y);
	if(p2.y < p1p2.y)
		return - CalculosUteis::anguloEntrePontos(p1,p2,p1p2);	
	return  CalculosUteis::anguloEntrePontos(p1,p2,p1p2);	

}
void MovimentadorMembro::setarAnguloBone(IAnimatedMeshSceneNode * node, std::string nome_bone,float angulo)
{
	IBoneSceneNode * bone = node->getJointNode(nome_bone.c_str());  
	if(bone)
	{
		core::vector3df rot = bone->getRotation();
		rot.Y = angulo;
		bone->setRotation(rot);               
	}

}
void MovimentadorMembro::setarAnguloPerna(IAnimatedMeshSceneNode * node,std::string nome_bone,float angulo)
{
	std::string pe_esquerdo_bone			=       "Foot_L";
	std::string coxa_direita_bone			=       "UpLeg_R";
	std::string coxa_esquerda_bone			=       "UpLeg_L";
	std::string perna_esquerda_bone			=       "LoLeg_L";
	IBoneSceneNode * coxaDir = node->getJointNode(coxa_direita_bone.c_str());
	if(coxaDir)
	{
		irr::core::vector3df rot = coxaDir->getRotation();
		rot.Z = 0;
		coxaDir->setRotation(rot);
	}

	IBoneSceneNode * coxaEsq = node->getJointNode(coxa_esquerda_bone.c_str());
	if(coxaEsq)
	{
		irr::core::vector3df rot = coxaEsq->getRotation();
		rot.Z = 0;
		coxaEsq->setRotation(rot);
	}


	IBoneSceneNode * bone = node->getJointNode(nome_bone.c_str());  
	if(bone)
	{
		vector3df rot = bone->getRotation();
		rot.Y = angulo;

		bone->setRotation(rot);               
	}
}

bool MovimentadorMembro::verificaMembroMarcador(Vetor posBone,vector<MarcadorPedra*> marcadores)
{

	for(int i=0;i<marcadores.size();i++)
	{
		if(marcadores[i]->pontoDentroMarcador(posBone))
			return true;
	}
	return false;

}


