#include "stdafx.h"
#include "Janela.h"
#include "dao.h"
using namespace irr;

core::aabbox3d<f32> Box;
video::SMaterial Material;

scene::ISceneManager * Janela::manager;

Janela::Janela(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id):ISceneNode(parent,mgr,id)
{
	IsVisible = false;
	
	Janela::manager= mgr;
	Janela::cursor = NULL;

}





Janela::~Janela(void)
{
}

void Janela::retirarFocoComponentes()
{
	for(int i=0;i<componentes.size();i++)
		componentes[i]->desativarFoco();
	if(Janela::cursor)
	{
		vector<CliqueListener *> listeners = Janela::cursor->getListeners();
		for(int i=0;i<listeners.size();i++)
			listeners[i]->desativarFoco();
	}
}
void Janela::adicioarFocoComponentes()
{
	for(int i=0;i<componentes.size();i++)
		componentes[i]->ativarFoco();
	if(Janela::cursor)
	{
		vector<CliqueListener *> listeners = Janela::cursor->getListeners();
		for(int i=0;i<listeners.size();i++)
			listeners[i]->ativarFoco();
	}
}
const core::aabbox3d<f32>& Janela::getBoundingBox() const
{
		return Box;
}

u32 Janela::getMaterialCount() const
{
		return 1;
}

video::SMaterial& Janela::getMaterial(u32 i)
{
	return (video::SMaterial) Material;
}	

void Janela::render()
{
//	if(Janela::cursor!=NULL)
	//	Janela::cursor->atualizar();
	//if(IsVisible)
		desenhar();
	


}

void Janela::OnRegisterSceneNode()
{
		
	if (IsVisible)
		SceneManager->registerNodeForRendering(this,irr::scene::E_SCENE_NODE_RENDER_PASS::ESNRP_TRANSPARENT_EFFECT);
	ISceneNode::OnRegisterSceneNode();
	
	
}

void Janela::desenharComponentes()
{
	if(Janela::cursor!=NULL)
		Janela::cursor->atualizar();
	//desenha primeiro os componentes que não tem foco
	for(int i=0;i<componentes.size();i++)
	{
		if(!componentes[i]->temFoco() /*&& componentes[i]->habilitado() */)
			componentes[i]->desenhar(SceneManager->getVideoDriver());
	}
	//desenha os componentes que tem foco depois,para eles 
	//aparecerem na frente dos que não tem foco
	for(int i=0;i<componentes.size();i++)
	{
		if(componentes[i]->temFoco() /*&& componentes[i]->habilitado() */)
			componentes[i]->desenhar(SceneManager->getVideoDriver());
	}
}

void Janela::remover()
{
	IsVisible = false;
	
	//remove();
}


void Janela::exibirMensagemSimples(std::string msg,CliqueListener * list )
{
	caixaMensagemSimples = NULL;
	exibirMensagem(msg,tipoMensagem::NORMAL);
	if(list)
		caixaMensagemSimples->setListenerFechar(list);
	

}

void Janela::exibirMensagem(std::string msg,tipoMensagem tipo)
{
	if(caixaMensagemSimples==NULL)
	{

		Configuracoes * dao = new Configuracoes();
		tipos::configuracoes config = dao->carregarConfigucacoes();
		
		int x1 = config.resolucao.x / 5;
		int y1 = config.resolucao.y / 3;
		int x2 = config.resolucao.x - (x1*2);
		int y2 = config.resolucao.y - (y1*2); 
		caixaMensagemSimples = new CaixaMensagemSimple(Vetor(x1,y1),Vetor(x2,y2),msg,tipo);
		
		componentes.push_back(caixaMensagemSimples);
		if(cursor)
		{
			
			caixaMensagemSimples->setListenerFechar(new Janela::fecharCaixaMensagemListener(caixaMensagemSimples,this));
			cursor->adicionarListener(caixaMensagemSimples);
		}
	}
	caixaMensagemSimples->habilitar(true);	
	
	retirarFocoComponentes();
	caixaMensagemSimples->ativar();

}

void Janela::exibirMensagem(CaixaMensagem * caixa)
{
	if(caixa!=NULL)
	{

		
		//caixaMensagemSimples = new CaixaMensagemSimple(Vetor(x1,y1),Vetor(x2,y2),msg,tipo);
		
		componentes.push_back(caixa);
		if(cursor)
		{
			
			caixa->setListenerFechar(new Janela::fecharCaixaMensagemListener(caixa,this));
			cursor->adicionarListener(caixa);

		}
		caixa->habilitar(true);
		retirarFocoComponentes();
		caixa->ativar();
	}
	//caixaMensagemSimples->habilitar(true);	
}
void Janela::exibirMensagemErro(std::string msg,CliqueListener * list)
{
	caixaMensagemSimples = NULL;
	exibirMensagem(msg,tipoMensagem::ERRO);
	if(list)
		caixaMensagemSimples->setListenerFechar(list);
}
void Janela::exibirMensagemAlerta(std::string msg,CliqueListener * list)
{
	caixaMensagemSimples = NULL;
	exibirMensagem(msg,tipoMensagem::ALERTA);
}
void Janela::iniciar()
{
	IsVisible = true;
	Janela::OnRegisterSceneNode();
	
}

bool Janela::emExecucao()
{
	return IsVisible;

}

void Janela::removerComponente(Componente * componente)
{
	vector<Componente * > novo;
	for(int i=0;i<componentes.size();i++)
	{
		if(componentes[i]!=componente)
		{
			novo.push_back(componentes[i]);
		}
		else
		{
			printf("retirou\n");
		}
	}
	componentes = novo;
}