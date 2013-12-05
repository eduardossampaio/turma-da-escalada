#include "stdafx.h"

#include "JanelaLoja2.h"
#include "Configuracoes.h"
#include "ItemDAO.h"
#include "CaixaVendaItem.h"
#include "CaixaMensagemSimNao.h"
#include "ComponenteInformacoesJogador.h"
#define QTD_LINHA  3
#define QTD_COLUNA 3

JanelaLoja2::JanelaLoja2(Jogador * jogador,scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id) : Janela(parent,mgr,id),jogador(jogador)
{
	

	Configuracoes * configuracoes = new Configuracoes();	
	tipos::configuracoes config = configuracoes->carregarConfigucacoes();
	
	//cursor
	JanelaLoja2::cursor = new KinectCursor();
	
	//imagem grande para exibicao do icone
	JanelaLoja2::alinhouImagem = false;
	JanelaLoja2::alinhouBotoes = false;
	
	//no comeco não tem item selecionado,não exibe imagem
	JanelaLoja2::imagemSelecionado = new Imagem("");
	JanelaLoja2::imagemSelecionado->setVisivel(false);
	componentes.push_back(imagemSelecionado);
	

	//area das informações do item
	areaDadosItem.v1 = Vetor(0,config.resolucao.y/2); // quadrado representa a area da imagem (grande)
	areaDadosItem.v2 = Vetor(config.resolucao.x*0.4,config.resolucao.y); // quadrado representa descricao do item

	//Componente para item selecionado
	JanelaLoja2::itemSelecionado = new ComponenteItemLojaSelecionado(this,areaDadosItem.v1,areaDadosItem.v2);
	
	JanelaLoja2::componentes.push_back(itemSelecionado);
	cursor->adicionarListener(itemSelecionado);

	//coordenadas da area onde será exibida a imagem grande do item
	JanelaLoja2::inicioAreaImagem = Vetor(0,0);
	JanelaLoja2::fimAreaImagem    = Vetor(config.resolucao.x*0.4,config.resolucao.y/2);


	//area dos dados do jogador
	areaDadosJogador.v1 = Vetor(config.resolucao.x*0.4,0);
	areaDadosJogador.v2 = Vetor(config.resolucao.x,config.resolucao.y/2);
	JanelaLoja2::informacoesJogador = new ComponenteInformacoesJogador(areaDadosJogador.v1,areaDadosJogador.v2,jogador,this);
	componentes.push_back(JanelaLoja2::informacoesJogador);
	cursor->adicionarListener( JanelaLoja2::informacoesJogador->getBotaoSair() );

	//coordenadas da area onde são exibidos os icones	
	//Vetor inicioAreaItensLoja = Vetor(config.resolucao.x*0.1,config.resolucao.y/2);
	//Vetor finalAreaItensLoja  = Vetor(config.resolucao.x - config.resolucao.x*0.1,config.resolucao.y);

	tipos::Area areaItensLoja;
	//areaItensLoja.v1 = Vetor(config.resolucao.x*0.1,config.resolucao.y/2); //antigo
	//areaItensLoja.v2 = Vetor(config.resolucao.x - config.resolucao.x*0.1,config.resolucao.y);//antigo	
	areaItensLoja.v1 = Vetor(config.resolucao.x*0.5,config.resolucao.y/2);
	areaItensLoja.v2 = Vetor(config.resolucao.x - config.resolucao.x*0.1,config.resolucao.y);


	//area do botão da esquerda
	JanelaLoja2::area_botao_voltar.v1 = Vetor(config.resolucao.x*0.4,config.resolucao.y/2);
	JanelaLoja2::area_botao_voltar.v2 = Vetor(config.resolucao.x*0.1,config.resolucao.y);

	//area do botão da direita
	JanelaLoja2::area_botao_proximo.v1 = Vetor(config.resolucao.x - config.resolucao.x*0.1,config.resolucao.y/2);
	JanelaLoja2::area_botao_proximo.v2 = Vetor(config.resolucao.x,config.resolucao.y);

	//botoões de navegacao
	JanelaLoja2::botaoProximo  = new Botao(area_botao_proximo.v1,"ui/botoes/proximo_item_pequeno.png");
	JanelaLoja2::botaoAnterior = new Botao(area_botao_voltar.v1,"ui/botoes/item_anterior_pequeno.png");
	
	componentes.push_back(botaoAnterior);
	componentes.push_back(botaoProximo);

	botaoProximo->addListener(new BotaoProximoItemListener(this));
	botaoAnterior->addListener(new BotaoItemAnteriorListener(this));
	
	
	cursor->adicionarListener(botaoProximo);
	cursor->adicionarListener(botaoAnterior);

	
	//itens para serem exibidos na loja
	ItemDAO * dao = new ItemDAO();
	vector<Item_loja> itens  = dao->getItens();

	//pega os indices de comeco e fim dos itens
	JanelaLoja2::itens_inicio = 0;
	JanelaLoja2::itens_fim	  = itens.size()>=QTD_LINHA * QTD_COLUNA ? QTD_LINHA * QTD_COLUNA : itens.size();
	
	//obtem as coordenadas de cada icone
	JanelaLoja2::coordenadasIcones = obterCoordenadasIcones(areaItensLoja.v1,areaItensLoja.v2);

	//seta os icones vazios 
	for(int i=0;i< QTD_LINHA * QTD_COLUNA ;i++)
	{
		
		ComponenteItemLojaIconeVazio * icone_vazio = 
							new ComponenteItemLojaIconeVazio(
								JanelaLoja2::coordenadasIcones[i],
								Vetor(
										(areaItensLoja.v2.x - areaItensLoja.v1.x) / QTD_COLUNA ,
										(areaItensLoja.v2.y - areaItensLoja.v1.y) / QTD_LINHA )
							);
		
		icone_vazio->habilitar(false);
		
		JanelaLoja2::icones_vazios.push_back(icone_vazio);
		
		componentes.push_back(icone_vazio);
		
		
	}
	//seta os icones itens
	for(int i=0,index_coord = 0 ;i<itens.size();i++,index_coord++)
	{

		if(index_coord == QTD_LINHA * QTD_COLUNA )
			index_coord = 0;

		//JanelaLoja2 * janela,Vetor pos,tipos::Item_Loja item
		ComponenteItemLojaIcone * icone = new
			ComponenteItemLojaIcone(
									this,
									JanelaLoja2::coordenadasIcones[index_coord],
									Vetor(
										(areaItensLoja.v2.x - areaItensLoja.v1.x) / QTD_COLUNA ,
										(areaItensLoja.v2.y - areaItensLoja.v1.y) / QTD_LINHA ),
									itens[i]);
		
		
		icone->habilitar(false);
		
		icones_itens.push_back(icone);
		
		componentes.push_back(icone);

		cursor->adicionarListener(icone);
		
	
	}
	JanelaLoja2::selecionarItensParaExibicao();
	
}


