#include "stdafx.h"
#include "TransformadorAtualizarPosicaoBracoEsquerdo.h"
#include "CalculosUteis.h"
#include <math.h>
#include <irrlicht.h>
using namespace irr;
using namespace scene;

TransformadorAtualizarPosicaoBracoEsquerdo::TransformadorAtualizarPosicaoBracoEsquerdo(irr::scene::IAnimatedMeshSceneNode * node)
{
	TransformadorAtualizarPosicaoBracoEsquerdo::primeiro = true;
	
		esqueletoRef.abdomen = Vetor( node->getJointNode("Root")->getAbsolutePosition().X , node->getJointNode("Root")->getAbsolutePosition().Y, node->getJointNode("Root")->getAbsolutePosition().Z);
		esqueletoRef.ombro_esquerdo = Vetor( node->getJointNode("UpArm_L")->getAbsolutePosition().X , node->getJointNode("UpArm_L")->getAbsolutePosition().Y, node->getJointNode("UpArm_L")->getAbsolutePosition().Z);
		esqueletoRef.cotovelo_esquerdo = Vetor( node->getJointNode("LoArm_L")->getAbsolutePosition().X , node->getJointNode("LoArm_L")->getAbsolutePosition().Y, node->getJointNode("LoArm_L")->getAbsolutePosition().Z);
		esqueletoRef.mao_esquerda  = Vetor( node->getJointNode("Index_L")->getAbsolutePosition().X , node->getJointNode("Index_L")->getAbsolutePosition().Y, node->getJointNode("Index_L")->getAbsolutePosition().Z);

		distanciaCotoveloMao = CalculosUteis::distanciaEntrePontos(esqueletoRef.cotovelo_esquerdo,esqueletoRef.mao_esquerda);
		distanciaOmbroCotovelo = CalculosUteis::distanciaEntrePontos(esqueletoRef.ombro_esquerdo,esqueletoRef.cotovelo_esquerdo);
}


TransformadorAtualizarPosicaoBracoEsquerdo::~TransformadorAtualizarPosicaoBracoEsquerdo(void)
{
}

void TransformadorAtualizarPosicaoBracoEsquerdo::transformar(irr::scene::IAnimatedMeshSceneNode * node, tipos::Esqueleto esqueleto)
{

	IBoneSceneNode * ombro = node->getJointNode("UpArm_L");
	IBoneSceneNode * cotovelo = node->getJointNode("UpArm_L");
	float menorDistancia = 999;
	float anguloOmbro = 0;
	float anguloCotovelo = 0;
	int anguloMinimoOmbro = ombro->getRotation().Y - 20;
	int anguloMaximoOmbro = ombro->getRotation().Y + 20;
	int anguloMinimoCotovelo = cotovelo->getRotation().Y - 20;
	int anguloMaximoCotovelo = cotovelo->getRotation().Y + 20;
	for (int i = anguloMinimoCotovelo ;i < anguloMaximoCotovelo ;i++)
	{
		core::vector3df rotOmbro = ombro->getRotation();
		rotOmbro.Y = i;
		ombro->setRotation(rotOmbro);
		for(int j =anguloMinimoCotovelo ; j< anguloMaximoCotovelo ;j++)
		{
			core::vector3df rotCot = cotovelo->getRotation();
			rotCot.Y = j;
			cotovelo->setRotation(rotCot);
			IBoneSceneNode * mao = node->getJointNode("Hand_L");
			
			node->updateAbsolutePosition();
			for(int i=0;i<node->getJointCount();i++)
			{
				node->getJointNode(i)->updateAbsolutePosition();
			}
			float distancia = CalculosUteis::distanciaEntrePontos(
				Vetor(mao->getAbsolutePosition().X,mao->getAbsolutePosition().Y,mao->getAbsolutePosition().Z),
				esqueletoRef.mao_esquerda);
			if(distancia<menorDistancia)
			{
				menorDistancia = distancia;
				anguloOmbro = i;
				anguloCotovelo = j;
			}


			
		}
		
		
	}

	printf("i: %f j: %f distancia : %f\n",anguloOmbro,anguloCotovelo,menorDistancia);
	core::vector3df rotOmbro = ombro->getRotation();
		rotOmbro.Y = anguloOmbro;
		ombro->setRotation(rotOmbro);

		core::vector3df rotCot = cotovelo->getRotation();
		rotCot.Y = anguloCotovelo;
		cotovelo->setRotation(rotCot);
}


/*

	float diff =node->getJointNode("Root")->getAbsolutePosition().Y - esqueletoRef.abdomen.y;
		printf("Diff: %f\n",diff);
		Vetor novoOmbro = esqueletoRef.ombro_direito;
		Vetor novoCotovelo = esqueletoRef.cotovelo_direito;

		novoOmbro.y+=diff;
		novoCotovelo.y+=diff;
		
		float distanciaOmbroMao = CalculosUteis::distanciaEntrePontos(novoCotovelo,esqueletoRef.mao_direita);
	
		float x = distanciaOmbroCotovelo;
		float y = distanciaCotoveloMao;
		float z = distanciaOmbroMao;
		
		float alfa = (x*x + z*z - y*y) / (2*x*z);
		float anguloOmbro =irr::core::radToDeg(acos(  alfa ));

		Vetor pontoAuxiliarOmbro = Vetor(esqueletoRef.cotovelo_direito.x,esqueletoRef.ombro_direito.y);
	
		float anguloOmbroComplementar = CalculosUteis::anguloEntrePontos(novoOmbro,pontoAuxiliarOmbro,novoCotovelo);
	
		IBoneSceneNode * ombro = node->getJointNode("UpArm_L");
		IBoneSceneNode * cotovelo = node->getJointNode("LoArm_L");
		irr::core::vector3df rotOmbro = ombro->getRotation();
		rotOmbro.Y = ( anguloOmbro + anguloOmbroComplementar );
		ombro->setRotation(rotOmbro);

		float beta = (x*x + y*y - z*z) / (2*x*y);
		float anguloCotovelo = irr::core::radToDeg(acos(beta));
	
		irr::core::vector3df rotCotovelo = cotovelo->getRotation();
		rotCotovelo.Y =   (-180 + anguloCotovelo );
		cotovelo->setRotation(rotCotovelo);
}
*/