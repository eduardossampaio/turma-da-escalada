#pragma once
#include "cursor.h"
#include "Sensor.h"
#include "Cronometro.h"
class KinectCursor : public Cursor
{
public:
	KinectCursor(void);
	~KinectCursor(void);
	virtual void atualizar() override;
private :
	float raioClique;
	float intervalo;
	Sensor *sensor;
	Cronometro * cronometroTempoNaMesmaPosicao;
	Vetor *centroCirculo;

	std::vector<Vetor> posicoes;
	tipos::Mao mao;
};

