#include "stdafx.h"
#include "PoseEscaparPedra.h"
#include "CalculosUteis.h"

PoseEscaparPedra::PoseEscaparPedra(void)
{
}


PoseEscaparPedra::~PoseEscaparPedra(void)
{
}

EstadoCaptura PoseEscaparPedra::identificar(Esqueleto esqueleto)
{
	if(
		CalculosUteis::estaDentroDoRange(CalculosUteis::anguloEntrePontos(esqueleto.ombro_direito,esqueleto.cotovelo_direito),20,20) &&
		CalculosUteis::estaDentroDoRange(CalculosUteis::anguloEntrePontos(esqueleto.cotovelo_direito,esqueleto.mao_direita),5,20) &&
		CalculosUteis::estaDentroDoRange(CalculosUteis::anguloEntrePontos(esqueleto.ombro_esquerdo,esqueleto.cotovelo_esquerdo),-5,20) &&
		CalculosUteis::estaDentroDoRange(CalculosUteis::anguloEntrePontos(esqueleto.cotovelo_esquerdo,esqueleto.mao_esquerda),-29,20) 
		
		){		
			return EstadoCaptura::VALIDO;	
	}
	return EstadoCaptura::INVALIDO;

}