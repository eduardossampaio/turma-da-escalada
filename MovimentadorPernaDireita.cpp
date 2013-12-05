#include "stdafx.h"
#include "MovimentadorPernaDireita.h"
#include "CalculosUteis.h"


MovimentadorPernaDireita::MovimentadorPernaDireita(vector<MarcadorPedra *> marcadores):marcadores(marcadores),indiceAnterior(-1)
{
}


MovimentadorPernaDireita::~MovimentadorPernaDireita(void)
{
}

void MovimentadorPernaDireita::mover(irr::scene::IAnimatedMeshSceneNode * node,tipos::Esqueleto esqueleto)
{
	std::string coxa_esquerda_bone			=       "UpLeg_L";
	std::string perna_esquerda_bone			=       "LoLeg_L";
	std::string pe_esquerdo_bone_1             =       "Foot_L";
	std::string pe_esquerdo_bone_2             =       "Toe_L";

	tipos::Vetor v3_ = Vetor(esqueleto.joelho_esquerdo.x,esqueleto.abdomen.y);
	Vetor p1_ = esqueleto.abdomen;
	Vetor p2_ = esqueleto.joelho_esquerdo;
	Vetor p3_ = v3_;
	float a1_ = CalculosUteis::anguloEntrePontos(p1_,p2_,p3_);
	if(!_isnan(a1_))
		setarAnguloBone(node,coxa_esquerda_bone,-90 + a1_);
	//setarAnguloPerna(node,coxa_direita_bone,90-a1_);


	float angulo_joelho = CalculosUteis::anguloEntrePontos(esqueleto.joelho_esquerdo,esqueleto.abdomen,esqueleto.pe_esquerdo);
	if(!_isnan(angulo_joelho))
	{

		setarAnguloPerna(node,perna_esquerda_bone, angulo_joelho);

		IBoneSceneNode * joelho = node->getJointNode(perna_esquerda_bone.c_str());
		core::vector3df rot=  joelho->getRotation();
		//rot.Y = angulo_joelho; 
		rot.Z = 180;
		joelho->setRotation(rot);


	}
	//

	IBoneSceneNode * pe_1 = node->getJointNode(pe_esquerdo_bone_1.c_str());
	IBoneSceneNode * pe_2 = node->getJointNode(pe_esquerdo_bone_2.c_str());
	pos_1 = Vetor(pe_1->getAbsolutePosition().X,pe_1->getAbsolutePosition().Y,pe_1->getAbsolutePosition().Z);
	pos_2 = Vetor(pe_2->getAbsolutePosition().X,pe_2->getAbsolutePosition().Y,pe_2->getAbsolutePosition().Z);
/*
	bool tem = false;
	for(int i=0;i<marcadores.size();i++)
	{
		if( ( (marcadores[i]->pontoDentroMarcador(pos_1)) || (marcadores[i]->pontoDentroMarcador(pos_2)) ) && i!=indiceAnterior)
		{
			if(!cronometro.iniciado())
			{
				cronometro.iniciarContagem();						
			}
			tem = true;
			indiceAtual = i;
		}
	}
	if(!tem)
	{
		cronometro.pararContagem();
	}
	*/
}
bool MovimentadorPernaDireita::terminou()
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
void MovimentadorPernaDireita::reset()
{
	cronometro.pararContagem();
}