JanelaLoja2::~JanelaLoja2(void)
{
}

void JanelaLoja2::desenhar()
{

	//para teste
	//desenha area do botao da esquerda
	SceneManager->getVideoDriver()->draw2DRectangle(
		SColor(255,245,245,245),
		core::rect<s32>(
			JanelaLoja2::area_botao_voltar.v1.x,
			JanelaLoja2::area_botao_voltar.v1.y,
			JanelaLoja2::area_botao_voltar.v1.x + JanelaLoja2::area_botao_voltar.v2.x,
			JanelaLoja2::area_botao_voltar.v1.y + JanelaLoja2::area_botao_voltar.v2.y
			));
	
	//desenha area do botao da direita
	SceneManager->getVideoDriver()->draw2DRectangle(
		SColor(255,245,245,245),
		core::rect<s32>(
			JanelaLoja2::area_botao_proximo.v1.x,
			JanelaLoja2::area_botao_proximo.v1.y,
			JanelaLoja2::area_botao_proximo.v1.x + JanelaLoja2::area_botao_proximo.v2.x,
			JanelaLoja2::area_botao_proximo.v1.y + JanelaLoja2::area_botao_proximo.v2.y
			));


	//for(int i=0;i<componentes.size();i++)
//		componentes[i]->desenhar(SceneManager->getVideoDriver());
	desenharComponentes();
	cursor->desenhar(SceneManager->getVideoDriver());
	//temp 
	//area da imagem
	// Retirado linha de marcacao. 
	/* 
	SceneManager->getVideoDriver()->draw2DLine(
		core::vector2d<irr::s32>(inicioAreaImagem.x,inicioAreaImagem.y),
		core::vector2d<irr::s32>(fimAreaImagem.x,fimAreaImagem.y) );
	*/

	
	

	//centralizar a imagem
	if(!alinhouImagem)
	{
		alinhouImagem = true;
		Vetor tam_img = imagemSelecionado->getTamanho();
		//Vetor pos_img = imagemSelecionado->getPosisao();
		Vetor centro = Vetor( (fimAreaImagem.x - inicioAreaImagem.x) /2  ,(fimAreaImagem.y - inicioAreaImagem.y)/2 );
		imagemSelecionado->atualizarPosisao(Vetor(centro.x-(tam_img.x/2),(centro.y-(tam_img.y/2))));
		
		//imagemSelecionado->atualizarPosisao(Vetor(pos_img.x + ( (area.x - tam_img.x)/2 ) , pos_img.y + ( (area.y - tam_img.y)/2 ) ));
	}

	if(!alinhouBotoes)
	{
		alinhouBotoes = true;
		
		Vetor tamanho_botao_voltar = JanelaLoja2::botaoAnterior->getTamanho();
		Vetor posicao_botao_voltar = JanelaLoja2::botaoAnterior->getPosisao();
		
		JanelaLoja2::botaoAnterior->atualizarPosisao(
			Vetor(
			posicao_botao_voltar.x + (JanelaLoja2::area_botao_voltar.v2.x  - tamanho_botao_voltar.x)/2,
			posicao_botao_voltar.y + (JanelaLoja2::area_botao_voltar.v2.y  - JanelaLoja2::area_botao_voltar.v1.y - tamanho_botao_voltar.y)/2
		));
		
		Vetor tamanho_botao_proximo = JanelaLoja2::botaoProximo->getTamanho();
		Vetor posicao_botao_proximo = JanelaLoja2::botaoProximo->getPosisao();
		JanelaLoja2::botaoProximo->atualizarPosisao(
			Vetor(
			posicao_botao_proximo.x + (JanelaLoja2::area_botao_proximo.v2.x  - JanelaLoja2::area_botao_proximo.v1.x - tamanho_botao_proximo.x)/2,
			posicao_botao_proximo.y + (JanelaLoja2::area_botao_proximo.v2.y  - JanelaLoja2::area_botao_proximo.v1.y - tamanho_botao_proximo.y)/2
		));
			

	}
	
	selecionarItensParaExibicao();
		
}

