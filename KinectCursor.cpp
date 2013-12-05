#include "stdafx.h"
#include "KinectCursor.h"
#include "KinectSensor.h"
#include "MouseSensor.h"
#include "tipos.h"
#include "Imagem.h"
#include <iostream>
#include "Cronometro.h"
#include "Configuracoes.h"
#include <math.h>
using namespace tipos;



KinectCursor::KinectCursor(void)
{
	KinectCursor::icone = new Imagem("ui/icone/cursor.png");
	cronometroTempoNaMesmaPosicao = new Cronometro();
	centroCirculo=NULL;

	KinectCursor::sensor = 
		KinectSensor::getInstancia();
		
		//new KinectSensor();
//	KinectCursor::sensor=
	//new MouseSensor();

	KinectCursor::raioClique = 40;
	KinectCursor::intervalo = 3;

	KinectCursor::sensor->iniciar();
	srand(time(NULL));
	
	Configuracoes * config = new Configuracoes();
	mao = config->carregarConfigucacoes().mao;
}


KinectCursor::~KinectCursor(void)
{
}

void KinectCursor::atualizar()
{
	
	double tempoCorrido;


	Vetor pos ;
	KinectCursor::sensor->processar();
	
	if(mao == tipos::Mao::ESQUERDA)
		pos = this->sensor->capturar().inverter().mao_esquerda;
	else
		pos = this->sensor->capturar().inverter().mao_direita;
	
	pos.y+=250;
	//pos.x =((int)pos.x) % 5;
	//pos.y =((int)pos.y) % 5;

	this->icone->atualizarPosisao(pos);
	//ver tempo de clique
	if(!cronometroTempoNaMesmaPosicao->iniciado())
		cronometroTempoNaMesmaPosicao->iniciarContagem();
	tempoCorrido = cronometroTempoNaMesmaPosicao->getTempoCorridoSegundos();
	for(int i=0;i<listeners.size();i++)
		listeners[i]->posicaoCaptada(pos);
	/*
	 *
	 *salvar posicaoes 
	 *para ver se esta dentro do circulo
	 *d²  = (px - cx)² + (py - cy)² 
	 *d < r -> dentro
	 *d = r -> em cima
	 *d > r -> fora
	 *
	 */
	//if(centroCirculo==NULL){
	//	centroCirculo = new Vetor(pos.x,pos.y,pos.z);
	//}
	bool taFora=false;
	
	if(centroCirculo==NULL)
		centroCirculo=&pos;

	float dx = (pos.x - centroCirculo->x);
	float dy =  (pos.y - centroCirculo->y);
	float d =   (dx * dx) + (dy * dy);

	d = sqrt(d);

	if(d > raioClique){
		taFora = true;
	}
	if(taFora)
	{
		cronometroTempoNaMesmaPosicao->pararContagem();
	}else{
		if(tempoCorrido >= intervalo ){
			int total=0;
			for(int i=0;i<listeners.size();i++)
			{
				if(listeners[i]->temFoco())
				{
					listeners[i]->onClique(*centroCirculo);
					total++;
				}
			}
			cronometroTempoNaMesmaPosicao->pararContagem();
			printf("notificado %d listeners\n",total);
		}
	}
	/*
	if(tempoCorrido >= intervalo ){
		printf("passou %l segundos... capturou %l posicoes... ",tempoCorrido,posicoes.size());
		cronometroTempoNaMesmaPosicao->pararContagem();
		float taFora = false;
		for(int i=0;i<posicoes.size();i++){
			if(i==0){
				centroCirculo = new Vetor(posicoes[i].x,posicoes[i].y);
			}
			float dx = (posicoes[i].x - centroCirculo->x);
			float dy =  (posicoes[i].y - centroCirculo->y);
			float d =   (dx * dx) + (dy * dy);

			d = sqrt(d);

			if(d > raioClique){
				taFora = true;
				break;
			}

		}
		
		
		if(taFora){
			printf("nao clicou\n");
			
		}
		else{
			printf("clicou \n");
			for(int i=0;i<listeners.size();i++)
				listeners[i]->onClique(*centroCirculo);
		}

		posicoes.clear();
		centroCirculo = NULL;
		
	}else{
		if(cronometroTempoNaMesmaPosicao->getTempoCorridoMiliSegundos() % 10 == 0 )
			posicoes.push_back(pos);
	}*/

	//printf("tempo corrido %f\n",tempoCorrido);

}