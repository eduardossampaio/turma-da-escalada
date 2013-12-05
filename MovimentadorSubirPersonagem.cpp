#include "stdafx.h"
#include "MovimentadorSubirPersonagem.h"
#include "PosePernaEmPe.h"
#include "TransformadorAtualizacaoPosicao.h"


MovimentadorSubirPersonagem::MovimentadorSubirPersonagem( vector<MarcadorPedra *> marcadores):marcadores(marcadores)
{
	primeiro	= true;
	terminado	= false;
	pose		= new PosePernaEmPe();

	passos	=20;
	tempo	=2;
	indice	=1;
	margem = 10;
	
}


MovimentadorSubirPersonagem::~MovimentadorSubirPersonagem(void)
{
}




void MovimentadorSubirPersonagem::mover(irr::scene::IAnimatedMeshSceneNode * node,tipos::Esqueleto esqueleto) 
{

	if(transformadorSubir==NULL)
		transformadorSubir = new TransformadorAtualizacaoPosicao(node);
	posicaoJoelho = esqueleto.joelho_esquerdo;
	core::vector3df pos = node->getAbsolutePosition();
	
		
	cronometro.pararContagem();
	float valParaSubir = 20;
	pos.Y +=valParaSubir;
	node->setPosition(pos);
	node->updateAbsolutePosition();
	transformadorSubir->transformar(node,esqueleto);
	
	




	
}
bool MovimentadorSubirPersonagem::terminou() 
{						
	return terminado;
}
void MovimentadorSubirPersonagem::reset() 
{
	primeiro = true;
	terminado = false;
	delete transformadorSubir;
	transformadorSubir = NULL;
	indice=1;
}
