#include "stdafx.h"
#include "ComboBox.h"
#include "CalculosUteis.h"


ComboBox::ComboBox(Vetor posicao,Vetor tamanho):Componente(posicao)
{
	ComboBox::tamanho = Vetor(posicao.x+ tamanho.x,posicao.y+tamanho.y);
	ComboBox::comboAberta=false;
	ComboBox::font =  Globais::getIrrDevice()->getGUIEnvironment()->getFont("media/fontes/myfont.xml");
	ComboBox::tamanhoLabel = tamanho;
	ComboBox::texto   = new Label(posicao,tamanho,"","comic",TAMANHO::MEDIO,true,true);
}

// Metodo construtor sobreecarregado para a construcao da imagem
/* 
ComboBox::ComboBox(Vetor posicao,Vetor tamanho,string imagem):Componente(posicao)
{
	ComboBox::tamanho = Vetor(posicao.x+ tamanho.x,posicao.y+tamanho.y);
	ComboBox::comboAberta=false;
	ComboBox::font =  Globais::getIrrDevice()->getGUIEnvironment()->getFont("media/fontes/myfont.xml");
	ComboBox::imagem = new Imagem(posicao,imagem); 
	ComboBox::tamanhoLabel = ComboBox::imagem->getTamanho();
	ComboBox::texto   = new Label(posicao,tamanho,"","comic",TAMANHO::GRANDE,true,true);
*/

	/*
	Botao::habilidato = true;
	Botao::imagem = new Imagem( posicao,imagem);
	Botao::tamanho = Botao::imagem->getTamanho();
	Botao::comTexto = true;
	Botao::label = new Label(posicao,Botao::tamanho,texto,fonte,tamanho,true,true);
	*/

//}


ComboBox::~ComboBox(void)
{
}
void ComboBox::addItens(string itens,bool seleciona )
{
	ComboBox::itens.push_back(itens);
	if(seleciona)
		selecionaItem(ComboBox::itens.size()-1);
}
void ComboBox::desenhar(IVideoDriver * driver)
{
	driver->draw2DRectangle(
		video::SColor(255,206,206,206), // cor cinza claro
		core::rect<s32>(posicao.x,posicao.y,tamanho.x,tamanho.y));
	video::SColor cor		= video::SColor(255,206,206,206); // cor cinza claro	
	video::SColor corLetra  = video::SColor(255,0,0,0);	      // cor preto
	
	if(comboAberta){
		float diffY = abs(posicao.y - tamanho.y);
		for(int i=0;i<itens.size();i++){
							
			driver->draw2DRectangle(
				cor,
				core::rect<s32>(posicao.x ,posicao.y+(diffY*i),tamanho.x ,tamanho.y+(diffY*i)));
			
			ComboBox::texto->setTexto(itens[i].c_str());
			ComboBox::texto->atualizarPosisao(Vetor(posicao.x ,posicao.y+(diffY*i)));
			
			ComboBox::texto->setTamanho(ComboBox::tamanhoLabel);
			
			ComboBox::texto->desenhar(driver);
		}
	}else{
		//if(itemSelecionado ){
			//font->draw(itemSelecionado.c_str(),core::rect<s32>(posicao.x ,posicao.y,tamanho.x ,tamanho.y),corLetra,true,true);
		ComboBox::texto->setTexto(itemSelecionado.c_str());	
		ComboBox::texto->atualizarPosisao(posicao);
			
			ComboBox::texto->setTamanho(ComboBox::tamanhoLabel);
			
			ComboBox::texto->desenhar(driver);

		//}

	}
}

void ComboBox::selecionaItem(int indice)
{
	itemSelecionado = ComboBox::itens[indice];
}

string ComboBox::getItemSelecionado()
{
	return ComboBox::itemSelecionado;
}

void ComboBox::onClique(Vetor pos)
{
		if(!ComboBox::comboAberta){	
		if(CalculosUteis::pontoDentroDeArea(pos,ComboBox::posicao,ComboBox::tamanho)){
			ComboBox::comboAberta = true;
		}
	}else{
		if(cursorEmCimaComboAberta(pos))
		{
			printf("dentro\n");
		}else{
			printf("fora\n");
			ComboBox::comboAberta = false;
		}
	}

}

void ComboBox::selecionaItem(Vetor pos)
{
	Vetor posTemp = posicao;
	Vetor tamTemp = tamanho;
	if(cursorEmCimaComboAberta(pos)){
		printf("clicou em cima\n");		
		float diffY = (abs(posicao.y - tamanho.y)) * (itens.size() -1);
		for(int i=0;i<itens.size();i++){
			if(CalculosUteis::pontoDentroDeArea(pos,posTemp,tamTemp)){
				printf("clicou index %d\n",i);
				ComboBox::itemSelecionado = itens[i];
				printf("iten selecionado: %s\n",itemSelecionado.c_str());
				return;
			}
			posTemp.y += diffY;
			tamTemp.y += diffY;

		}
	}else{
		comboAberta=false;
	}
}
void ComboBox::posicaoCaptada(Vetor pos)
{

	selecionaItem(pos);
}
inline bool ComboBox::cursorEmCimaComboAberta(Vetor pos)
{
	Vetor tamanhoNovo = ComboBox::tamanho;
	tamanhoNovo.y += (abs(posicao.y - tamanho.y)) * (itens.size() -1);
	return comboAberta &&  (CalculosUteis::pontoDentroDeArea(pos,ComboBox::posicao,tamanhoNovo));
}
void ComboBox::setItens(vector<string> itens)
{
	ComboBox::itens = itens;
}
void ComboBox::setItens(string itens...)
{
//	for(int i=0;i<itens.size();i++)
//		ComboBox::itens.push_back(itens[i]);

}
vector<string> ComboBox::getItens()
{
	return ComboBox::itens;
}
bool ComboBox::comboEstaAberta()
{
	return ComboBox::comboAberta;
}
