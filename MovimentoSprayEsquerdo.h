#pragma once
#include "Movimento.h"
#include "Gesto.h"
#include "Pose.h"

class MovimentoSprayEsquerdoPose1 : public Pose
{
public:
	EstadoCaptura MovimentoSprayEsquerdoPose1::identificar(Esqueleto e) override;

};

class MovimentoSprayEsquerdoPose2 : public Pose
{
public:
	EstadoCaptura MovimentoSprayEsquerdoPose2::identificar(Esqueleto e) override;

};
