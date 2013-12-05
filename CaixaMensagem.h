#pragma once
#include "Componente.h"
#include "CliqueListener.h"
class CaixaMensagem : public Componente , public CliqueListener
{
public:
	CaixaMensagem(Vetor pos,Vetor tamanho);
	~CaixaMensagem(void);
	virtual void setListenerFechar(CliqueListener * listener) = 0;
	virtual void ativar() = 0;
	virtual void fechar() = 0;
	virtual void onClique(Vetor pos) = 0;
	virtual void posicaoCaptada(Vetor pos) = 0;

protected:
	Vetor tamanho;


};



