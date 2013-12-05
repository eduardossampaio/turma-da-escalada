#pragma once
#include "caixamensagem.h"
#include "interface.h"
class CaixaMensagemSimNao : public CaixaMensagem
{
public:
	CaixaMensagemSimNao(Vetor pos,Vetor tamanho,std::string msg,CliqueListener * listenerSim = 0,CliqueListener * listenerNao = 0);
	~CaixaMensagemSimNao(void);
	virtual void setListenerFechar(CliqueListener * listener) override;
	virtual void ativar() override;
	virtual void fechar() override;
	virtual void onClique(Vetor pos) override;
	virtual void posicaoCaptada(Vetor pos) override;
	virtual void desenhar(IVideoDriver * driver) override;
private:
	Botao * botaoSim;
	Botao * botaoNao;
	Label * mensagem;

	tipos::Area areaBotaoSim;
	tipos::Area areaBotaoNao;
	tipos::Area areaBotoes;
	bool fechou ;
	bool		alinhado;
	std::string texto;
	vector<Componente *> componentes;

};

