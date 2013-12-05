#pragma once
#include "tipos.h"
#include "ItemDAO.h"
class Inventario
{
public:
	typedef struct s_item
	{
		s_item():item(NULL),quantidade(0){}
		
		s_item(tipos::Item_loja *item):quantidade(1)
		{
			s_item::item = new tipos::Item_loja(*item);
		}
		
		s_item(tipos::Item_loja *item,int qtd):quantidade(qtd)
		{
			s_item::item = new tipos::Item_loja(*item);
		}
		
		tipos::Item_loja *item;
		int				 quantidade;

		bool possuiItem()
		{
			return item!=NULL && quantidade!=0;
		}
			
	}Item;
	
	Inventario(void);
	Inventario(tipos::Inventario_t inventario);
	~Inventario(void);
	//metodos publicos de inventario

	void adicionarItem (tipos::Item_loja item,int qtd);
	bool possuiItem(tipos::Item_loja);
	bool possuiDinheiro();
	void removerItem(tipos::Item_loja,int qtd);
	int  totalItens();
	void usarItem(tipos::Item_loja);
	int  getDinheiro();
	void setDinheiro(int dinheiro);
	void addDinheiro(int dinheiro);
	void subtraiDinheiro(int dinheiro);
	int quatidadeItem(tipos::Item_loja);
	bool contemTipoItem(tipos::tipo_item tipo);
	float getPesoTotalItens();
	vector<Item> getItens();

private:
	vector<Item>	itens;
	int				maximoItens;
	int				dinheiro;

	int getIndiceItem(Item_loja item);
};

