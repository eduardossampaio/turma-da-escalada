#pragma once
#include "tipos.h"
#include "Componente.h"
#include "interface.h"
#include "CaixaMensagem.h"

using namespace tipos;
enum tipoMensagem
{
		NORMAL,
		ALERTA,
		ERRO	
};	
class CaixaMensagemSimple : public CaixaMensagem
{
public:
	CaixaMensagemSimple(Vetor pos,Vetor tamanho,std::string texto,tipoMensagem tipoMensagem);
	~CaixaMensagemSimple(void);
	virtual void desenhar(IVideoDriver * driver) override;
	void setBotaoOKListener(CliqueListener * listener);
	virtual void setListenerFechar(CliqueListener * listener) override;
	virtual void onClique(Vetor por) override;
	virtual void posicaoCaptada(Vetor pos) override;
	Botao * getBotaoOK();
	void fechar() override;
	void ativar() override;
private:
	std::string texto;	
	tipoMensagem tipo;
	
	Botao 		* botao;
	Imagem		* imagem;
	Label		* labelMensagem;
	//Vetor		tamanho;
	bool		alinhado;
	bool		fechou;
	vector<Componente*> componentes;
	

	class BotaoOKListener : public CliqueListener {
		
	

		virtual void onClique(Vetor pos) override
		{
			// IMP - Implementacao
			//Fazer com o botao OK feche a caixinha de erros !
			// Alterar o foco da caixa de erros para não acessar os elementos atrás (campo nome, campo sexo etc).
			BotaoOKListener::desativarFoco();
		
			
		}
		virtual void posicaoCaptada(Vetor pos) override{}
	};


};
	


         
	
	
	
	


