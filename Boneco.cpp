#include "stdafx.h"
#include "Boneco.h"

#include "CalculosUteis.h"

Esqueleto ajustarEsqueleto(Esqueleto e);
float raioCabeca = 50;

Boneco::Boneco(Vetor pos) : Componente(pos)
{
}


Boneco::~Boneco(void)
{
}

void Boneco::desenhar(IVideoDriver * driver)
{
	video::SColor vermelho = video::SColor(255,255,0,0);
	//video::SColor azul		= video::SColor(255,0,0,255);
	video::SColor azul		= video::SColor(255,255,255,255);
	//desenha a cabeça
	driver->draw2DPolygon(core::vector2d<s32>(esqueleto.cabeca.x,esqueleto.cabeca.y),raioCabeca,azul,360);
	
	//desenha o tronco
	driver->draw2DLine(
		core::vector2d<s32>(esqueleto.cabeca.x,esqueleto.cabeca.y),
		core::vector2d<s32>(esqueleto.abdomen.x,esqueleto.abdomen.y),
		azul);
	driver->draw2DLine(
		core::vector2d<s32>(esqueleto.ombro_direito.x,esqueleto.ombro_direito.y),
		core::vector2d<s32>(esqueleto.ombro_esquerdo.x,esqueleto.ombro_esquerdo.y),
		azul);
	driver->draw2DLine(
		core::vector2d<s32>(esqueleto.ombro_esquerdo.x,esqueleto.ombro_esquerdo.y),
		core::vector2d<s32>(esqueleto.abdomen.x,esqueleto.abdomen.y),
		azul);
	driver->draw2DLine(
		core::vector2d<s32>(esqueleto.ombro_direito.x,esqueleto.ombro_direito.y),
		core::vector2d<s32>(esqueleto.abdomen.x,esqueleto.abdomen.y),
		azul);

	//desenha o braço direito
	driver->draw2DLine(
		core::vector2d<s32>(esqueleto.ombro_direito.x,esqueleto.ombro_direito.y),
		core::vector2d<s32>(esqueleto.cotovelo_direito.x,esqueleto.cotovelo_direito.y),
		azul);
	driver->draw2DLine(
		core::vector2d<s32>(esqueleto.cotovelo_direito.x,esqueleto.cotovelo_direito.y),
		core::vector2d<s32>(esqueleto.mao_direita.x,esqueleto.mao_direita.y),
		azul);

	//desenha braco esquerdo
	driver->draw2DLine(
		core::vector2d<s32>(esqueleto.ombro_esquerdo.x,esqueleto.ombro_esquerdo.y),
		core::vector2d<s32>(esqueleto.cotovelo_esquerdo.x,esqueleto.cotovelo_esquerdo.y),
		azul);
	driver->draw2DLine(
		core::vector2d<s32>(esqueleto.cotovelo_esquerdo.x,esqueleto.cotovelo_esquerdo.y),
		core::vector2d<s32>(esqueleto.mao_esquerda.x,esqueleto.mao_esquerda.y),
		azul);

	//desenha perna direita
	driver->draw2DLine(
		core::vector2d<s32>(esqueleto.abdomen.x,esqueleto.abdomen.y),
		core::vector2d<s32>(esqueleto.joelho_direito.x,esqueleto.joelho_direito.y),
		azul);
	driver->draw2DLine(
		core::vector2d<s32>(esqueleto.joelho_direito.x,esqueleto.joelho_direito.y),
		core::vector2d<s32>(esqueleto.pe_direito.x,esqueleto.pe_direito.y),
		azul);

	//desenha perna esquerda
	driver->draw2DLine(
		core::vector2d<s32>(esqueleto.abdomen.x,esqueleto.abdomen.y),
		core::vector2d<s32>(esqueleto.joelho_esquerdo.x,esqueleto.joelho_esquerdo.y),
		azul);
	driver->draw2DLine(
		core::vector2d<s32>(esqueleto.joelho_esquerdo.x,esqueleto.joelho_esquerdo.y),
		core::vector2d<s32>(esqueleto.pe_esquerdo.x,esqueleto.pe_esquerdo.y),
		azul);

	//linha do braco
	Vetor p1   = esqueleto.cotovelo_direito;
	Vetor p2   = esqueleto.mao_direita;
	Vetor p1p2 = Vetor(p2.x,p1.y);
	driver->draw2DLine(core::vector2d<s32>(p1.x,p1.y),core::vector2d<s32>(p1p2.x,p1p2.y),vermelho);
	driver->draw2DLine(core::vector2d<s32>(p2.x,p2.y),core::vector2d<s32>(p1p2.x,p1p2.y),vermelho);
	//printf("angulo: %f\n",CalculosUteis::anguloEntrePontos(p1,p2,p1p2));


	//linha da perna
	//tipos::Vetor v3 = Vetor(esqueleto.abdomen.x,esqueleto.joelho_direito.y);
	tipos::Vetor v3 = Vetor(esqueleto.joelho_direito.x,esqueleto.abdomen.y);
	driver->draw2DLine(core::vector2d<s32>(esqueleto.abdomen.x,esqueleto.abdomen.y),core::vector2d<s32>(v3.x,v3.y),vermelho);
	driver->draw2DLine(core::vector2d<s32>(esqueleto.joelho_direito.x,esqueleto.joelho_direito.y),core::vector2d<s32>(v3.x,v3.y),vermelho);
}

void Boneco::setEsqueleto(Esqueleto e)
{
	
	//esqueleto = Esqueleto();
//	esqueleto = ajustarEsqueleto(e);
	
	this->esqueleto = ajustarEsqueleto(e);
	
}
Esqueleto Boneco::getEsqueleto()
{
	return Boneco::esqueleto;
}

Esqueleto Boneco::ajustarEsqueleto(Esqueleto e)
{
	e.escalarEsqueleto(0.6);
	float menorValorYAbaixo0 = 0;
	for(int i=0;i<e.qtd;i++){
		e.getJoints()[i]->y*=-1;
		if(e.getJoints()[i]->y < 0 && e.getJoints()[i]->y < menorValorYAbaixo0 )
			menorValorYAbaixo0 = e.getJoints()[i]->y;
	}

	//subir esqueleto
	menorValorYAbaixo0*=-1;
	menorValorYAbaixo0+=raioCabeca;
	for(int i=0;i<e.qtd;i++){
		e.getJoints()[i]->y += menorValorYAbaixo0;
	
	}
	
		

	return e;
}