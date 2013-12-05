#pragma once
#include "tipos.h"
#include "SensorListener.h"
using namespace tipos;
class Sensor
{
public:
	Sensor(void);
	~Sensor(void);

	virtual bool iniciar()   = 0;
	virtual void processar() = 0;
	virtual bool finalizar() = 0;
	virtual Esqueleto capturar() = 0;
	virtual void addListener(SensorListener * listener) = 0;
	virtual int getUsuariosAtivos() = 0;
	virtual bool ativo() = 0;
};

