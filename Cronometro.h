#pragma once
#include <time.h>
class Cronometro
{
private:
	time_t tempoInicio;
	time_t tempoFinal;
protected:
	bool iniciou;

public:
	Cronometro(void);
	~Cronometro(void);

	void iniciarContagem();
	void pausarContagem();
	void pararContagem();
	void reiniciarContagem();
	double getTempoCorridoSegundos();
	long getTempoCorridoMiliSegundos();
	bool iniciado();

};

