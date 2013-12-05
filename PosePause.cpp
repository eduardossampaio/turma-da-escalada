#include "stdafx.h"
#include "PosePause.h"
#include "CalculosUteis.h"


PosePause::PosePause(void)
{
	cronometro = new Cronometro();
	identificou = false;
	
}


PosePause::~PosePause(void)
{
}


EstadoCaptura PosePause::identificar(Esqueleto esqueleto)
{

	float angulo = CalculosUteis::anguloEntrePontos(esqueleto.ombro_direito,esqueleto.mao_direita);
	float margem = 10;
	
	if(angulo >= 45-margem && angulo<= 45 + margem){
		if(!cronometro->iniciado()){
			cronometro->iniciarContagem();
			
		}
		if(cronometro->getTempoCorridoSegundos() >= 5){
			cronometro->pararContagem();
			return EstadoCaptura::VALIDO;
		}else{
			return EstadoCaptura::IDENTIFICANDO;
		}
	}else{
		cronometro->pararContagem();
		return EstadoCaptura::INVALIDO;
	}
}