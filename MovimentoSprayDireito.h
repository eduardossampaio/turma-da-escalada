#pragma once
#include "Movimento.h"
#include "Gesto.h"
#include "Pose.h"

class MovimentoSprayDireitoPose1 : public Pose
{
public:
	EstadoCaptura MovimentoSprayDireitoPose1::identificar(Esqueleto e) override;

};

class MovimentoSprayDireitoPose2 : public Pose
{
public:
	EstadoCaptura MovimentoSprayDireitoPose2::identificar(Esqueleto e) override;

};
