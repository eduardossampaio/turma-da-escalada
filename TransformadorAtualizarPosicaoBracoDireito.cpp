#include "stdafx.h"
#include "TransformadorAtualizarPosicaoBracoDireito.h"
#include "CalculosUteis.h"
#include <math.h>

TransformadorAtualizarPosicaoBracoDireito::TransformadorAtualizarPosicaoBracoDireito(IAnimatedMeshSceneNode * node)
{
	TransformadorAtualizarPosicaoBracoDireito::primeiro = true;
	TransformadorAtualizarPosicaoBracoDireito::node	=	node;
	
	esqueletoRef.abdomen = Vetor( node->getJointNode("Root")->getAbsolutePosition().X , node->getJointNode("Root")->getAbsolutePosition().Y, node->getJointNode("Root")->getAbsolutePosition().Z);
	esqueletoRef.ombro_direito = Vetor( node->getJointNode("UpArm_R")->getAbsolutePosition().X , node->getJointNode("UpArm_R")->getAbsolutePosition().Y, node->getJointNode("UpArm_R")->getAbsolutePosition().Z);
	esqueletoRef.cotovelo_direito = Vetor( node->getJointNode("LoArm_R")->getAbsolutePosition().X , node->getJointNode("LoArm_R")->getAbsolutePosition().Y, node->getJointNode("LoArm_R")->getAbsolutePosition().Z);
	esqueletoRef.mao_direita  = Vetor( node->getJointNode("Hand_R")->getAbsolutePosition().X , node->getJointNode("Hand_R")->getAbsolutePosition().Y, node->getJointNode("Hand_R")->getAbsolutePosition().Z);

	distanciaCotoveloMao = CalculosUteis::distanciaEntrePontos(esqueletoRef.cotovelo_direito,esqueletoRef.mao_direita);
	distanciaOmbroCotovelo = CalculosUteis::distanciaEntrePontos(esqueletoRef.ombro_direito,esqueletoRef.cotovelo_direito);
	
	IBoneSceneNode * nodeOmbro = node->getJointNode("UpArm_R");	
	core::vector3df rotOmbro = nodeOmbro->getRotation();	
	rotOmbro.Y = 0;
	//nodeOmbro->setRotation(rotOmbro);
}




TransformadorAtualizarPosicaoBracoDireito::~TransformadorAtualizarPosicaoBracoDireito(void)
{
}

