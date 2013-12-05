#include "stdafx.h"
#include "Cursor.h"

using namespace tipos;
Cursor::Cursor(void)
{
}


Cursor::~Cursor(void)
{
}

Vetor Cursor::getPosicao()
{
	return Cursor::posicao;
}

void Cursor::setPosicao(Vetor pos)
{
	Cursor::posicao = pos;
}
void Cursor::adicionarListener(CliqueListener *listener)
{
	Cursor::listeners.push_back(listener);
}
vector<CliqueListener *> Cursor::getListeners()
{
	return Cursor::listeners;
}
void Cursor::removerListener(CliqueListener * listener)
{
	//adicionar depois lógica de remoção

	vector<CliqueListener *>::iterator position = std::find(listeners.begin(), listeners.end(), listener);
	if (position != listeners.end()) 
		listeners.erase(position);
}

Componente* Cursor::getIcone()
{
	return Cursor::icone;
}

void Cursor::desenhar(IVideoDriver * driver)
{
	if(Cursor::icone!=NULL)
		Cursor::icone->desenhar(driver);
}