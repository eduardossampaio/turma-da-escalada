#include "stdafx.h"
#include "MovimentadorBracoEsquerdo.h"
#include "CalculosUteis.h"




MovimentadorBracoEsquerdo::~MovimentadorBracoEsquerdo(void)
{
}
MovimentadorBracoEsquerdo::MovimentadorBracoEsquerdo(vector<MarcadorPedra *> marcadores):marcadores(marcadores),indiceAnterior(-1),indiceAtual(-1),terminado(false){}
void MovimentadorBracoEsquerdo::mover(irr::scene::IAnimatedMeshSceneNode * node,tipos::Esqueleto esqueleto) 
{
	std::string ombro_esquerdo_bone			=       "UpArm_L";
	std::string braco_esquerdo_bone			=       "LoArm_L";
	std::string mao_esquerda_bone			=		"Index_L";

	float anguloOmbroEsquerdo = getAnguloBraco(esqueleto.ombro_esquerdo,esqueleto.cotovelo_esquerdo);	
	setarAnguloBone(node,ombro_esquerdo_bone,-anguloOmbroEsquerdo);		
	float anguloMaoEsquerda = CalculosUteis::anguloEntrePontos(esqueleto.cotovelo_esquerdo,esqueleto.ombro_esquerdo,esqueleto.mao_esquerda);
	if(esqueleto.cotovelo_esquerdo.y < esqueleto.mao_esquerda.y)
		anguloMaoEsquerda = - anguloMaoEsquerda;
	if(!_isnan(anguloMaoEsquerda))
		setarAnguloBone(node,braco_esquerdo_bone,anguloMaoEsquerda);


	IBoneSceneNode * mao = node->getJointNode(mao_esquerda_bone.c_str());
	pos = Vetor(
		mao->getAbsolutePosition().X,
		mao->getAbsolutePosition().Y,
		mao->getAbsolutePosition().Z);
	//teste
	/*
	bool tem = false;
	for(int i=0;i<marcadores.size();i++)
	{
		if(marcadores[i]->pontoDentroMarcador(pos) && i!=indiceAnterior)
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
bool MovimentadorBracoEsquerdo::terminou() 
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
//	return cronometro.getTempoCorridoSegundos() >= 3;
	  if(!cronometro.iniciado())
                                cronometro.iniciarContagem();
	if(cronometro.getTempoCorridoSegundos()>=5)
	{
		if(verificaMembroMarcador(pos,marcadores))
			return true;
		else
		{
			cronometro.reiniciarContagem();
		}
	}
                        return false;
}
void MovimentadorBracoEsquerdo::reset() 
{
	cronometro.pararContagem();
}
	