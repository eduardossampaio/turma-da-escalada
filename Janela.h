#pragma once
#include <irrlicht.h>
#include "Exibivel.h"
#include "Componente.h"
#include <iostream>
#include <vector>
#include "interface.h"
#include "CaixaMensagemSimple.h"
using namespace std;


using namespace irr;

class Janela : public irr::scene::ISceneNode , public Exibivel
{
public:
	Janela(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);
	~Janela(void);
	void iniciar();
	virtual	void remover();
	virtual void desenhar() =0;	
	virtual const core::aabbox3d<f32>& getBoundingBox() const;
	virtual u32 getMaterialCount() const;	
	virtual video::SMaterial& getMaterial(u32 i);
	virtual void render();
	virtual void OnRegisterSceneNode();
	virtual bool emExecucao() override;
	void retirarFocoComponentes();
	void adicioarFocoComponentes();
	void removerComponente(Componente * componente);
//public:
	//rever isso aqui
	static scene::ISceneManager* manager;

protected:
	vector<Componente *> componentes;
	Cursor * cursor;
	CaixaMensagem * caixaMensagemSimples;
	
	
	void desenharComponentes();
	
	void exibirMensagemSimples(std::string msg,CliqueListener * list = 0);
	void exibirMensagemErro(std::string msg,CliqueListener * list = 0);
	void exibirMensagemAlerta(std::string msg,CliqueListener * list = 0);
	void exibirMensagem(CaixaMensagem * caixa); 

private:
	void exibirMensagem(std::string msg,tipoMensagem tipo);
	//exibirMensagem(msg : string,tipo: tipoMensagem ): void
	

	class fecharCaixaMensagemListener : public CliqueListener
	{
	public:
		fecharCaixaMensagemListener(CaixaMensagem * caixa,Janela * janela) : caixaMensagem(caixa),janela(janela) {}
		void onClique(Vetor pos) override
		{
			printf("clicou\n");
			janela->adicioarFocoComponentes();
			caixaMensagem->habilitar(false);
			caixaMensagem->fechar();
			janela->removerComponente(caixaMensagem);
		}
		void posicaoCaptada(Vetor pos) override
		{

		}
	private:
		CaixaMensagem * caixaMensagem;
		Janela * janela;
	};

	
};

