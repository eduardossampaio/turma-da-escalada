#include "stdafx.h"


#include "KinectCursor.h"
#include "Janelas.h"
#include "interface.h"
#include "Conversoes.h"
#include "CaixaMensagemSimple.h"

int JanelaNovoJogo::id_janela = 21;

class SelecionaCaixaListener : public CliqueListener
{
	public:
	JanelaNovoJogo * janela;
	SelecionaCaixaListener(const JanelaNovoJogo * janela){
	SelecionaCaixaListener::janela = (JanelaNovoJogo*) janela;
	}

	void SelecionaCaixaListener::onClique(Vetor v) override
	{
		printf("clicou\n");
		vector<CaixaTexto *> caixas = SelecionaCaixaListener::janela->getCaixasTexto();
		for(int i=0;i<caixas.size();i++){
			CaixaTexto * t = caixas[i];			
			t->setSelecionado(t->posicaoDentroCaixa(v) || (t->getTeclado()->habilitado() && t->getTeclado()->emCimaDoTeclado(v)));						
			
		}
	}
	virtual void posicaoCaptada(tipos::Vetor posicao) override{};

};


JanelaNovoJogo::JanelaNovoJogo(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id) : Janela(parent,mgr,id)
{
	setComponentes();
}

JanelaNovoJogo::JanelaNovoJogo() : Janela(Janela::manager->getRootSceneNode(),Janela::manager,13)
{
	setComponentes();
}


void JanelaNovoJogo::setComponentes()
{
	JanelaNovoJogo::componentes.push_back(new Imagem("ui/janela/novo-jogo.png"));
	JanelaNovoJogo::labelNome = new Label(Vetor(10,10),"Nome");
	JanelaNovoJogo::labelIdade = new Label(Vetor(10,100),"Idade");
	JanelaNovoJogo::labelPeso = new Label(Vetor(10,190),"Peso");
	JanelaNovoJogo::labelSexo = new Label(Vetor(10,290),"Sexo");

	
	//JanelaNovoJogo::teclado =
		 //new TecladoAlfaNumerico(Vetor(0,450));
		//new TecladoNumerico(Vetor(0,450));
		//new TecladoGenero(Vetor(0,450));

	TecladoVirtual * tecladoLetra	=	new TecladoAlfaNumerico(Vetor(0,450));
	TecladoVirtual * tecladoNum1	=	new TecladoNumerico(Vetor(0,450));
	TecladoVirtual * tecladoNum2	=	new TecladoNumerico(Vetor(0,450));
	TecladoVirtual * tecladoGen		=	new TecladoGenero(Vetor(0,450));
	
	JanelaNovoJogo::caixaNome		=	new CaixaTexto(Vetor(140,10),Vetor(450,60));
	JanelaNovoJogo::caixaIdade		=	new CaixaTexto(Vetor(140,100),Vetor(450,60));
	JanelaNovoJogo::caixaPeso		=	new CaixaTexto(Vetor(140,190),Vetor(450,60));
	JanelaNovoJogo::caixaSexo		=	new CaixaTexto(Vetor(140,280),Vetor(450,60));


	JanelaNovoJogo::caixaNome->setTeclado(tecladoLetra);
	JanelaNovoJogo::caixaIdade->setTeclado(tecladoNum1);
	JanelaNovoJogo::caixaPeso->setTeclado(tecladoNum2);
	JanelaNovoJogo::caixaSexo->setTeclado(tecladoGen);


	JanelaNovoJogo::botaoCriar	  = new Botao(Vetor(655,150),"ui/botoes/em-branco-normal.png","CONTINUAR","comic",PEQUENO);
	JanelaNovoJogo::botaoCriar->setTamanho(Vetor(249,42));

	JanelaNovoJogo::botaoCancelar = new Botao(Vetor(655,260),"ui/botoes/em-branco-normal.png","CANCELAR","comic",PEQUENO); 
	JanelaNovoJogo::botaoCancelar->setTamanho(Vetor(249,42)); 
	

	JanelaNovoJogo::componentes.push_back(JanelaNovoJogo::labelNome);
	JanelaNovoJogo::componentes.push_back(JanelaNovoJogo::labelIdade);
	JanelaNovoJogo::componentes.push_back(JanelaNovoJogo::labelPeso);
	JanelaNovoJogo::componentes.push_back(JanelaNovoJogo::labelSexo);
	
	JanelaNovoJogo::componentes.push_back(JanelaNovoJogo::caixaNome);
	JanelaNovoJogo::componentes.push_back(JanelaNovoJogo::caixaIdade);
	JanelaNovoJogo::componentes.push_back(JanelaNovoJogo::caixaSexo);
	JanelaNovoJogo::componentes.push_back(JanelaNovoJogo::caixaPeso);
	JanelaNovoJogo::componentes.push_back(JanelaNovoJogo::botaoCancelar);
	JanelaNovoJogo::componentes.push_back(JanelaNovoJogo::botaoCriar);

	JanelaNovoJogo::componentes.push_back(tecladoGen);
	JanelaNovoJogo::componentes.push_back(tecladoNum1);
	JanelaNovoJogo::componentes.push_back(tecladoNum2);
	JanelaNovoJogo::componentes.push_back(tecladoLetra);
	
	//JanelaNovoJogo::componentes.push_back(teclado);

	JanelaNovoJogo::caixaNome->habilitar(true);

	JanelaNovoJogo::caixasTexto.push_back(JanelaNovoJogo::caixaNome);
	JanelaNovoJogo::caixasTexto.push_back(JanelaNovoJogo::caixaIdade);	
	JanelaNovoJogo::caixasTexto.push_back(JanelaNovoJogo::caixaPeso);
	JanelaNovoJogo::caixasTexto.push_back(JanelaNovoJogo::caixaSexo);


	JanelaNovoJogo::cursor = new KinectCursor();
	
	JanelaNovoJogo::cursor->adicionarListener(new SelecionaCaixaListener(this));

	JanelaNovoJogo::cursor->adicionarListener(tecladoGen);
	JanelaNovoJogo::cursor->adicionarListener(tecladoNum1);
	JanelaNovoJogo::cursor->adicionarListener(tecladoNum2);
	JanelaNovoJogo::cursor->adicionarListener(tecladoLetra);


	JanelaNovoJogo::botaoCancelar->addListener(new BotaoCancelarListener());
	
	//tipos::flag = true;
	JanelaNovoJogo::botaoCriar->addListener(new BotaoValidarListener(this));


	
	/*
	if(tipos::vezes!=0 || tipos::flag==true){
			JanelaNovoJogo::botaoCriar->addListener(new BotaoValidarListener(this));
			if(!tipos::flag){
				JanelaNovoJogo::botaoCriar->addListener(new BotaoCriarListener(this));
		}
	}
	tipos::vezes++;	
	printf("--------------------------------Vezes:%d",tipos::vezes);
	*/
	
	JanelaNovoJogo::cursor->adicionarListener(botaoCancelar);
	JanelaNovoJogo::cursor->adicionarListener(botaoCriar);
	

}
Perfil JanelaNovoJogo::getPerfil()// validação
{
	Perfil perfil;
	perfil.nome  = JanelaNovoJogo::caixaNome->getTexto();
	perfil.idade = Conversoes::converteParaInt( JanelaNovoJogo::caixaIdade->getTexto() );
	perfil.peso  = Conversoes::converteParaInt( JanelaNovoJogo::caixaPeso->getTexto() );
	if(strcmp(JanelaNovoJogo::caixaSexo->getTexto().c_str(),"MENINO")==0) 
		perfil.sexo = Sexo::MASCULINO;
	else if(strcmp(JanelaNovoJogo::caixaSexo->getTexto().c_str(),"MENINA")==0)
			perfil.sexo = Sexo::FEMININO;
	
	PerfilDao * dao = new PerfilDao();
	perfil.id = dao->gerarIdPersonagem();
	return perfil;
}
JanelaNovoJogo::~JanelaNovoJogo(void)
{
}

