#include "stdafx.h"
#include "Cronometro.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//melhorar isso aqui depois
long tempoInicioMili;
long tempoFinalMili;
Cronometro::Cronometro(void)
{
	tempoInicio = NULL;
	tempoFinal  = NULL;
	iniciou = false;
}


Cronometro::~Cronometro(void)
{
}

void Cronometro::iniciarContagem()
{
	iniciou = true;
	tempoInicio = time(NULL);
	tempoInicioMili = time(NULL);
}

void Cronometro::reiniciarContagem()
{
	pararContagem();
	iniciarContagem();
}

void Cronometro::pausarContagem()
{

}


void Cronometro::pararContagem()
{
	iniciou=false;
}


double Cronometro::getTempoCorridoSegundos()
{
	if (iniciou){
		Cronometro::tempoFinal = time(NULL);
	}
	double diff  = difftime(Cronometro::tempoFinal,Cronometro::tempoInicio);
	return diff;
}
long Cronometro::getTempoCorridoMiliSegundos()
{
	if (iniciou){
		tempoFinalMili = clock();
	}
	long diff = tempoFinalMili - tempoInicioMili;
	return diff;
}
bool Cronometro::iniciado()
{
	return Cronometro::iniciou;
}