#include "stdafx.h"
#include "KinectSensor.h"
#include "Sensor.h"
#include "Conversor.h"
#include <OpenNi.h>
#include <Nite.h>

KinectSensor * KinectSensor::instancia = NULL;

bool estaAtivo ;

//atributos NITE

Esqueleto esqueleto;

nite::UserTracker userTracker;
nite::UserTrackerFrameRef userTrackerFrame;
nite::Status niteRc;

KinectSensor::KinectSensor(void)
{
	estaAtivo = false;
}


KinectSensor::~KinectSensor(void)
{
}
KinectSensor * KinectSensor::getInstancia(){
//}
//KinectSensor * KinectSensor::getInstancia(){
	if(instancia == NULL)
		instancia = new KinectSensor();
	return instancia;
//	return NULL;
}
bool KinectSensor::iniciar()   
{
	if(!estaAtivo)
	{
		nite::Status statusNite = nite::NiTE::initialize();
		if(statusNite == nite::Status::STATUS_OK)
		{
			estaAtivo = true;
			printf("nite iniciado com sucesso\n");
		}else{
			printf("erro ao iniciar nite: %d ",statusNite);
			if(statusNite == nite::Status::STATUS_BAD_USER_ID)
				printf("bad user id\n");
			if(statusNite == nite::Status::STATUS_ERROR)
				printf("status error\n");
			if(statusNite == nite::Status::STATUS_OUT_OF_FLOW)
				printf("status out of flow\n");
		
			//return false;
			estaAtivo = false;
		}
	
		
	

		niteRc = userTracker.create();
		if (niteRc != nite::STATUS_OK)
		{
			printf("erro ao criar user tracker\n");
			estaAtivo = false;
		}else
		{
			printf("user tacker criado\n");
		}
	}
	if(estaAtivo)
		printf("ativado\n");
	return estaAtivo;
	
	
	//return true;
}
void KinectSensor::processar() 
{
	if(estaAtivo)
	{
		printf("kinect processando\n");
		niteRc = userTracker.readFrame(&userTrackerFrame);
	
		if (niteRc != nite::STATUS_OK)
		{
			//erro - tratar
			printf("======================= \n");
			printf("	ERRRROOOORRRRRR		\n");
			printf("======================= \n");
		}else{
			int i=0;
		
			const nite::Array<nite::UserData>& users = userTrackerFrame.getUsers();
			//printf("usuários %d\n",users.getSize());
			usuariosAtivos = 0;
			for(int i=0; i<users.getSize();i++){
				const nite::UserData& user = users[i];
				userTracker.startSkeletonTracking(user.getId());
				if (user.getSkeleton().getState() == nite::SKELETON_TRACKED){
					usuariosAtivos++;
					const nite::Skeleton *niteSkeleton = &(user.getSkeleton());
					
					esqueleto = Conversor::NiteSkeletonParaEsqueleto(niteSkeleton);	
					printf("esqueleto capturado\n");
				}			
			}

		}
	}
	
}

bool KinectSensor::finalizar() 
{
	
	openni::OpenNI::shutdown();
	nite::NiTE::shutdown();
	
	return true;
}
Esqueleto KinectSensor::capturar() 
{
	//esqueleto.mao_direita = Vetor(500,500,0);
	return esqueleto;
}
void KinectSensor::addListener(SensorListener * listener) 
{
}
int KinectSensor::getUsuariosAtivos() 
{
	return usuariosAtivos;
}
	
bool KinectSensor::ativo()
{
	return estaAtivo;

}
