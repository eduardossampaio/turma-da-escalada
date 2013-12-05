#include "stdafx.h"
#include "JanelaEscolhaPerfil.h"
#include "Configuracoes.h"
#include "Conversoes.h"
#include "PerfilDao.h"
#include "PersonagemDAO.h"
using namespace tipos;

JanelaEscolhaPerfil::JanelaEscolhaPerfil(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id):Janela(parent,mgr,id)
{
	JanelaEscolhaPerfil::fundo = new Imagem(Vetor(),"ui/janela/escolha_perfil.jpg");
	Configuracoes * configuracoes = new Configuracoes();
	tipos::configuracoes config = configuracoes->carregarConfigucacoes();
	JanelaEscolhaPerfil::indiceSave = 0;
	JanelaEscolhaPerfil::cursor = new KinectCursor();

	JanelaEscolhaPerfil::corFundo = video::SColor(255,245,245,245); // cor cinza tendendo ao branco
	JanelaEscolhaPerfil::corLetra = video::SColor(255,0,0,0); // cor preta
	JanelaEscolhaPerfil::tamanhoTela = config.resolucao;
	//teste
	//JanelaEscolhaPerfil::saves.push_back(  Save(Perfil("Eduardo","modelos/personagem/boneco1/boneco.obj",21,67,Sexo::MASCULINO),9999999));
	//JanelaEscolhaPerfil::saves.push_back(  Save(Perfil("Roger"	,"modelos/personagem/boneco1/boneco.obj",21,67,Sexo::MASCULINO),0));
	//JanelaEscolhaPerfil::saves.push_back(  Save(Perfil("Bruna"	,"modelos/personagem/boneco1/boneco.obj",21,67,Sexo::FEMININO),-1));
	PerfilDao * dao = new PerfilDao();
	
	JanelaEscolhaPerfil::saves = dao->carregarPerfis();
	areaPersonagem.v1.x = 0;
	areaPersonagem.v1.y = 0;
	areaPersonagem.v2.x = tamanhoTela.x - tamanhoTela.x*0.4;
	areaPersonagem.v2.y = tamanhoTela.y - tamanhoTela.y * 0.2;

	alinhouPersonagem = false;
	
	float xInicial = tamanhoTela.x - tamanhoTela.x*0.4;
	float yInicial = 0;
	float yFinal = tamanhoTela.y*0.2;
	float xFinal   = tamanhoTela.x-xInicial;
	char *temp;
	
	//if (saves.size()!=0) {
	JanelaEscolhaPerfil::labelNomeTexto = new Label(
			Vetor(xInicial*0.8,yInicial),
			Vetor(xFinal,  yFinal),
			saves.size()==0?"Nome:":"",
			"comic",
			TAMANHO::MEDIO
			,true,
			true,
			"255255255"
			);
		JanelaEscolhaPerfil::labelNome = new Label(
			Vetor(xInicial,yInicial),
			Vetor(xFinal,  yFinal),
			saves.size()>0?getSaveSelecionado().perfil.nome:"",
			"comic",
			TAMANHO::GRANDE
			,true,
			true,
			"255255255"
			);



		JanelaEscolhaPerfil::labelIdadeTexto = new Label(
			Vetor(xInicial,yFinal),
			Vetor(xFinal/2,yFinal*0.3),
			"Idade:",
			"comic",
			TAMANHO::MEDIO,
			true,
			true,
			"255255255"
		);
		//Conversoes::converteParaChar(&temp,getSaveSelecionado().perfil.idade);
		JanelaEscolhaPerfil::labelIdade = new Label(
			Vetor(xInicial+xFinal/2,yFinal),
			Vetor(xFinal/2,yFinal*0.3),
			saves.size()>0?Conversoes::converteParaString(getSaveSelecionado().perfil.idade).c_str():"",
			"comic",
			TAMANHO::MEDIO,
			true,
			true,
			"255255255" 
		);


		JanelaEscolhaPerfil::labelPesoTexto = new Label(
			Vetor(xInicial,tamanhoTela.y*0.3),
			Vetor(xFinal/2,yFinal*0.3),
			"Peso:",
			"comic",
			TAMANHO::MEDIO,
			true,
			true,
			"255255255"
		);
		JanelaEscolhaPerfil::labelPeso = new Label(
			Vetor(xInicial+xFinal/2,tamanhoTela.y*0.3),
			Vetor(xFinal/2,yFinal*0.3),
			//getSaveSelecionado().perfil.idade+"",
			saves.size()>0?Conversoes::converteParaString(getSaveSelecionado().perfil.peso).c_str():"",
			"comic",
			TAMANHO::MEDIO,
			true,
			true,
			"255255255"
		);	
	
		JanelaEscolhaPerfil::labelSexoTexto = new Label(
			Vetor(xInicial,tamanhoTela.y*0.4),
			Vetor(xFinal/2,yFinal*0.3),
			"Sexo:",
			"comic",
			TAMANHO::MEDIO,
			true,
			true,
			"255255255"
		);
		JanelaEscolhaPerfil::labelSexo = new Label(
			Vetor(xInicial+xFinal/2,tamanhoTela.y*0.4),
			Vetor(xFinal/2,yFinal*0.3),
			saves.size()>0?Conversoes::converteParaString(getSaveSelecionado().perfil.sexo).c_str():"",
			"comic",
			TAMANHO::MEDIO,
			true,
			true,
			"255255255"
		);
	

		JanelaEscolhaPerfil::labelPontosTexto = new Label(
			Vetor(xInicial,tamanhoTela.y*0.5),
			Vetor(xFinal/2,yFinal*0.3),
			"Pontos:",
			"comic",
			TAMANHO::MEDIO,
			true,
			true,
			"255255255"
		);
		JanelaEscolhaPerfil::labelPontos = new Label(
			Vetor(xInicial+xFinal/2,tamanhoTela.y*0.5),
			Vetor(xFinal/2,yFinal*0.3),
			saves.size()>0?Conversoes::converteParaString(getSaveSelecionado().pontos):"",
			"comic",
			TAMANHO::MEDIO,
			true,
			true,
			"255255255"
		);
		
	
	

	JanelaEscolhaPerfil::botaoProximo=new Botao(Vetor(xInicial+xFinal/2,tamanhoTela.y*0.9),"media/icones/proximo.png");
	JanelaEscolhaPerfil::botaoAnterior=new Botao(Vetor(xInicial,tamanhoTela.y*0.9),"media/icones/anterior.png");
	JanelaEscolhaPerfil::botaoCarregar=new Botao(Vetor(xInicial,tamanhoTela.y*0.6),"ui/botoes/em-branco-normal.png","CARREGAR","comic",PEQUENO);
	JanelaEscolhaPerfil::botaoExcluir=new Botao(Vetor(xInicial,tamanhoTela.y*0.7),"ui/botoes/em-branco-normal.png","EXCLUIR","comic",PEQUENO);
	JanelaEscolhaPerfil::botaoCancelar=new Botao(Vetor(xInicial,tamanhoTela.y*0.8),"ui/botoes/em-branco-normal.png","CANCELAR","comic",PEQUENO);
	

	JanelaEscolhaPerfil::botaoProximo->addListener(new JanelaEscolhaPerfil::ProximoSaveBotaoListener(this));
	JanelaEscolhaPerfil::botaoAnterior->addListener(new JanelaEscolhaPerfil::SaveAnteriorBotaoListener(this));
	JanelaEscolhaPerfil::botaoCarregar->addListener(new JanelaEscolhaPerfil::CarregarBotaoListener(this));
	JanelaEscolhaPerfil::botaoCancelar->addListener(new JanelaEscolhaPerfil::CancelarBotaoListener());
	JanelaEscolhaPerfil::botaoExcluir->addListener(new JanelaEscolhaPerfil::ExcluirBotaoListener(this));
	
	componentes.push_back(fundo);
	componentes.push_back(labelNomeTexto);
	componentes.push_back(labelNome);
	componentes.push_back(labelIdadeTexto);
	componentes.push_back(labelIdade);	
	componentes.push_back(labelPesoTexto);
	componentes.push_back(labelPeso);
	componentes.push_back(labelSexoTexto);
	componentes.push_back(labelSexo);
	componentes.push_back(labelPontosTexto);
	componentes.push_back(labelPontos);
	componentes.push_back(botaoProximo);
	componentes.push_back(botaoAnterior);
	componentes.push_back(botaoCarregar);
	componentes.push_back(botaoCancelar);
	componentes.push_back(botaoExcluir);
	if(saves.size()==0){
		exibirMensagemErro("Nao existem perfis cadastrados",new JanelaEscolhaPerfil::CancelarBotaoListener());
	}
	cursor->adicionarListener(botaoProximo);
	cursor->adicionarListener(botaoAnterior);
	cursor->adicionarListener(botaoCarregar);
	cursor->adicionarListener(botaoCancelar);
	cursor->adicionarListener(botaoExcluir);
	
	
	carregaValoresSave();
	
}


