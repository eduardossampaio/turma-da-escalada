#include "stdafx.h"
#include "ComponenteInformacoesJogador.h"
#include "Conversoes.h"
#include "JanelaLoja2.h"

ComponenteInformacoesJogador::ComponenteInformacoesJogador(Vetor posicao,Vetor tamanho,Jogador * jogador,JanelaLoja2 *loja):Componente(posicao),tamanho(tamanho),jogador(jogador),loja(loja)
{
	alinhou = false;
	//moedas
	areaMoedas.v1 = posicao;
	areaMoedas.v2 = Vetor(tamanho.x ,tamanho.y*0.3 );
			
	//mochila
	areaMochila.v1 = Vetor(posicao.x,areaMoedas.v2.y);
	areaMochila.v2 = Vetor(tamanho.x,areaMochila.v1.y + tamanho.y*0.4);

	//botao
	areaBotaoSair.v1 = Vetor(posicao.x,areaMochila.v2.y);
	areaBotaoSair.v2 = Vetor(tamanho.x,areaBotaoSair.v1.y+tamanho.y*0.3);

	//botao vender

			
	//imagem da moeda
	moedaImagem = new Imagem(areaMoedas.v1,"ui/icone/moeda.jpg");
	labelMoeda = new Label(
		areaMoedas.v1,
		Vetor(areaMoedas.v2.x - areaMoedas.v1.x,areaMoedas.v2.y,areaMoedas.v1.y),
		"0000",
		"comic",
		TAMANHO::MEDIO,
		true,
		true);
	
	//imagem da mochila
	mochilaImagem = new Imagem(areaMochila.v1,"ui/icone/mochila.jpg");
	labelMochila  = new Label(
		areaMochila.v1,
		Vetor(areaMochila.v2.x - areaMochila.v1.x,areaMochila.v2.y - areaMochila.v1.y),
		"1111",
		"comic",
		TAMANHO::MEDIO,
		true,
		true); 
			
	//botao sair
	areaBotaoSair.v1.x * 0.2;
	
	botaoSair = new Botao(areaBotaoSair.v1,"ui/botoes/em-branco-pequeno.png","Sair","comic",TAMANHO::MEDIO);
	botaoVender = new Botao(areaBotaoSair.v1,"ui/botoes/em-branco-pequeno.png","Vender","comic",TAMANHO::MEDIO);

	botaoSair->addListener(new ComponenteInformacoesJogador::VoltarListener());
	botaoVender->addListener(new ComponenteInformacoesJogador::VenderListener(jogador,loja));

	loja->adicionarListener(botaoSair);
	loja->adicionarListener(botaoVender);
}
ComponenteInformacoesJogador::~ComponenteInformacoesJogador(void)
{
}


void ComponenteInformacoesJogador::desenhar(IVideoDriver * driver) 
{
			
	//area das moedas
	driver->draw2DRectangle(
		video::SColor(255,245,245,245),
		core::rect<s32>(areaMoedas.v1.x,areaMoedas.v1.y,areaMoedas.v2.x,areaMoedas.v2.y));
			
	//area das mochilas
	driver->draw2DRectangle(
		video::SColor(255,245,245,245),
		core::rect<s32>(areaMochila.v1.x,areaMochila.v1.y,areaMochila.v2.x,areaMochila.v2.y));
	//area do botao
	driver->draw2DRectangle(
		video::SColor(255,245,245,245),
		core::rect<s32>(areaBotaoSair.v1.x,areaBotaoSair.v1.y,areaBotaoSair.v2.x,areaBotaoSair.v2.y));
			
			

	//desenha moeda
	moedaImagem->desenhar(driver);
	labelMoeda->desenhar(driver);

	//desenha a mochila
	mochilaImagem->desenhar(driver);
	labelMochila->desenhar(driver);

	//desenha o botao
	botaoSair->desenhar(driver);
	botaoVender->desenhar(driver);

//			alinhou = true;
	if(!alinhou)
	{
		alinhou = true;
		int margemXImagens = 15;
		//alinha moeda
		Vetor tamanhoMoeda = moedaImagem->getTamanho();
		float diffYMoeda = (areaMoedas.v2.y - areaMoedas.v1.y - tamanhoMoeda.y )/2;
		moedaImagem->atualizarPosisao(Vetor (moedaImagem->getPosisao().x+margemXImagens, moedaImagem->getPosisao().y + diffYMoeda) );

		//alinha mochila
		Vetor tamanhoMochila = mochilaImagem->getTamanho();
		float diffYMochila = (areaMochila.v2.y - areaMochila.v1.y - tamanhoMochila.y )/2;
		mochilaImagem->atualizarPosisao(Vetor (mochilaImagem->getPosisao().x+margemXImagens, mochilaImagem->getPosisao().y + diffYMochila) );

		//alinha botao
		Vetor tamanhoBotao = botaoSair->getTamanho();
		float diffYbotao = (areaBotaoSair.v2.y - areaBotaoSair.v1.y - tamanhoBotao.y )/2;
		float diffXbotao = (areaBotaoSair.v2.x - areaBotaoSair.v1.x - tamanhoBotao.x )/2;
		botaoSair->atualizarPosisao(Vetor (botaoSair->getPosisao().x+diffXbotao*1.8, botaoSair->getPosisao().y + diffYbotao) );
		botaoSair->addListener(new VenderListener(jogador,loja));

		// alinha botao vender
		Vetor tamanhoBotaoVender = botaoVender->getTamanho();
		float diffYbotaoVender = (areaBotaoSair.v2.y - areaBotaoSair.v1.y - tamanhoBotaoVender.y )/2;
		float diffXbotaoVender = (areaBotaoSair.v2.x - areaBotaoSair.v1.x - tamanhoBotaoVender.x )/2;
		botaoVender->atualizarPosisao(Vetor (botaoVender->getPosisao().x+diffXbotaoVender*0.2, botaoVender->getPosisao().y + diffYbotaoVender) );
		
		//botaoVender->addListener(new SalvarPerfilListener(jogador));
	}
	atualizarDados();
}


void ComponenteInformacoesJogador::atualizarDados()
{
	labelMoeda->setTexto(Conversoes::converteParaString(jogador->getInventario()->getDinheiro()));
	labelMochila->setTexto(Conversoes::converteParaString(jogador->getInventario()->getPesoTotalItens()));
}
Botao * ComponenteInformacoesJogador::getBotaoSair()
{
	return botaoSair;
}

Botao * ComponenteInformacoesJogador::getBotaoVender()
{
	return botaoVender;
}