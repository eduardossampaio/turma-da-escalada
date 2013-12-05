#include "stdafx.h"
#include "MouseSensor.h"



MouseSensor::MouseSensor()
{
	//device->setEventReceiver(this);
	
	
}


MouseSensor::~MouseSensor(void)
{
}



bool MouseSensor::iniciar() 
{



	return true;
}
void MouseSensor::processar()
{

}
bool MouseSensor::finalizar()
{
	return true;
}
Esqueleto MouseSensor::capturar()
{
	Esqueleto esqueleto;
	
	
	esqueleto.mao_direita  =  Vetor(Globais::getIrrDevice()->getCursorControl()->getPosition().X,Globais::getIrrDevice()->getCursorControl()->getPosition().Y);
	esqueleto.mao_esquerda =  esqueleto.mao_direita;
	return esqueleto;
}
void MouseSensor::addListener(SensorListener * listener)
{

}
int MouseSensor::getUsuariosAtivos()
{
	return 1;
}
bool MouseSensor::ativo()
{
	return true;
}

