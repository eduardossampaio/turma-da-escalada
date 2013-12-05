#include "stdafx.h"
#include "JanelaLoja.h"
#include "ItemDAO.h"
#include "Configuracoes.h"

JanelaLoja::JanelaLoja(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id):Janela(parent,mgr,32)
{
	JanelaLoja::fundo= new Imagem("ui/janela/loja.jpg");
	JanelaLoja::botaoTeste= new Botao(tipos::Vetor(50,100),"ui/botoes/em-branco-normal.png","Teste","comic",TAMANHO::PEQUENO);



	JanelaLoja::componentes.push_back(fundo);
	JanelaLoja::componentes.push_back(botaoTeste);
	JanelaLoja::cursor= new KinectCursor();
	JanelaLoja::cursor->adicionarListener(botaoTeste);
	JanelaLoja::botaoTeste->addListener(new botaoTesteListener());
	ItemDAO *itemDao = new ItemDAO() ;
	JanelaLoja::itensLoja= itemDao->getItens();

	// Obtendo a configuracao da tela para exibicao dos itens
	Configuracoes * conf = new Configuracoes();


}


JanelaLoja::~JanelaLoja(void)
{
}



void JanelaLoja::desenhar()
{
	for(int aux=0; aux<componentes.size(); aux++){
		componentes[aux]->desenhar(SceneManager->getVideoDriver());
	
	}
	cursor->desenhar(SceneManager->getVideoDriver());

}
	
	
bool JanelaLoja::emExecucao()
{
	return IsVisible;
}