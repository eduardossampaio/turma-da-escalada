#include "stdafx.h"
#include "TransformadorAtualizacaoPosicao.h"
#include "TransformadorAtualizarPosicaoBracoEsquerdo.h"
#include "TransformadorAtualizarPosicaoBracoDireito.h"
#include "TransformadorAtualizarPosicaoPernaDireita.h"
#include "TransformadorAtualizarPosicaoPernaEsquerda.h"

TransformadorAtualizacaoPosicao::TransformadorAtualizacaoPosicao(IAnimatedMeshSceneNode * node)
{
	transformadorBracoEsquerdo	= new TransformadorAtualizarPosicaoBracoEsquerdo(node);	
	transformadorBracoDireito	= new TransformadorAtualizarPosicaoBracoDireito(node);	
	transformadorPernaDireita	= new TransformadorAtualizarPosicaoPernaDireita(node);
	transformadorPernaEsquerda	= new TransformadorAtualizarPosicaoPernaEsquerda(node);
}


TransformadorAtualizacaoPosicao::~TransformadorAtualizacaoPosicao(void)
{
}

void TransformadorAtualizacaoPosicao::transformar(irr::scene::IAnimatedMeshSceneNode * node, tipos::Esqueleto esqueleto)
{
	transformadorBracoEsquerdo->transformar(node,esqueleto);
	transformadorBracoDireito->transformar(node,esqueleto);
	transformadorPernaDireita->transformar(node,esqueleto);
	transformadorPernaEsquerda->transformar(node,esqueleto);
	for(int i=0;i<node->getJointCount();i++)
	{
		node->getJointNode(i)->updateAbsolutePosition();
	}
}