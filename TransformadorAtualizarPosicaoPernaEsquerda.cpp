#include "stdafx.h"
#include "TransformadorAtualizarPosicaoPernaEsquerda.h"
#include "tipos.h"
#include "CalculosUteis.h"
using namespace irr;
using namespace scene;
TransformadorAtualizarPosicaoPernaEsquerda::TransformadorAtualizarPosicaoPernaEsquerda(IAnimatedMeshSceneNode * node)
{
		
	posPe = Vetor(node->getJointNode("Foot_L")->getAbsolutePosition().X,node->getJointNode("Foot_L")->getAbsolutePosition().Y,
	node->getJointNode("Foot_L")->getAbsolutePosition().Z);
}


TransformadorAtualizarPosicaoPernaEsquerda::~TransformadorAtualizarPosicaoPernaEsquerda(void)
{
}
void TransformadorAtualizarPosicaoPernaEsquerda::transformar(irr::scene::IAnimatedMeshSceneNode * node, tipos::Esqueleto esqueleto)
{

	IBoneSceneNode * quadril = node->getJointNode("UpLeg_L");
	IBoneSceneNode * joelho = node->getJointNode("LoLeg_L");
	float menorDistancia = 999;
	float anguloOmbro = 0;
	float anguloCotovelo = 0;
	int anguloMinimoOmbro = 0;
	int anguloMaximoOmbro = 180;
	int anguloMinimoCotovelo = 0 ;
	int anguloMaximoCotovelo = 180;
	for (int i = anguloMinimoCotovelo ;i < anguloMaximoCotovelo ;i++)
	{
		core::vector3df rotOmbro = quadril->getRotation();
		rotOmbro.Y = i;
		quadril->setRotation(rotOmbro);
		for(int j =anguloMinimoCotovelo ; j< anguloMaximoCotovelo ;j++)
		{
			core::vector3df rotCot = joelho->getRotation();
			rotCot.Y = j;
			joelho->setRotation(rotCot);
			IBoneSceneNode * mao = node->getJointNode("Foot_L");
			
			node->updateAbsolutePosition();
			for(int i=0;i<node->getJointCount();i++)
			{
				node->getJointNode(i)->updateAbsolutePosition();
			}
			Vetor pos = Vetor(mao->getAbsolutePosition().X,mao->getAbsolutePosition().Y,mao->getAbsolutePosition().Z);
			float distancia = CalculosUteis::distanciaEntrePontos( pos,posPe);
			if(distancia<menorDistancia)
			{
				menorDistancia = distancia;
				anguloOmbro = i;
				anguloCotovelo = j;
			}


			
		}
		
		
	}

	printf("i: %f j: %f distancia : %f\n",anguloOmbro,anguloCotovelo,menorDistancia);
	core::vector3df rotOmbro = quadril->getRotation();
		rotOmbro.Y = anguloOmbro;
		quadril->setRotation(rotOmbro);

		core::vector3df rotCot = joelho->getRotation();
		rotCot.Y = anguloCotovelo;
		joelho->setRotation(rotCot);

}

/*

	std::string pe_direito_bone				=       "Foot_L";    
	std::string ombro_esquerd_bone_teste	=       "UpLeg_L";
	std::string braco_esqerdo_bone_teste	=       "LoLeg_L";

	irr::scene::IBoneSceneNode * pe		= node->getJointNode(pe_direito_bone.c_str());
	irr::scene::IBoneSceneNode * joelho	= node->getJointNode(braco_esqerdo_bone_teste.c_str());
	irr::scene::IBoneSceneNode * coxa		= node->getJointNode(ombro_esquerd_bone_teste.c_str());
	
	
	
	
	irr::core::vector3df	posJoelho		= joelho->getAbsolutePosition();
	irr::core::vector3df	posOmbro		= coxa->getAbsolutePosition();

	Vetor posJoelhoFinal;
	Vetor posCoxaFinal;

	irr::core::vector3df nodePosition = node->getAbsolutePosition();
	posJoelhoFinal.x = posJoelho.X * 10 + nodePosition.X;
	posJoelhoFinal.y = posJoelho.Y * 10 + nodePosition.Y;
	
	
	posCoxaFinal.x = posOmbro.X * 10 + nodePosition.X;
	posCoxaFinal.y = posOmbro.Y * 10 + nodePosition.Y;
	


	
	if(TransformadorAtualizarPosicaoPernaEsquerda::primeiro)
	{
		TransformadorAtualizarPosicaoPernaEsquerda::primeiro = false;
		
		pe->updateAbsolutePosition();
		irr::core::vector3df	posPeTemp		= pe->getAbsolutePosition();
		

		TransformadorAtualizarPosicaoPernaEsquerda::posPe.x = posPeTemp.X + nodePosition.X;
		TransformadorAtualizarPosicaoPernaEsquerda::posPe.y = posPeTemp.Y + nodePosition.Y;
	}

		TransformadorAtualizarPosicaoPernaEsquerda::distanciaJoelhoPe = 
			CalculosUteis::distanciaEntrePontos(posJoelhoFinal,posPe);
	
		TransformadorAtualizarPosicaoPernaEsquerda::distanciaPernaJoelho = 
			CalculosUteis::distanciaEntrePontos(posCoxaFinal,posJoelhoFinal);

	

	
	
	float distanciaOmbroMao = CalculosUteis::distanciaEntrePontos(posCoxaFinal,posPe);
	
	float x = distanciaPernaJoelho;
	float y = distanciaJoelhoPe;
	float z = distanciaOmbroMao;

	float alfa = (x*x + z*z - y*y) / (2*x*z);
	float anguloOmbro =irr::core::radToDeg(acos(  alfa ));

	Vetor pontoAuxiliarCoxa = Vetor(posJoelho.X,posOmbro.Y);
	
	float anguloCoxaComplementar = CalculosUteis::anguloEntrePontos(posCoxaFinal,pontoAuxiliarCoxa,posJoelhoFinal);
	
	irr::core::vector3df rotCoxa = coxa->getRotation();
	rotCoxa.Y = - (90 -( anguloCoxaComplementar ) );
	
	coxa->setRotation(rotCoxa);

	float beta = (x*x + y*y - z*z) / (2*x*y);
	float anguloCotovelo = irr::core::radToDeg(acos(beta));
	
	
	irr::core::vector3df rotCotovelo = joelho->getRotation();
	//rotCotovelo.Y =   -( anguloCotovelo );

	joelho->setRotation(rotCotovelo);*/