void JanelaLoja2::setItemSelecionado(tipos::Item_loja item)
{
	JanelaLoja2::itemSelecionado->setItemSelecionado(item);
	JanelaLoja2::itemSelecionado->atualizaItemSelecionado();
	
	//força realinhar as imagens
	JanelaLoja2::alinhouImagem = false;
	JanelaLoja2::imagemSelecionado->atualizaImagem(item.caminhoG); // alterado para ler a imagem grande.
	JanelaLoja2::imagemSelecionado->setVisivel(true);
}
	
void JanelaLoja2::comprarItem(tipos::Item_loja item,int qtd)
{
	
	jogador->comprarItem(item,qtd);
	PerfilDao * dao = new PerfilDao();
	dao->atualizarPerfil(jogador->getSave());
}
void JanelaLoja2::venderItem(tipos::Item_loja item,int qtd)
{
	jogador->venderItem(item,qtd);
	PerfilDao * dao = new PerfilDao();
	dao->atualizarPerfil(jogador->getSave());
}

//obtem as coordenadas de cada icone da janela para ser exibido
vector<Vetor> JanelaLoja2::obterCoordenadasIcones(Vetor inicio,Vetor fim)
{
	vector<Vetor> posicoes;
	
	for(int i = 0 ;i <QTD_LINHA ; i++)
	{
	
		for(int j = 0; j < QTD_COLUNA ; j++)
		{
			posicoes.push_back(
					Vetor(
							(inicio.x + (fim.x - inicio.x) / QTD_COLUNA * j ),
							(inicio.y + (fim.y - inicio.y) / QTD_LINHA  * i) 
						)
						//,Vetor((fim.x - inicio.x) / QTD_COLUNA ),(fim.y - inicio.y) / QTD_LINHA ) )
			);
		}
	
	}
	
	return posicoes;

}
void JanelaLoja2::adicionarListener(CliqueListener * listener)
{
	cursor->adicionarListener(listener);
}
void JanelaLoja2::selecionarItensParaExibicao()
{
	
	//coloca todos os icones invisiveis
	for(int i=0;i<icones_itens.size();i++)
		JanelaLoja2::icones_itens[i]->habilitar(false);
	
	//coloca todos os icones vazios invisiveis
	for(int i=0;i<icones_vazios.size();i++)
		icones_vazios[i]->habilitar(false);
	
	
	//coloca os itens selecionados visiveis
	for(int i = itens_inicio; i <itens_fim ; i++)
	{	
		JanelaLoja2::icones_itens[i]->habilitar(true);
	}
	
	//coloca os itens vazios restantes  visiveis
	for(int i= itens_fim - itens_inicio ; i<QTD_COLUNA * QTD_LINHA ;i++)
	{
		JanelaLoja2::icones_vazios[i]->habilitar(true);
	}
	
}

