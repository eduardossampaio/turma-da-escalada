#pragma once
#include "Componente.h"
#include "Editavel.h"
#include "tipos.h"
#include "TecladoVirtual.h"
#include "Cronometro.h"
using namespace tipos;
class CaixaTexto :public Componente,public Editavel
{
public:
	CaixaTexto(Vetor pos,Vetor tamanho);
	~CaixaTexto(void);

	virtual std::string getTexto() override;
	virtual void setTexto(std::string texto) override;
	virtual void addTexto(std::string texto) override;
	virtual void apagaTexto() override;

	virtual void desenhar(IVideoDriver * driver) override;

	bool posicaoDentroCaixa(Vetor v);

	void setSelecionado(bool selecionado);
	bool estaSelecionado();

	TecladoVirtual * getTeclado();
	void setTeclado(TecladoVirtual * teclado);
private:
	std::string texto;
	Vetor tamanho;
	bool selecionado;
	TecladoVirtual * teclado;
	Cronometro cronometroCursor;


};

