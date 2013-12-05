#pragma once
#include "caixamensagem.h"
#include "interface.h"
#include "tipos.h"
class CaixaVendaItem : public CaixaMensagem
{
public:
	CaixaVendaItem(Vetor posicao,Vetor tamanho,std::string msg,CliqueListener * listenerVender ,CliqueListener * listenerSair ,int maximo);
	~CaixaVendaItem(void);
	virtual void setListenerFechar(CliqueListener * listener) override;
	virtual void setListenerVender(CliqueListener * listener);
	virtual void setListenerSair(CliqueListener * listener);
	virtual void ativar() override;
	virtual void fechar() override;
	virtual void onClique(Vetor pos) override;
	virtual void posicaoCaptada(Vetor pos) override;
	virtual void desenhar(IVideoDriver * driver) override;
	int getQuantidadeSelecionada();
private:
	Botao * botaoVender;
	Botao * botaoSair;
	Label * mensagem;
	NumberSpinner * spinner;

	tipos::Area areaBotaoSair;
	tipos::Area areaBotaoVender;
	tipos::Area areaBotoes;
	tipos::Area areaSpinner;
	tipos::Area areaTexto;

	bool		alinhado;
	std::string texto;
	vector<Componente *> componentes;
};