void JanelaLoja2::proximoPaginaItens()
{
	printf("mudando as paginas dos itens==>\n");
	if (itens_inicio + (QTD_COLUNA * QTD_LINHA) < icones_itens.size())
	{
		itens_inicio += (QTD_COLUNA * QTD_LINHA);
		itens_fim += (QTD_COLUNA * QTD_LINHA);
		if(itens_fim>icones_itens.size())
			itens_fim=icones_itens.size();
	}
}
void JanelaLoja2::paginaAnteriorItens()
{
	printf("<==mudando as paginas dos itens\n");
	if(itens_inicio - (QTD_COLUNA*QTD_LINHA) >= 0 )
	{
		itens_inicio-= (QTD_COLUNA*QTD_LINHA) ;
		itens_fim = itens_inicio +  (QTD_COLUNA*QTD_LINHA) ;

	}
}

tipos::Item_loja JanelaLoja2::getItemSelecionado()
{
	return JanelaLoja2::itemSelecionado->getItem();
}
int JanelaLoja2::getQuatidadeItem()
{
	return JanelaLoja2::itemSelecionado->getQuantidade();
}

void JanelaLoja2::solicitaVendaPerfil()
{
	printf("perguntando quantos quer vender\n");
	tipos::Item_loja item = JanelaLoja2::itemSelecionado->getItem();
	if(jogador->podeVenderItem(item))
	{
		Vetor tamanho = Vetor(700,280);
		Configuracoes * config = new Configuracoes();
		tipos::configuracoes c = config->carregarConfigucacoes();
		int x = (c.resolucao.x - tamanho.x) /2;
		int y = (c.resolucao.y - tamanho.y) /2;
		int maximo = jogador->getInventario()->quatidadeItem(item);
		CaixaVendaItem * vendaItem = new CaixaVendaItem(Vetor(30,30),tamanho,"Deseja vender "+item.nome+" ?",NULL,NULL,maximo);
		CliqueListener * l = new VenderItemListener(this,vendaItem);
		vendaItem->setListenerVender(l);
		exibirMensagem(vendaItem);
	}
	else
	{
		exibirMensagemErro("voce nao possui este item");
	}
	
	
}

void JanelaLoja2::solicitaCompraItem(tipos::Item_loja item,int qtd)
{
	printf("pede pra comprar\n");
	if(jogador->podeComprarItem(item,qtd))
	{
			Configuracoes *c = new Configuracoes();
			tipos::configuracoes config = c->carregarConfigucacoes();
			int x1 = config.resolucao.x / 5;
			int y1 = config.resolucao.y / 3;
			int x2 = config.resolucao.x - (x1*2);
			int y2 = config.resolucao.y - (y1*2); 
			CaixaMensagemSimNao * caixa = new CaixaMensagemSimNao(
				Vetor(x1,y1),
				Vetor(x2,y2),
				"Deseja comprar este item? "				
				,new BotaoComprarListener(this)
				);
			exibirMensagem(caixa);
	}
	else
	{
		exibirMensagemSimples("voce nao possui dinheiro\npra comprar este item");
	}
}