void JanelaNovoJogo::desenhar()

{
	bool mostrarTeclado = false;
	if(teclado!=NULL && teclado->habilitado() && teclado->emCimaDoTeclado(JanelaNovoJogo::cursor->getPosicao()))
		mostrarTeclado=true;
	else{
		for(int i=0;i<JanelaNovoJogo::getCaixasTexto().size();i++){
			if(JanelaNovoJogo::getCaixasTexto()[i]->estaSelecionado()){
				mostrarTeclado = true;
				JanelaNovoJogo::teclado = JanelaNovoJogo::getCaixasTexto()[i]->getTeclado();
				JanelaNovoJogo::teclado->setAlvo(JanelaNovoJogo::getCaixasTexto()[i]);
			}
			else{
				JanelaNovoJogo::getCaixasTexto()[i]->getTeclado()->habilitar(false);
			}
		}
	}
	
//	for(int i=0;i<JanelaNovoJogo::componentes.size();i++){
		//JanelaNovoJogo::componentes[i]->desenhar(SceneManager->getVideoDriver());
	//}
	
	desenharComponentes();
	
	if(JanelaNovoJogo::teclado)
	{
		JanelaNovoJogo::teclado->habilitar(mostrarTeclado);	
		//JanelaNovoJogo::teclado->desenhar(SceneManager->getVideoDriver());
	}
	


	
	JanelaNovoJogo::cursor->getIcone()->desenhar(SceneManager->getVideoDriver());
}

bool JanelaNovoJogo::emExecucao()
{

	return IsVisible;
}

vector<CaixaTexto * > JanelaNovoJogo::getCaixasTexto()
{
	return JanelaNovoJogo::caixasTexto;
}

void JanelaNovoJogo::apresentaMsgErro (std::string listaMensagens,JanelaNovoJogo * janela) {
	//janela->componentes.push_back();
	//janela->desenhar
	//exibirMensagem(new CaixaMensagemSimple(Vetor(80, 40), Vetor(900, 500), listaMensagens, tipoMensagem::ERRO));
	exibirMensagemErro(listaMensagens);

}