JanelaEscolhaPerfil::~JanelaEscolhaPerfil(void)
{

}



void JanelaEscolhaPerfil::desenhar()
{
	Vetor inicioQuadro = Vetor(tamanhoTela.x - tamanhoTela.x*0.4,0);
	IVideoDriver * driver = SceneManager->getVideoDriver();
	//desenha o quadro
	driver->draw2DRectangle(corFundo,core::rect<s32>(inicioQuadro.x,inicioQuadro.y,tamanhoTela.x,tamanhoTela.y));
	desenharComponentes();
	
	//cursor->atualizar();
	
	cursor->desenhar(driver);

	if(!alinhouPersonagem)
	{
		if(personagem!=NULL)
		{
			Vetor tamanho_personagem = personagem->getTamanho();
			personagem->atualizarPosisao(Vetor(
				(areaPersonagem.v2.x - tamanho_personagem.x) /2,
				(areaPersonagem.v2.y - tamanho_personagem.y) /2));

			alinhouPersonagem = true;
		}
	}	
}
bool JanelaEscolhaPerfil::emExecucao()
{
	return IsVisible;
}

Save JanelaEscolhaPerfil::getSaveSelecionado()
{
	//JanelaEscolhaPerfil::saveExclusao = JanelaEscolhaPerfil::saves[indiceSave]; // coloca o save a excluir
	return JanelaEscolhaPerfil::saves[indiceSave];
}

