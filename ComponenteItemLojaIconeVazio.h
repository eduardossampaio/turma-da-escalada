#pragma once
#include "componente.h"

/*
		classe para desenhar um item "vazio", vai ser usada quadno não tiver
		item para ser exibido
*/
class ComponenteItemLojaIconeVazio : public Componente
{
public:
	ComponenteItemLojaIconeVazio(Vetor pos,Vetor tamanho);
	~ComponenteItemLojaIconeVazio(void);
	
	virtual void desenhar(IVideoDriver * driver) override;

private:
		Vetor tamanho;
};