void TransformadorAtualizarPosicaoBracoDireito::transformar(irr::scene::IAnimatedMeshSceneNode * node, tipos::Esqueleto esqueleto)
{
	IBoneSceneNode * ombro = node->getJointNode("UpArm_R");
	IBoneSceneNode * cotovelo = node->getJointNode("UpArm_R");
	float menorDistancia = 999;
	float anguloOmbro = 0;
	float anguloCotovelo = 0;
	//int anguloMinimo = -60;
	//int anguloMaximo = 60;
	int anguloMinimoOmbro = ombro->getRotation().Y - 20;
	int anguloMaximoOmbro = ombro->getRotation().Y + 20;
	int anguloMinimoCotovelo = cotovelo->getRotation().Y - 20;
	int anguloMaximoCotovelo = cotovelo->getRotation().Y + 20;
	
	for (int i = anguloMinimoOmbro ;i < anguloMaximoOmbro ;i++)
	{
		core::vector3df rotOmbro = ombro->getRotation();
		rotOmbro.Y = i;
		ombro->setRotation(rotOmbro);
		for(int j =anguloMinimoCotovelo ; j< anguloMaximoCotovelo ;j++)
		{
			core::vector3df rotCot = cotovelo->getRotation();
			rotCot.Y = j;
			cotovelo->setRotation(rotCot);
			IBoneSceneNode * mao = node->getJointNode("Hand_R");
			
			node->updateAbsolutePosition();
			for(int i=0;i<node->getJointCount();i++)
			{
				node->getJointNode(i)->updateAbsolutePosition();
			}
			float distancia = CalculosUteis::distanciaEntrePontos(
				Vetor(mao->getAbsolutePosition().X,mao->getAbsolutePosition().Y,mao->getAbsolutePosition().Z),
				esqueletoRef.mao_direita);
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
	
		IBoneSceneNode * ombro = node->getJointNode("UpArm_R");
		IBoneSceneNode * cotovelo = node->getJointNode("LoArm_R");
		irr::core::vector3df rotOmbro = ombro->getRotation();
		rotOmbro.Y = -( anguloOmbro + anguloOmbroComplementar );
		ombro->setRotation(rotOmbro);

		float beta = (x*x + y*y - z*z) / (2*x*y);
		float anguloCotovelo = irr::core::radToDeg(acos(beta));
	
		irr::core::vector3df rotCotovelo = cotovelo->getRotation();
		rotCotovelo.Y =  - (-180 + anguloCotovelo );
		cotovelo->setRotation(rotCotovelo);
*/


	/*
	core::vector3df novoOmbro		= node->getJointNode("UpArm_R")->getAbsolutePosition();
	core::vector3df novoCotovelo	= node->getJointNode("LoArm_R")->getAbsolutePosition(); 
	
	Vetor novoOmbroV = Vetor(novoOmbro.X,novoOmbro.Y,novoOmbro.Z);
	Vetor novoCotoveloV = Vetor(novoCotovelo.X,novoCotovelo.Y,novoCotovelo.Z);
	//float angulo = CalculosUteis::anguloEntrePontos(novoOmbroV,esqueletoRef.cotovelo_direito);
	float angulo = CalculosUteis::anguloEntrePontos(novoOmbroV,esqueletoRef.cotovelo_direito);
	
	//core::vector3df v1 = novoCotovelo;
	core::vector3df v1 = novoOmbro;
	core::vector3df v2 = core::vector3df( esqueletoRef.cotovelo_direito .x,esqueletoRef.cotovelo_direito.y,esqueletoRef.cotovelo_direito.z);

	Vetor v_1 = novoOmbroV;
	Vetor v_2 = novoCotoveloV;
	Vetor v_3 = esqueletoRef.cotovelo_direito;

	float a1 = CalculosUteis::anguloEntrePontos(v_1,v_2,v_3);
	float a2 = CalculosUteis::anguloEntrePontos(v_1,v_3,v_2);
	float a3 = CalculosUteis::anguloEntrePontos(v_2,v_1,v_3);
	float a4 = CalculosUteis::anguloEntrePontos(v_2,v_3,v_1);
	float a5 = CalculosUteis::anguloEntrePontos(v_3,v_1,v_2);
	float a6 = CalculosUteis::anguloEntrePontos(v_3,v_2,v_1);
	float a7 = CalculosUteis::anguloEntrePontos(v_1,v_3);
	float a8 = CalculosUteis::anguloEntrePontos(v_3,v_1);

	printf("============================\n");
	printf("a1 %f\na2 %f\na3 %f\na4 %f\na5 %f\na6 %f \na7 %f\na8 %f\n",a1,a2,a3,a4,a5,a6,a7,a8);
	printf("============================\n");


	core::vector3df origem = novoCotovelo;
		//novoOmbro;
	v1 = v1-origem;
	v2 = v2-origem;

	core::vector3df v1_x_v2 = v1 * v2;
	float t =  (v1_x_v2.X + v1_x_v2.Y) / ( sqrt( (v1.X * v1.X) + (v1.Y * v1.Y) ) *  sqrt( (v2.X * v2.X) + (v2.Y * v2.Y) )  );

	float angulo_w = acos(t);
	
	IBoneSceneNode * nodeOmbro = node->getJointNode("UpArm_R");	
	core::vector3df rotOmbro = nodeOmbro->getRotation();
	//rotOmbro.Y -=1;
	rotOmbro.Y =90 -a5;
	printf("t = %f , angulo_w %f\n",t,angulo_w);
	
	if(!_isnan(rotOmbro.Y))
		nodeOmbro->setRotation(rotOmbro);
	/*
	IBoneSceneNode * nodeCotovelo = node->getJointNode("LoArm_R");
	core::vector3df rotCot = nodeCotovelo->getRotation();
	rotCot.Y+=1;
	nodeCotovelo->setRotation(rotCot);
	*/
	
