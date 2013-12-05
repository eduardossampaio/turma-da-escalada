#include "stdafx.h"
#include "MovimentadorBracoDireito.h"
#include "CalculosUteis.h"


MovimentadorBracoDireito::MovimentadorBracoDireito(vector<MarcadorPedra *> marcadores):marcadores(marcadores),indiceAnterior(-1),indiceAtual(-1),terminado(false)
{
}


MovimentadorBracoDireito::~MovimentadorBracoDireito(void)
{
}


 void MovimentadorBracoDireito::mover(irr::scene::IAnimatedMeshSceneNode * node,tipos::Esqueleto esqueleto)
{
	std::string ombro_direito_bone			=       "UpArm_R";
	std::string braco_direito_bone			=       "LoArm_R";				
	std::string mao_direita_bone			=		"Index_R";

	float anguloOmbroDireito = getAnguloBraco(esqueleto.ombro_direito,esqueleto.cotovelo_direito);	
	setarAnguloBone(node,ombro_direito_bone,anguloOmbroDireito);		
	float anguloMaoDireita = CalculosUteis::anguloEntrePontos(esqueleto.cotovelo_direito,esqueleto.ombro_direito,esqueleto.mao_direita);
	if(esqueleto.cotovelo_direito.y < esqueleto.mao_direita.y)
		anguloMaoDireita = - anguloMaoDireita;
	if(!_isnan(anguloMaoDireita))
		setarAnguloBone(node,braco_direito_bone,-anguloMaoDireita);

	IBoneSceneNode * mao = node->getJointNode(mao_direita_bone.c_str());
	pos = Vetor(mao->getAbsolutePosition().X,mao->getAbsolutePosition().Y,mao->getAbsolutePosition().Z);
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
			tem  = true;
			indiceAtual = i;
		}
	}
	if(!tem)
	{
		cronometro.pararContagem();
	}
	*/

}
 bool MovimentadorBracoDireito::terminou() 
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
void MovimentadorBracoDireito::reset() 
{
	cronometro.pararContagem();
}
	