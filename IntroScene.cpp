#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Janelas.h"


#include "MouseSensor.h"

static time_t milisInicio=0;
static time_t milisFim=0;
int imagem;

bool ativo;

Imagem * logo_open_ni;
Imagem * logo_irrlich;
Imagem * logo_ucb;

scene::ISceneNode* parent_; 
scene::ISceneManager* mgr_;


IntroScene::IntroScene(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id):Janela(parent, mgr, id)
{
	parent_ = parent;
	mgr_	= mgr;

	imagem	= 1;
	ativo	= true;

	logo_ucb	 = new Imagem(Vetor(),"media/logo/ucb-logo.jpg");
	logo_irrlich = new Imagem(Vetor(),"media/logo/irrlich-logo.jpg");
	logo_open_ni = new Imagem(Vetor(),"media/logo/openni-logo.png");
}


IntroScene::~IntroScene(void)
{
}






void IntroScene::desenhar()
{
if(milisInicio==0){
		printf("entrou aqui nesse if - ");
		milisInicio=time(NULL);
	}
	milisFim=time(NULL);
	if(difftime(milisFim,milisInicio)>= 1){
		imagem++;
		if(imagem>3){
			//scene::ISceneManager* smg = MouseSensor::d->getSceneManager();
				
			GerenciadorDeExibicao::getGerenciador()->novaJanelaParaExibicao(new JanelaPrincipal(parent_,  mgr_, 11));
			ativo=false;
		}
		milisInicio=time(NULL);
	}
	//printf("entrou aqui-dif= %lf\n",difftime(milisFim,milisInicio));
	//getchar();
	Imagem * mostrar;
	if(imagem==1)
		mostrar = logo_irrlich;
	else if(imagem==2)
		mostrar = logo_open_ni;
	else 
		mostrar = logo_ucb;
	
	mostrar->setVisivel(true);
	mostrar->desenhar(SceneManager->getVideoDriver());
	
	logo_irrlich->setVisivel(false);
	logo_ucb->setVisivel(false);
	logo_open_ni->setVisivel(false);

	

}

bool  IntroScene::emExecucao()
{
	if(!ativo)
		IsVisible=false;
	return ativo;
}