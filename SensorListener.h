#pragma once
#include "tipos.h"

using namespace tipos;

class SensorListener
{
public:
	SensorListener(void);
	~SensorListener(void);
	virtual void onMovimentoCapturado(Esqueleto esqueleto) =  0;
};

