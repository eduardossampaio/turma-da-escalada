#include "stdafx.h"
#include "TransformadorKinect.h"
#include "CalculosUteis.h"
#include "MovimentadorBracoDireito.h"
#include "MovimentadorBracoEsquerdo.h"
#include "MovimentadorPernaDireita.h"
#include "MovimentadorPernaEsquerda.h"
#include "MovimentadorSubirPersonagem.h"
/*
std::string root_bone                   =       "Root";
std::string scene_root_bone             =       "Scene_root";
std::string root_root_bone              =       "Root";
std::string quadril_bone                =       "Hips";
std::string coxa_esquerda_bone			=       "UpLeg_L";
std::string perna_esquerda_bone			=       "LoLeg_L";
std::string pe_esquerdo_bone			=       "Foot_L";
std::string coxa_direita_bone			=       "UpLeg_R";
std::string perna_direita_bone			=       "LoLeg_R";
std::string pe_direito_bone             =       "Foot_R";
std::string coluna1_bone                =       "Spine1";
std::string coluna2_bone                =       "Spine2";
std::string ombro_esquerdo_bone			=       "UpArm_L";
std::string braco_esquerdo_bone			=       "LoArm_L";
std::string mao_esquerda_bone			=       "Hand_L";    
std::string ombro_direito_bone			=       "UpArm_R";
std::string braco_direito_bone			=       "LoArm_R";
std::string mao_direita_bone			=       "Hand_R";
std::string pescoco_bone                =       "Neck";
std::string cabeca_bone                 =       "Head";
*/



TransformadorKinect::TransformadorKinect(vector<MarcadorPedra *> marcadores):marcadores(marcadores)
{
	

	
	TransformadorKinect::movimentoBracoDireito	= new Cel_Movimentos();
	TransformadorKinect::movimentoBracoEsquerdo = new Cel_Movimentos();
	TransformadorKinect::movimentoPernaDireita	= new Cel_Movimentos();
	TransformadorKinect::movimentoPernaEsquerda	= new Cel_Movimentos();
	TransformadorKinect::movimentoSubir			= new Cel_Movimentos();
	
	
	TransformadorKinect::movimentoBracoDireito->movimento	= new MovimentadorBracoDireito(marcadores);
	TransformadorKinect::movimentoBracoEsquerdo->movimento	= new MovimentadorBracoEsquerdo(marcadores);
	TransformadorKinect::movimentoPernaDireita->movimento	= new MovimentadorPernaDireita(marcadores);
	TransformadorKinect::movimentoPernaEsquerda->movimento	= new MovimentadorPernaEsquerda(marcadores);
	TransformadorKinect::movimentoSubir->movimento			= new MovimentadorSubirPersonagem(marcadores);


	bool teste = false;
	if(!teste)
	{
	//esse aqui ta certo
		TransformadorKinect::movimentoBracoDireito->proximo		= TransformadorKinect::movimentoBracoEsquerdo;
		TransformadorKinect::movimentoBracoEsquerdo->proximo		= TransformadorKinect::movimentoPernaDireita;
		TransformadorKinect::movimentoPernaDireita->proximo		= TransformadorKinect::movimentoPernaEsquerda;
		TransformadorKinect::movimentoPernaEsquerda->proximo		= TransformadorKinect::movimentoSubir;
		TransformadorKinect::movimentoSubir->proximo				= TransformadorKinect::movimentoBracoDireito;

		TransformadorKinect::atual = TransformadorKinect::movimentoBracoDireito;
	}
	else
	{
	//esse aqui eh de teste
		TransformadorKinect::movimentoBracoDireito->proximo		= TransformadorKinect::movimentoBracoEsquerdo;
		TransformadorKinect::movimentoBracoEsquerdo->proximo		= TransformadorKinect::movimentoBracoDireito;
		//TransformadorKinect::movimentoSubir ->proximo			= TransformadorKinect::movimentoBracoDireito;
		
		//TransformadorKinect::movimentoPernaDireita->proximo		= TransformadorKinect::movimentoPernaEsquerda;
		//TransformadorKinect::movimentoPernaEsquerda->proximo		= TransformadorKinect::movimentoSubir;
		//TransformadorKinect::movimentoSubir->proximo				= TransformadorKinect::movimentoPernaDireita;
		//TransformadorKinect::atual = TransformadorKinect::movimentoPernaDireita;
		
		TransformadorKinect::atual = TransformadorKinect::movimentoBracoEsquerdo;
	}
	
	
}


TransformadorKinect::~TransformadorKinect(void)
{


}


void TransformadorKinect::transformar(irr::scene::IAnimatedMeshSceneNode * node,tipos::Esqueleto esqueleto) 
{
	/*
	for(int i=1;i<node->getJointCount();i++)
	{
		node->getJointNode(i)->updateAbsolutePosition();
	}
	*/
	TransformadorKinect::atual->movimento->mover(node,esqueleto);
	if(TransformadorKinect::atual->movimento->terminou())
	{
		TransformadorKinect::atual->movimento->reset();
		TransformadorKinect::atual = TransformadorKinect::atual->proximo;
	}

}


					 
