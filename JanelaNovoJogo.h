#pragma once
#include "Janela.h"
#include "JanelaEscolhaPersonagem.h"
#include "CaixaTexto.h"
#include "Cursor.h"
#include "TecladoVirtual.h"
#include "Botao.h"
#include "GerenciadorDeExibicao.h"
#include "GerenciadorExibicao2.h"
#include "Irrlicht.h"
#include "PerfilDao.h"
//#include "validaUteis.h"


using namespace irr;
using namespace gui;
using namespace video;
using namespace scene;
class JanelaNovoJogo : public Janela
{
public:
	JanelaNovoJogo(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);
	JanelaNovoJogo(void);
	~JanelaNovoJogo(void);
	virtual void desenhar() override;
	virtual bool emExecucao() override;
	Perfil getPerfil();
	vector<CaixaTexto * > getCaixasTexto();
	void apresentaMsgErro (std::string listaMensagens,JanelaNovoJogo * janela);

private:
	void setComponentes();
	CaixaTexto * caixaNome;
	CaixaTexto * caixaIdade;
	CaixaTexto * caixaSexo;
	CaixaTexto * caixaPeso;
	Botao	   * botaoCancelar;
	Botao	   * botaoCriar;
	Label      * labelNome;
	Label      * labelIdade;
	Label      * labelPeso;
	Label      * labelSexo;


	//Cursor * cursor;
	vector<CaixaTexto * > caixasTexto;
	TecladoVirtual * teclado;
	
	
	static int id_janela;



class BotaoCancelarListener : public CliqueListener
{

public:
	
	virtual void onClique(Vetor pos) override
	{
		printf("botao cancelar\n");
		GerenciadorDeExibicao::getGerenciador()->removerUltimaJanelaExibida();
		//GerenciadorExibicao2::getInstancia()->removerUltimaJanela();
	}
	virtual void posicaoCaptada(Vetor pos) override{}

};

class BotaoCriarListener : public CliqueListener
{
private:
	//ISceneManager * manager;
	JanelaNovoJogo * janela;

public:
	BotaoCriarListener(JanelaNovoJogo * janela):janela(janela){}
	
	virtual void onClique(Vetor pos) override
	{
		printf("botao criar\n");
		//manager->getRootSceneNode()->removeAll();
		std::string listaMensagens;
		
		//GerenciadorExibicao2::getInstancia()->novaJanelaExibicao(tipos::JanelaExibicao::Janela_Escolha_Personagem);
		Perfil perfil = janela->getPerfil();
		// Validadao do perfil antes da criacao efetiva
		//new Imagem("ui/janela/novo-jogo.png"));
		
		
		 // Dados corretos avanca para a proxima tela
		GerenciadorDeExibicao::getGerenciador()->novaJanelaParaExibicao(new JanelaEscolhaPersonagem(perfil,manager->getRootSceneNode(),manager,id_janela));
		id_janela++;

	}
	virtual void posicaoCaptada(tipos::Vetor posicao) override{}

	

};


class BotaoValidarListener : public CliqueListener
{
private:
	//ISceneManager * manager;
	JanelaNovoJogo * janela;

public:
	BotaoValidarListener(JanelaNovoJogo * janela):janela(janela){
		
	}
	
	virtual void onClique(Vetor pos) override
	{
		printf("botao validar dados\n");
		//manager->getRootSceneNode()->removeAll();
		std::string listaMensagens;
		
		
		Perfil perfil = janela->getPerfil();
		// Validadao do perfil antes da criacao efetiva
		//new Imagem("ui/janela/novo-jogo.png"));
		bool flag = false; // indicando se houve algum erro.
		if (perfil.nome.length() < 1 || perfil.nome.length() > 200) {
			listaMensagens.append(" * Insira um nome de 1 a 200 caracteres ! \n ");
			flag = true;
		}
		
		if (perfil.idade < 6 || perfil.idade > 12) {
			listaMensagens.append(" * A idade deve estar entre 6 a 12 anos ! \n");
			flag = true;
		}
		
		if(perfil.peso < 20) {
			listaMensagens.append(" * O peso deve estar no minimo com 20 kg ! \n");
			flag = true;
		}
		
		// if(save.perfil.sexo==Sexo::MASCULINO)
		if(perfil.sexo != Sexo::FEMININO && perfil.sexo != Sexo::MASCULINO) { // sexo
			flag = true;
			listaMensagens.append(" * Deve escolher o sexo feminino ou masculino ! \n");
		}
		

		
		if (flag==true) { // teve erros, mostre-o.
			janela->apresentaMsgErro(listaMensagens,janela);
		}
		else { // nao teve erros, entao chame a proxima tela
				GerenciadorDeExibicao::getGerenciador()->novaJanelaParaExibicao(new JanelaEscolhaPersonagem(perfil,manager->getRootSceneNode(),manager,20));
		}
		
	}
	virtual void posicaoCaptada(tipos::Vetor posicao) override{}

	

};

};