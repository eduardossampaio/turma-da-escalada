#include "stdafx.h"
#include "PosePernaEmPe.h"
#include "CalculosUteis.h"

PosePernaEmPe::PosePernaEmPe(void)
{
}


PosePernaEmPe::~PosePernaEmPe(void)
{
}

EstadoCaptura PosePernaEmPe::identificar(Esqueleto esqueleto)
{
	Vetor p1_dir 	= esqueleto.abdomen;					  
	Vetor p2_dir 	= esqueleto.joelho_direito;
	Vetor p1p2_dir	= Vetor(p1_dir.x,p2_dir.y);	
	


	float angulo_abdomem_dir = CalculosUteis::anguloEntrePontos(p1_dir, p2_dir);
	//ver range

	//	TA CERTO
	if(angulo_abdomem_dir>-45 || angulo_abdomem_dir<-65)
		return  EstadoCaptura::INVALIDO;
	
	Vetor p4_dir 	= esqueleto.joelho_direito;
	Vetor p5_dir 	= esqueleto.pe_direito;
	Vetor p4p5_dir	= Vetor(p4_dir.x,p5_dir.y);

	float angulo_joelho_dir = CalculosUteis::anguloEntrePontos(p4_dir,p5_dir);
	
	//		TA CERTO
	//if(angulo_joelho_dir < 60 || angulo_joelho_dir > 80)
	//	return EstadoCaptura::INVALIDO;
	
	Vetor p1_esq 	= esqueleto.abdomen;
	Vetor p2_esq 	= esqueleto.joelho_esquerdo;
	Vetor p1p2_esq	= Vetor(p1_esq.x,p2_esq.y);	
	
	float angulo_abdomem_esq = CalculosUteis::anguloEntrePontos(p1_esq,p2_esq);
	
	//ver range
	if(angulo_abdomem_esq>-20 || angulo_abdomem_esq<-60)
		return  EstadoCaptura::INVALIDO;

	Vetor p4_esq 	= esqueleto.joelho_esquerdo;
	Vetor p5_esq 	= esqueleto.pe_esquerdo;
	Vetor p4p5_esq	= Vetor(p4_esq.x,p5_esq.y);
	
	float angulo_joelho_esq = CalculosUteis::anguloEntrePontos(p4_esq,p5_esq);
	
	//if(angulo_joelho_esq < 25 || angulo_joelho_esq > 45)
	//	return EstadoCaptura::INVALIDO;
	
	return EstadoCaptura::VALIDO;
}
