#include "stdafx.h"
#include "MovimentadorPernaEsquerda.h"

#include "CalculosUteis.h"
MovimentadorPernaEsquerda::MovimentadorPernaEsquerda(vector<MarcadorPedra *> marcadores):marcadores(marcadores),indiceAnterior(-1)
{
}


MovimentadorPernaEsquerda::~MovimentadorPernaEsquerda(void)
{
}

void MovimentadorPernaEsquerda:: mover(irr::scene::IAnimatedMeshSceneNode * node,tipos::Esqueleto esqueleto) 
{
	std::string coxa_direita_bone			=       "UpLeg_R";
	std::string perna_direita_bone			=       "LoLeg_R";
	std::string pe_direito_bone_1             =       "Foot_R";
	std::string pe_direito_bone_2             =       "Toe_R";
	Vetor p1 = esqueleto.abdomen;
	Vetor p2 = esqueleto.joelho_direito;
	Vetor p3 = Vetor(esqueleto.joelho_direito.x,esqueleto.abdomen.y);	
	float a1 = CalculosUteis::anguloEntrePontos(p1,p2,p3);
	if(!_isnan(a1))
		setarAnguloPerna(node,coxa_direita_bone,90 - a1);

	Vetor p2p4 = Vetor(esqueleto.pe_direito.x,esqueleto.joelho_direito.y);
	float a2 = CalculosUteis::anguloEntrePontos(p2,esqueleto.abdomen,esqueleto.pe_direito);
	//if(!_isnan(a2))			
//		

	if(!_isnan(a2))
	{

		setarAnguloPerna(node,perna_direita_bone,-a2);

		IBoneSceneNode * joelho = node->getJointNode(perna_direita_bone.c_str());
		core::vector3df rot=  joelho->getRotation();
		//rot.Y = angulo_joelho; 
		rot.Z = 180;
		joelho->setRotation(rot);


	}

	/*
		float angulo_joelho = CalculosUteis::anguloEntrePontos(esqueleto.joelho_esquerdo,esqueleto.abdomen,esqueleto.pe_esquerdo);
	if(!_isnan(angulo_joelho))
	{

		setarAnguloPerna(node,perna_esquerda_bone, angulo_joelho);

		IBoneSceneNode * joelho = node->getJointNode(perna_esquerda_bone.c_str());
		core::vector3df rot=  joelho->getRotation();
		//rot.Y = angulo_joelho; 
		rot.Z = 180;
		joelho->setRotation(rot);


	}*/


	IBoneSceneNode * pe_1 = node->getJointNode(pe_direito_bone_1.c_str());
	IBoneSceneNode * pe_2 = node->getJointNode(pe_direito_bone_2.c_str());
	pos_1 = Vetor(pe_1->getAbsolutePosition().X,pe_1->getAbsolutePosition().Y,pe_1->getAbsolutePosition().Z);
	pos_2 = Vetor(pe_2->getAbsolutePosition().X,pe_2->getAbsolutePosition().Y,pe_2->getAbsolutePosition().Z);
	/*
	bool tem = false;
	for(int i=0;i<marcadores.size();i++)
	{
		if( (marcadores[i]->pontoDentroMarcador(pos_1) || (marcadores[i]->pontoDentroMarcador(pos_2))) && i!=indiceAnterior)
		{
			if(!cronometro.iniciado())
			{
				cronometro.iniciarContagem();						
			}
			tem = true;
			//indiceAnterior = -1;
			indiceAtual = i;
		}
	}
	if(!tem)
	{
		cronometro.pararContagem();
	}
	*/
}
bool MovimentadorPernaEsquerda::terminou() 
{

		/*
	if( cronometro.getTempoCorridoSegundos()>=3 )
	{
		cronometro.pararContagem();
		indiceAnterior = indiceAtual;
		return true;
	}
	return false;
	*/
	//return cronometro.getTempoCorridoSegundos() >= 3;
	  if(!cronometro.iniciado())
		cronometro.iniciarContagem();
	if(cronometro.getTempoCorridoSegundos()>=5)
	{
		if(verificaMembroMarcador(pos_1,marcadores) || verificaMembroMarcador(pos_2,marcadores))
			return true;
		else
		{
			cronometro.reiniciarContagem();
		}
	}
	return false;

}
void MovimentadorPernaEsquerda::reset() 
{
	cronometro.pararContagem();
}