void JanelaEscolhaPerfil::selecionaPerfilAnterior()
{
	if(indiceSave>0){
		
		indiceSave--;
		carregaValoresSave();
	}
}

void JanelaEscolhaPerfil::selecionaProximoPerfil()
{
	if(indiceSave<saves.size()-1){
		indiceSave++;
		carregaValoresSave();
	}
}

Save JanelaEscolhaPerfil::getPerfilSelecionado()
{
	return saves[indiceSave];

}

void JanelaEscolhaPerfil::carregaValoresSave()
{

	JanelaEscolhaPerfil::labelNome->setTexto(saves.size()>0?getSaveSelecionado().perfil.nome:"");
	JanelaEscolhaPerfil::labelIdade->setTexto(saves.size()>0?Conversoes::converteParaString( getSaveSelecionado().perfil.idade):"");
	if (saves.size()>0){
		if(getSaveSelecionado().perfil.sexo==Sexo::MASCULINO)
		JanelaEscolhaPerfil::labelSexo->setTexto("Masculino");
		if(getSaveSelecionado().perfil.sexo==Sexo::FEMININO)
		JanelaEscolhaPerfil::labelSexo->setTexto("Feminino");
	}
	else
		JanelaEscolhaPerfil::labelSexo->setTexto("");
	JanelaEscolhaPerfil::labelPontos->setTexto(saves.
		size()>0?Conversoes::converteParaString(getSaveSelecionado().pontos):"");
	
	//setupComponentes3d();

	PersonagemDAO * dao = new PersonagemDAO();
	if(saves.size()>0){
		Mesh_Info * mesh_info = dao->getPersonagem(getSaveSelecionado().perfil.personagem);
		if(mesh_info!=NULL)
		{
			if(JanelaEscolhaPerfil::personagem==NULL)
			{
				JanelaEscolhaPerfil::personagem = new Imagem(Vetor(10,10),mesh_info->img);
				JanelaEscolhaPerfil::componentes.push_back(JanelaEscolhaPerfil::personagem );
			}
			else
			{
				JanelaEscolhaPerfil::personagem->atualizaImagem(mesh_info->img);
			}
		}
	}
}
void JanelaEscolhaPerfil::setupComponentes3d()
{
	/*
	PersonagemDAO * dao = new PersonagemDAO();
	if(saves.size()>0){
		Mesh_Info * mesh_info = dao->getPersonagem(getSaveSelecionado().perfil.personagem);
		if(mesh_info!=NULL)
		{
			scene::IAnimatedMesh * mesh=SceneManager->getMesh(mesh_info->arquivo.c_str());
			float xFinal = tamanhoTela.x - tamanhoTela.x*0.4;
			float y = tamanhoTela.y;
			SceneManager->addCameraSceneNode(0,core::vector3df(30,0,23),core::vector3df(30,0,0));
			//SceneManager->addCameraSceneNodeFPS();
	
			if(mesh)
			{
				JanelaEscolhaPerfil::node = SceneManager->addAnimatedMeshSceneNode(mesh);
		
				JanelaEscolhaPerfil::node->setPosition(core::vector3df(30,0,-10));
				JanelaEscolhaPerfil::node->setMaterialFlag(EMF_LIGHTING, false);
				JanelaEscolhaPerfil::node->setMaterialFlag(video::EMF_FOG_ENABLE, true);
				//JanelaEscolhaPerfil::node->setMaterialTexture(1,SceneManager->getVideoDriver()->getTexture("modelos/personagem/boneco1/texture.png"));	
				JanelaEscolhaPerfil::node->setVisible(true);
				JanelaEscolhaPerfil::node->setScale(core::vector3df(mesh_info->escala.x,mesh_info->escala.y,mesh_info->escala.z));
				JanelaEscolhaPerfil::node->setRotation(core::vector3df(mesh_info->rotacao.x,mesh_info->rotacao.y,mesh_info->rotacao.z));


			}
		}
	}
	*/
}



void JanelaEscolhaPerfil::excluirPerfil () {
	PerfilDao * dao = new PerfilDao();
	JanelaEscolhaPerfil::saves = dao->carregarPerfis();
	if (saves.size() > 0) { // Existem perfis a serem excluidos
		dao->excluirPerfil(getPerfilSelecionado());
		indiceSave = 0;
		JanelaEscolhaPerfil::saves = dao->carregarPerfis(); // carregando novamente os perfis
		exibirMensagemSimples("Perfil excluido com sucesso !",new CLicouSimCaixaExcluirListener(this));
		// Falta atualizar a janela
		carregaValoresSave();
	}


}