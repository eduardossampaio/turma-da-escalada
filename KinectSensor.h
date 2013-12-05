#pragma once
#include "Sensor.h"
class KinectSensor : public Sensor
{
public:
	

	 bool iniciar()   override;
	 void processar() override;
	 bool finalizar() override;
	 Esqueleto capturar() override;
	 void addListener(SensorListener * listener) override;
	 int getUsuariosAtivos() override;
	 bool ativo () override;
	
	 static KinectSensor * getInstancia();
	 
	 ~KinectSensor(void);
	 //mover para private
	 KinectSensor(void);
private:
	
	static KinectSensor * instancia  ;
	int usuariosAtivos;
	
	
};

