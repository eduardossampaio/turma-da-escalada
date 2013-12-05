#include "stdafx.h"
#include "Janelas.h"
#include "Conversoes.h"


JanelaConfiguracao::JanelaConfiguracao(void):Janela(Janela::manager->getRootSceneNode(),Janela::manager,14)
{
	setarComponentes();
}
JanelaConfiguracao::JanelaConfiguracao(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id) : Janela(parent,mgr,id)
{
	setarComponentes();
}


void JanelaConfiguracao::setarComponentes()
{
	JanelaConfiguracao::fundo = new Imagem("ui/janela/configuracoes.jpg");

	JanelaConfiguracao::labelResolucao = new Label(Vetor(50,128),"Resolucao");
	JanelaConfiguracao::labelCor	   = new Label(Vetor(50,256),"Cor");
	JanelaConfiguracao::labelMao	   = new Label(Vetor(50,384),"Mao");
	JanelaConfiguracao::labelFullScreen= new Label(Vetor(50,512),"Tela cheia");


	JanelaConfiguracao::comboResolucao	= new ComboBox(Vetor(250,128),Vetor(500,40));	//Posição- Tamanho
	
	JanelaConfiguracao::comboCor		= new ComboBox(Vetor(250,256),Vetor(500,40));	
	JanelaConfiguracao::comboMao		= new ComboBox(Vetor(250,384),Vetor(500,40));	
	JanelaConfiguracao::checkFullScreen = new CheckBox(Vetor(250,512));

	JanelaConfiguracao::botaoCancelar   = new Botao(Vetor(250,700),"ui/botoes/em-branco-normal.png","CANCELAR","comic",PEQUENO);
	JanelaConfiguracao::botaoSalvar     = new Botao(Vetor(550,700),"ui/botoes/em-branco-normal.png","SALVAR","comic",PEQUENO);
	JanelaConfiguracao::botaoCancelar->addListener(new BotaoCancelarListener());
	JanelaConfiguracao::botaoSalvar->addListener(new BotaoSalvarListener(this));

	JanelaConfiguracao::componentes.push_back(fundo);
	
	JanelaConfiguracao::componentes.push_back(comboResolucao);
	JanelaConfiguracao::componentes.push_back(comboCor);
	JanelaConfiguracao::componentes.push_back(comboMao);
	JanelaConfiguracao::componentes.push_back(checkFullScreen);

	JanelaConfiguracao::combos.push_back(comboResolucao);
	JanelaConfiguracao::combos.push_back(comboCor);
	JanelaConfiguracao::combos.push_back(comboMao);


	JanelaConfiguracao::cursor = new KinectCursor();
	
	JanelaConfiguracao::cursor->adicionarListener(comboResolucao);
	JanelaConfiguracao::cursor->adicionarListener(comboCor);
	JanelaConfiguracao::cursor->adicionarListener(comboMao);
	JanelaConfiguracao::cursor->adicionarListener(checkFullScreen);
	JanelaConfiguracao::cursor->adicionarListener(botaoSalvar);
	JanelaConfiguracao::cursor->adicionarListener(botaoCancelar);

	JanelaConfiguracao::componentes.push_back(labelResolucao);
	JanelaConfiguracao::componentes.push_back(labelCor);
	JanelaConfiguracao::componentes.push_back(labelMao);
	JanelaConfiguracao::componentes.push_back(labelFullScreen);
	JanelaConfiguracao::componentes.push_back(botaoCancelar);
	JanelaConfiguracao::componentes.push_back(botaoSalvar);
	
	Configuracoes *  dao = new Configuracoes();
	tipos::configuracoes config = dao->carregarConfigucacoes();
	
	JanelaConfiguracao::comboResolucao->addItens("800 X 600",(config.resolucao.x == 800  && config.resolucao.y == 600));
	JanelaConfiguracao::comboResolucao->addItens("1024 X 768",(config.resolucao.x == 1024  && config.resolucao.y == 768));
	
	JanelaConfiguracao::comboCor->addItens("16 bits",(config.bitsCor == 16));
	JanelaConfiguracao::comboCor->addItens("32 bits",(config.bitsCor == 32));

	JanelaConfiguracao::comboMao->addItens("Mao direita",(config.mao==tipos::Mao::DIREITA)); 
	JanelaConfiguracao::comboMao->addItens("Mao esquerda",(config.mao==tipos::Mao::ESQUERDA)); 

	JanelaConfiguracao::checkFullScreen->selecionar(config.fullscreen);

	

//	teste = new Botao(Vetor(100,100),"ui/botoes/em-branco.png");

}

JanelaConfiguracao::~JanelaConfiguracao(void)
{
}

void JanelaConfiguracao::desenhar()
{
	
	for(int i=0;i<JanelaConfiguracao::componentes.size();i++){
		JanelaConfiguracao::componentes[i]->desenhar(SceneManager->getVideoDriver());
	}
	for(int i=0;i<JanelaConfiguracao::combos.size();i++)
		if(JanelaConfiguracao::combos[i]->comboEstaAberta())
			JanelaConfiguracao::combos[i]->desenhar(SceneManager->getVideoDriver());
	
	/*
	teste->desenhar(SceneManager->getVideoDriver());
	for(int i=0;i<JanelaConfiguracao::componentes.size();i++){
		JanelaConfiguracao::componentes[i]->atualizarPosisao(
									Vetor(
									JanelaConfiguracao::componentes[i]->getPosisao().x+1,
									JanelaConfiguracao::componentes[i]->getPosisao().y+1));

	}*/
	//teste->
	cursor->desenhar(SceneManager->getVideoDriver());
	
}

tipos::configuracoes  JanelaConfiguracao::getConfiguracoes()
{
	std::string resulucao	= JanelaConfiguracao::comboResolucao->getItemSelecionado();
	std::string cor			= JanelaConfiguracao::comboCor->getItemSelecionado();
	bool fullscreen			= JanelaConfiguracao::checkFullScreen->estaSelecionado();
	std::string mao			= JanelaConfiguracao::comboMao->getItemSelecionado();
	tipos::configuracoes conf = configuracoes();
	int indiceX = resulucao.find("X");
	std::string lar = resulucao.substr(0,indiceX);
	std::string alt = resulucao.substr(indiceX+1);
	cor = cor.substr(0,cor.find("bits"));
	conf.resolucao=Vetor(Conversoes::converteParaInt(lar),Conversoes::converteParaInt(alt));
	conf.bitsCor = Conversoes::converteParaInt(cor);
	conf.fullscreen=fullscreen;
	if(strcmp(mao.c_str(),"Mao direita")==0)
		conf.mao = Mao::DIREITA;
	else
		conf.mao = Mao::ESQUERDA;
	return conf;
}