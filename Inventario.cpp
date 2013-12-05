#include "stdafx.h"
#include "Inventario.h"
#include "ItemDAO.h"

Inventario::Inventario(void)
{
	Inventario::dinheiro = 0;
}
Inventario::Inventario(tipos::Inventario_t inventario_t)
{
	Inventario::dinheiro = inventario_t.moedas;
	ItemDAO * dao = new ItemDAO();
	for(int i=0;i<inventario_t.itens.size();i++)
	{
		Item_loja * item = dao->getItem(inventario_t.itens[i].itemId);
		if(item!=NULL)
			Inventario::itens.push_back(Inventario::Item(item,inventario_t.itens[i].qtd));
	}
	
}

Inventario::~Inventario(void)
{
}

float Inventario::getPesoTotalItens()
{
	float peso =0;

	for(int i=0;i<itens.size();i++)
	{
		peso+=itens[i].item->peso*(itens[i].quantidade);
	}

	return peso;
}

void Inventario::adicionarItem (tipos::Item_loja item,int qtd)
{
	int i = getIndiceItem(item);
	if(i==-1)
		Inventario::itens.push_back(Inventario::Item(&item,qtd));
	else
	{
		itens[i].quantidade+=qtd;
	}
}
//mudar depois
bool Inventario::possuiItem(tipos::Item_loja item_l)
{
	for(int i=0;i<Inventario::itens.size();i++)
	{
		if(itens[i].item->id == item_l.id)
			return true;
	}
	return false;
}
void Inventario::removerItem(tipos::Item_loja item,int qtd)
{
	int indice = getIndiceItem(item);
	if(indice!=-1)
	{
		Inventario::Item item = itens[indice];
		if(item.quantidade>0)
		{
			item.quantidade-=qtd;
			if(item.quantidade<0)
				item.quantidade = 0;
		}
		itens[indice]=item;
		

	}
}
int Inventario::quatidadeItem(tipos::Item_loja item)
{
	int i =getIndiceItem(item);
	if(i>=0)
	{
		return itens[i].quantidade;
	}
	return 0;
}
int  Inventario::totalItens()
{
	return Inventario::itens.size();
}
//ver como vai fazer essa aqui
void Inventario::usarItem(tipos::Item_loja)
{

}
int  Inventario::getDinheiro()
{
	return Inventario::dinheiro;
}
void Inventario::setDinheiro(int dinheiro)
{
	Inventario::dinheiro = dinheiro;
}
void Inventario::addDinheiro(int dinheiro)
{
	Inventario::dinheiro += dinheiro;
}
void Inventario::subtraiDinheiro(int dinheiro)
{
	Inventario::dinheiro-=dinheiro;
	if(Inventario::dinheiro<0)
		Inventario::dinheiro = 0;
}

bool Inventario::possuiDinheiro()
{
	return Inventario::dinheiro>0;
}

vector<Inventario::Item> Inventario::getItens()
{
	return Inventario::itens;
}

int Inventario::getIndiceItem(Item_loja item)
{
	for(int i=0;i<Inventario::itens.size();i++)
	{
		if(itens[i].item->id == item.id)
			return i;
	}
	return -1;
}
bool Inventario::contemTipoItem(tipos::tipo_item tipo)
{
	for(int i=0;i<itens.size();i++)
	{
		if(itens[i].item->tipo == tipo)
			return true;
	}
	return false;
}