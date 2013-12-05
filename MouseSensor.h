#pragma once
#include "sensor.h"

#include <irrlicht.h>
#include "Globais.h"
using namespace irr;

class MouseSensor :public Sensor 
{
public:
	MouseSensor();
	~MouseSensor(void);

	virtual bool iniciar()  override;
	virtual void processar() override;
	virtual bool finalizar() override;
	virtual Esqueleto capturar() override;
	virtual void addListener(SensorListener * listener) override;
	virtual int getUsuariosAtivos() override;
	virtual bool ativo() override;

	

};

