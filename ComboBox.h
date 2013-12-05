#pragma once
#include "componente.h"
#include "interface.h"
#include "irrlicht.h"
#include "Globais.h"
#include "Imagem.h"

using namespace irr;
using namespace gui;
class ComboBox : public Componente , public CliqueListener
{
public:
	ComboBox(Vetor posicao,Vetor tamanho);
	ComboBox(Vetor posicao,Vetor tamanho,std::string imagem);
	~ComboBox(void);

	virtual void desenhar(IVideoDriver * driver) override;

	std::string getItemSelecionado();
	void setItens(vector<std::string> itens);
	void setItens(std::string itens...);
	void addItens(std::string itens,bool seleciona = false);
	vector<std::string> getItens();


	virtual void onClique(Vetor posicao) override;
	virtual void posicaoCaptada(Vetor posicao) override;

	bool comboEstaAberta();
	void selecionaItem(int indice);

private:
	Vetor tamanho;
	Vetor tamanhoLabel;
	// Imagem * imagem; - Referencia da pasta image
	vector<std::string> itens;
	std::string itemSelecionado;
	int indiceSelecioado;
	bool comboAberta;

	inline bool cursorEmCimaComboAberta(Vetor pos);
	void selecionaItem(Vetor pos);
	IGUIFont *font;
	Label  * texto;
};

