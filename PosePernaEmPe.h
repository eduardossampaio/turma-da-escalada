#pragma once
#include "pose.h"
class PosePernaEmPe : public Pose
{
public:
	PosePernaEmPe(void);
	~PosePernaEmPe(void);
	virtual EstadoCaptura identificar(Esqueleto esqueleto) override;
};

