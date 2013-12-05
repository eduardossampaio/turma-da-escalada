#pragma once
#include "componente.h"
#include "interface.h"

class CheckBox : public Componente , public CliqueListener
{
public:

	CheckBox(Vetor pos);
	CheckBox(Vetor pos,std::string checkboxSelecionado,std::string checkBoxDeselecionado);
	~CheckBox(void);
	virtual void desenhar(IVideoDriver * driver) override;

	bool estaSelecionado();
	void selecionar(bool selecionar);

	virtual void onClique(Vetor pos) override;
	virtual void posicaoCaptada(Vetor pos) override;
private:

	Imagem * imagemSelecionado;
	Imagem * imagemDeselecionado;
	Imagem * imagemParaDesenhar;
	
	bool selecionado;

};

