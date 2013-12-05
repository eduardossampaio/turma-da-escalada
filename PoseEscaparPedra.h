#pragma once
#include "pose.h"
class PoseEscaparPedra : public Pose
{
public:
	PoseEscaparPedra(void);
	~PoseEscaparPedra(void);

	virtual EstadoCaptura PoseEscaparPedra::identificar(Esqueleto esqueleto) override;
};

