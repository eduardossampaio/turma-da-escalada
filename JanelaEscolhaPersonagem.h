#pragma once
#include "janela.h"
#include "interface.h"
#include "GerenciadorDeExibicao.h"
#include "GerenciadorExibicao2.h"
#include "PerfilDao.h"
class JanelaEscolhaPersonagem : public Janela
{
public:
	JanelaEscolhaPersonagem(Perfil perfil,scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);
	~JanelaEscolhaPersonagem(void);

	virtual void desenhar() override;
	virtual void remover() override;
	void mudarProximoPersonagem();
	void mudarPersonagemAnterior();
	Mesh_Info getPersonagem();
private:
	void atualizarPersonagem();
	
	
	Imagem * fundo;
	Perfil	perfil;

	
	int selecionado;
	Botao * botaoProximo;
	Botao * botaoAnterior;
	Botao * botaoConfirmar;
	Botao * botaoCancelar;
	Imagem * personagemImg;
	vector<Mesh_Info> personagens;
	tipos::Area areaPersonagem;
	bool alinhouPersonagem;



/* listeners */	
class botaoProximoCharListener : public CliqueListener{
public:
	botaoProximoCharListener(JanelaEscolhaPersonagem * janela) : janela(janela){}

	void onClique(Vetor pos)
	{
		printf("mudar proximo personagem\n");
		janela->mudarProximoPersonagem();
	}
	void posicaoCaptada(Vetor pos)
	{

	}
private:
	JanelaEscolhaPersonagem * janela;
};

class botaoCharAnteriorListener : public CliqueListener{
public:
	botaoCharAnteriorListener(JanelaEscolhaPersonagem * janela) : janela(janela){}
	void onClique(Vetor pos)
	{
		printf("mudar personagem anterior\n");
		janela->mudarPersonagemAnterior();
	}
	void posicaoCaptada(Vetor pos)
	{

	}
private:
	JanelaEscolhaPersonagem * janela;
};

	
class BotaoConfirmarListener : public CliqueListener
{
public:
	BotaoConfirmarListener(JanelaEscolhaPersonagem * janela,Perfil perfil):janela(janela),perfil(perfil){}

	void onClique(Vetor pos)
	{
		printf("criou\n");
		Mesh_Info info = janela->getPersonagem();
		
		//lembrar de trocar
		perfil.personagem = info.id;
		
		
		PerfilDao * dao = new PerfilDao();
		Save save= Save(perfil,0);
		save.inventario.moedas = 1600;
		dao->criarPerfil(save);
		janela->exibirMensagemSimples("Perfil criado com sucesso", new BotaoOkListener());
	}
	void posicaoCaptada(Vetor pos)
	{

	}

private:
	JanelaEscolhaPersonagem * janela;
	Perfil perfil;

};
class BotaoOkListener : public CliqueListener
{
public:
	void onClique(Vetor pos) override
	{
		GerenciadorDeExibicao::getGerenciador()->removerUltimaJanelaExibida();
		GerenciadorDeExibicao::getGerenciador()->removerUltimaJanelaExibida();
	}
	void posicaoCaptada(Vetor pos) override{}
};
class BotaoCancelarListener : public CliqueListener
{
public:
	BotaoCancelarListener(JanelaEscolhaPersonagem * janela):janela(janela){}

	void onClique(Vetor pos)
	{
		printf("cancelou\n");
		
		
		GerenciadorDeExibicao::getGerenciador()->removerUltimaJanelaExibida();
		GerenciadorDeExibicao::getGerenciador()->removerUltimaJanelaExibida();
		
		//janela->drop();
		//GerenciadorExibicao2::getInstancia()->removerUltimaJanela();
	}
	void posicaoCaptada(Vetor pos)
	{

	}

private:
	JanelaEscolhaPersonagem * janela;

};


};
