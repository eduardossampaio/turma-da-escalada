#pragma once
#include "janela.h"
#include "Sensor.h"
#include "KinectSensor.h"
#include "Boneco.h"
#include "tipos.h"
using namespace tipos;
class JanelaTesteKinect :public Janela, public IEventReceiver 
{
public:
	JanelaTesteKinect(void);
	~JanelaTesteKinect(void);

	void desenhar() override;

	void atualizaPosBoneco(Esqueleto e/*,std::string arq*/);

	bool OnEvent(const SEvent& event) override;

	vector<Esqueleto> lerDoArquivo(/*std::string arq*/);

private:
	Sensor * sensor;
	Boneco * boneco;
	bool primeiro;

	tipos::Esqueleto moverBonecoProLado(tipos::Esqueleto esqueleto);
	irr::scene::ICameraSceneNode * camera;
};

