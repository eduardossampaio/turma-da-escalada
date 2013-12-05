#pragma once
#include "transformador.h"
#include "Cronometro.h"
#include "tipos.h"
#include <irrlicht.h>
#include "MarcadorPedra.h"
#include "CalculosUteis.h"
#include "PosePernaEmPe.h"
#include "TransformadorAtualizacaoPosicao.h"
#include "MovimentadorMembro.h"
#include "MovimentadorBracoDireito.h"

#define TEMPO_TESTE 6
using namespace irr;
using namespace scene;
using namespace tipos;
using namespace core;



class TransformadorKinect : public Transformador
{
private:
	bool primeiro;
	Cronometro cronometro;
	vector<MarcadorPedra *> marcadores;
	typedef struct s_cel_movimentos
	{
		
		MovimentadorMembro * movimento;
		s_cel_movimentos * proximo;
	}Cel_Movimentos;
	
	
	Cel_Movimentos * movimentoBracoEsquerdo;
	Cel_Movimentos * movimentoBracoDireito;
	Cel_Movimentos * movimentoPernaEsquerda;
	Cel_Movimentos * movimentoPernaDireita;
	Cel_Movimentos * movimentoSubir;
	Cel_Movimentos * atual;
public:
	TransformadorKinect(vector<MarcadorPedra *> marcadores);
	~TransformadorKinect(void);
	virtual void transformar(irr::scene::IAnimatedMeshSceneNode * mesh,tipos::Esqueleto esqueleto) override;

};
	

	

	




	