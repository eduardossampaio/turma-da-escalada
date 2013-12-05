#pragma once
#include "Pose.h"
#include "Cronometro.h"
class PosePause : public Pose
{
public:
	PosePause(void);
	~PosePause(void);

	
	virtual EstadoCaptura identificar(Esqueleto esqueleto) override;
private:
	Cronometro * cronometro;
	bool identificou;
};

