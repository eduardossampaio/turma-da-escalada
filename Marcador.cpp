#include "stdafx.h"
#include "Marcador.h"
#include "CalculosUteis.h"
#include "Configuracoes.h"
#include "Label.h"
#include "FaseDAO.h"
#define MARGEM 5
Marcador::Marcador(Vetor pos,ISceneManager * mgr,Jogador * jogador,JanelaEscolhaFase * janela) :Componente(pos),jogador(jogador)
{
	//Marcador::posIcone.x = pos.x * 6;
	//Marcador::posIcone.y = pos.y;
	//Marcador::posIcone.z = pos.z;
	Marcador::icone = new Imagem(pos, "ui/icone/marcador.jpg");
	Marcador::emCima = false;
	Marcador::aberta = false;
	Marcador::config = (new Configuracoes())->carregarConfigucacoes();

	inicioCaixa.x = Marcador::posicao.x + MARGEM + Marcador::icone->getTamanho().x;
	inicioCaixa.y = Marcador::posicao.y;
	fimCaixa.x = config.resolucao.x* 0.4;
	fimCaixa.y = config.resolucao.y* 0.6;

	Marcador::info.local = "Monte Roraima";
	Marcador::info.coordenadas = Vetor(100, 200);

	Marcador::info.descricao = "Pais: Fronteira da Venezuela, Brasil e Guiana";
	Marcador::info.infoFauna = " Fauna: Mamiferos carnivoros, roedores \n Ex: furao, tamandua-bandeira, capivara";
	Marcador::info.infoFlora = "\n Flora: Floresta tropical com plantas de \n coloracao negra, plantas carnivoras e arvores \n";
	FaseDAO * dao = new FaseDAO();
	Marcador::info.dados	=	dao->getFase("fases/parede.xml");
	
	//cria labels
	//tamanho das caixas.
	Vetor tamanho = Vetor(50, 10);
	Marcador::nomeFase = new Label(Vetor(), tamanho, info.local, "comic", TAMANHO::PEQUENO, true, true);
	Marcador::informacoes = new Label(Vetor(), tamanho, info.descricao, "comic", TAMANHO::PEQUENO, true, true);
	Marcador::localizacaoLabel = new Label(Vetor(), tamanho, "Altitude: 2.810m ", "comic", TAMANHO::PEQUENO, true, true);
	Marcador::localizacaoTexto = new Label(Vetor(), tamanho, " Tempertura Media: 20C", "comic", TAMANHO::PEQUENO, true, true);
	Marcador::fauna = new Label(Vetor(), tamanho, info.infoFauna, "comic", TAMANHO::PEQUENO, true, true);
	Marcador::flora = new Label(Vetor(), tamanho, info.infoFlora, "comic", TAMANHO::PEQUENO, true, true);
	Marcador::botao = new Botao(Vetor(inicioCaixa.x * 6, inicioCaixa.y + fimCaixa.y * 0.8), "ui/botoes/em-branco-pequeno.png", "jogar", "comic", TAMANHO::PEQUENO);

	Marcador::botao->addListener(new Marcador::BotaoJogarListener(mgr,Marcador::info.dados,jogador,janela));

	//Localizacao
	//Fronteira do Brasil, Venezuela e Guiana
	//Monte Roraima
}


Marcador::~Marcador(void)
{
}

void Marcador::desenhar(IVideoDriver * driver)
{
	//icone->atualizarPosisao(Marcador::posIcone);
	Marcador::icone->desenhar(driver);

	if (aberta)
	{


		inicioCaixa.x = Marcador::posicao.x + MARGEM + Marcador::icone->getTamanho().x;
		inicioCaixa.y = Marcador::posicao.y;
		fimCaixa.x = config.resolucao.x* 0.8;
		fimCaixa.y = config.resolucao.y* 0.6;

		irr::video::SColor cor = irr::video::SColor(255, 221, 221, 211); // cinza claro

		driver->draw2DRectangle(cor, core::rect<s32>(inicioCaixa.x, inicioCaixa.y, fimCaixa.x, fimCaixa.y));

		//nome da fase
		nomeFase->atualizarPosisao(inicioCaixa);
		nomeFase->setTamanho(tipos::Vetor(fimCaixa.x - inicioCaixa.x, fimCaixa.y*0.1)); // tamanho do quadradinho
		//nomeFase->setTamanho(tipos::Vetor(200,300)); 

		//nomeFase->setTamanhoFonte(TAMANHO::MEDIO);
		//texto 'localizacao'
		localizacaoLabel->atualizarPosisao(Vetor(inicioCaixa.x, inicioCaixa.y + fimCaixa.y * 0.1));
		localizacaoLabel->setTamanho(Vetor((fimCaixa.x - inicioCaixa.x) / 2, fimCaixa.y*0.1));

		//localizacao(coordenadas)
		localizacaoTexto->atualizarPosisao(Vetor(inicioCaixa.x + (fimCaixa.x - inicioCaixa.x) / 2, inicioCaixa.y + fimCaixa.y * 0.1));
		localizacaoTexto->setTamanho(Vetor((fimCaixa.x - inicioCaixa.x) / 2, fimCaixa.y*0.1));

		//informacoes da fase
		informacoes->atualizarPosisao(Vetor(inicioCaixa.x, inicioCaixa.y + fimCaixa.y * 0.2));
		informacoes->setTamanho(Vetor((fimCaixa.x - inicioCaixa.x), fimCaixa.y*0.2));

		//informacoes da fauna
		fauna->atualizarPosisao(Vetor(inicioCaixa.x, inicioCaixa.y + fimCaixa.y * 0.4));
		fauna->setTamanho(Vetor((fimCaixa.x - inicioCaixa.x), fimCaixa.y*0.2));

		//informacoes da flora
		flora->atualizarPosisao(Vetor(inicioCaixa.x, inicioCaixa.y + fimCaixa.y * 0.6));
		flora->setTamanho(Vetor((fimCaixa.x - inicioCaixa.x), fimCaixa.y*0.2));

		//botão


		/*--------------------------------------------------------*/
		nomeFase->desenhar(driver);
		localizacaoLabel->desenhar(driver);
		localizacaoTexto->desenhar(driver);
		informacoes->desenhar(driver);
		fauna->desenhar(driver);
		flora->desenhar(driver);
		botao->desenhar(driver);
	}

}

void Marcador::onClique(Vetor pos)
{
	botao->onClique(pos);
}
void Marcador::posicaoCaptada(Vetor pos)
{


	Vetor inicioIcone = Marcador::posicao;
	Vetor fimIcone = CalculosUteis::somarAtributosVetor(Marcador::posicao, Marcador::icone->getTamanho());

	Vetor inicioCaixaTemp = inicioCaixa;
	Vetor fimCaixaTemp = fimCaixa;
	inicioCaixaTemp.x -= MARGEM + Marcador::posicao.x;

	//bool emCimaCaixa=false;
	emCima = false;
	//em cima do incone
	if (CalculosUteis::pontoDentroDeArea(pos, inicioIcone, fimIcone))
	{
		emCima = true;
		aberta = true;
	}
	//em cima da caixa
	else if (CalculosUteis::pontoDentroDeArea(pos, inicioCaixaTemp, fimCaixaTemp) && aberta)
	{
		//emCimaCaixa=true;
	}
	else{
		emCima = false;
		aberta = false;
	}

	//aberta = emCima || aberta && emCimaCaixa;

}