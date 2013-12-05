#include "tipos.h"
#include "irrlicht.h";
#pragma once
class Globais{
public:
	Globais();
	
	static irr::IrrlichtDevice* getIrrDevice()
	{
		return Globais::device;
	}
	
	static void setIrrDevice (irr::IrrlichtDevice * device)
	{
		Globais::device = device;
	}


private:
	static irr::IrrlichtDevice * device;

};

/*
class Configuracoes{
	private:
		//static Vetor Configuracoes::resolucao = Vetor(1024,768)
	public:
		static tipos::Vetor Configuracoes::getConfiguracoes(){
			
			return tipos::Vetor(1024,768);
			//return Vetor(1920,1080);
		}
	};
	*/