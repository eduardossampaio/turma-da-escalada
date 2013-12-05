#include "stdafx.h"
#include "MovimentoSprayDireito.h"
#include "CalculosUteis.h"

float diferencaAngulo = 10;

EstadoCaptura MovimentoSprayDireitoPose1::identificar(Esqueleto e)
{
	float angulo = CalculosUteis::anguloEntrePontos(e.ombro_direito,e.mao_direita);
	if(CalculosUteis::estaDentroDoRange(angulo,50,diferencaAngulo))
		return EstadoCaptura::VALIDO;
	else
		return EstadoCaptura::IDENTIFICANDO;
}



EstadoCaptura MovimentoSprayDireitoPose2::identificar(Esqueleto e)
{
	float angulo = CalculosUteis::anguloEntrePontos(e.ombro_direito,e.mao_direita);
	if(CalculosUteis::estaDentroDoRange(angulo,20,diferencaAngulo))
		return EstadoCaptura::VALIDO;
	else
		return EstadoCaptura::IDENTIFICANDO;
}

