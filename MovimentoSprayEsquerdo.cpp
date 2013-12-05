#include "stdafx.h"
#include "MovimentoSprayEsquerdo.h"

#include "CalculosUteis.h"

//float diferencaAngulo = 10;


EstadoCaptura MovimentoSprayEsquerdoPose1::identificar(Esqueleto e)
{
	float angulo = CalculosUteis::anguloEntrePontos(e.ombro_esquerdo,e.mao_esquerda);
	if(CalculosUteis::estaDentroDoRange(angulo,50,10))
		return EstadoCaptura::VALIDO;
	else
		return EstadoCaptura::IDENTIFICANDO;
}



EstadoCaptura MovimentoSprayEsquerdoPose2::identificar(Esqueleto e)
{
	float angulo = CalculosUteis::anguloEntrePontos(e.ombro_esquerdo,e.mao_esquerda);
	if(CalculosUteis::estaDentroDoRange(angulo,20,10))
		return EstadoCaptura::VALIDO;
	else
		return EstadoCaptura::IDENTIFICANDO;
}


