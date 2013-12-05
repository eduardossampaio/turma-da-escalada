#include "stdafx.h"
#include "JanelaEscolhaFase.h"
#include "Marcador.h"
#include "Configuracoes.h"
//teste
#include "Marcador.h"
#include "CaixaMensagemSimple.h"
#include "tipos.h"
CaixaMensagemSimple * caixa;

JanelaEscolhaFase::JanelaEscolhaFase(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id,tipos::Save perfil):Janela(parent,mgr,32),perfil(perfil)
{
	JanelaEscolhaFase::fundo = new Imagem("ui/janela/mapa_brasil.png");
	JanelaEscolhaFase::jogador = new Jogador(perfil);
	JanelaEscolhaFase::componentes.push_back(fundo);
	JanelaEscolhaFase::cursor = new KinectCursor();	
	Marcador *marcador = new Marcador(Vetor(60,10),SceneManager,jogador,this);
	JanelaEscolhaFase::cursor ->adicionarListener(marcador);
	JanelaEscolhaFase::componentes.push_back(marcador);

	//JanelaEscolhaFase::botaoJogar = new Botao(Vetor(),"ui/botoes/em-branco-pequeno.png","Jogar","comic",TAMANHO::MEDIO);
	tipos::configuracoes configuracoes = (new Configuracoes())->carregarConfigucacoes();
	
	JanelaEscolhaFase::botaoVoltar = new Botao(
		Vetor(configuracoes.resolucao.x*0.1,(configuracoes.resolucao.y - configuracoes.resolucao.y*0.2)),
		"ui/botoes/em-branco-pequeno.png","Voltar","comic",TAMANHO::MEDIO);

	JanelaEscolhaFase::botaoLoja = new Botao(
		Vetor(configuracoes.resolucao.x-configuracoes.resolucao.x*0.4,(configuracoes.resolucao.y - configuracoes.resolucao.y*0.2)),
		"ui/botoes/em-branco-pequeno.png","Loja","comic",TAMANHO::MEDIO);
	
	JanelaEscolhaFase::botaoLoja->addListener(new BotaoLojaListener(this));
	JanelaEscolhaFase::botaoVoltar->addListener(new BotaoVoltarListener());

	JanelaEscolhaFase::cursor->adicionarListener(botaoLoja);
	JanelaEscolhaFase::cursor->adicionarListener(botaoVoltar);
	
	JanelaEscolhaFase::componentes.push_back(botaoLoja);
	JanelaEscolhaFase::componentes.push_back(botaoVoltar);

	

	//caixa=new CaixaMensagem(Vetor(100,200),Vetor(800,300),"Teste da caixa\nde mensagem",tipoMensagem::ALERTA);
}


JanelaEscolhaFase::~JanelaEscolhaFase(void)
{
}
void JanelaEscolhaFase::exibirErro(std::string msg)
{
	exibirMensagemErro(msg);
}
void JanelaEscolhaFase::desenhar()
{
	//for(int i=0;i<componentes.size();i++)
		//JanelaEscolhaFase::componentes[i]->desenhar(SceneManager->getVideoDriver());
	desenharComponentes();
	JanelaEscolhaFase::cursor->desenhar(SceneManager->getVideoDriver());
	

}

tipos::Save JanelaEscolhaFase::getPerfil()
{
	return JanelaEscolhaFase::perfil;
}



bool JanelaEscolhaFase::emExecucao()
{
	return IsVisible;
}
Jogador * JanelaEscolhaFase::getJogador()
{
	return JanelaEscolhaFase::jogador;
}