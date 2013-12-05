#include "stdafx.h"
#include "Jogador.h"


Jogador::Jogador(void)
{
}

Jogador::Jogador(tipos::Save save)
{
	//Jogador::perfil = save.perfil;
	Jogador::save = save;
	Jogador::inventario = new Inventario(save.inventario);
}



Jogador::~Jogador(void)
{
}

Inventario* Jogador::getInventario()
{
	return Jogador::inventario;
}
void Jogador::setInventario(Inventario *inventario)
{
	Jogador::inventario = inventario;
}
int	Jogador::getVidas()
{
	return Jogador::getVidas();
}
void Jogador::setVidas(int vidas)
{
	Jogador::vidas = vidas;
}
void Jogador::setPerfil(tipos::Perfil perfil)
{
	Jogador::save.perfil = perfil;
}
tipos::Perfil Jogador::getPerfil()
{
	return Jogador::save.perfil;
}
void Jogador::setAvatar(Avatar * avatar)
{
	Jogador::avatar = avatar;
}
Avatar* Jogador::getAvatar()
{
	return Jogador::avatar;
}
void Jogador::addDinheiro(int dinheiro)
{
	if(Jogador::inventario!=NULL)
		Jogador::inventario->addDinheiro(dinheiro);
}
void Jogador::diminuiVida()
{
	if(Jogador::vidas>0)
		Jogador::vidas--;
}
void Jogador::aumentaVida()
{
	Jogador::vidas++;
}
void Jogador::atualizaPosicaoAvatar(tipos::Esqueleto esqueleto)
{
	Jogador::avatar->atualizarPosicao(esqueleto);
}
bool Jogador::podeComprarItem(tipos::Item_loja item)
{
	return Jogador::podeComprarItem(item,1);
}
bool Jogador::podeComprarItem(tipos::Item_loja item,int qtd)
{
	return Jogador::inventario->getDinheiro()>=(item.valor*qtd);
}
void Jogador::comprarItem(tipos::Item_loja item)
{
	Jogador::comprarItem(item,1);
}
void Jogador::comprarItem(tipos::Item_loja item,int qtd)
{
	printf("comprou %d %s\n",qtd,item.descricao.c_str());
	Jogador::inventario->subtraiDinheiro(item.valor * qtd);
	Jogador::inventario->adicionarItem(item,qtd);

}
bool Jogador::podeVenderItem(tipos::Item_loja item)
{
	return inventario->possuiItem(item);
}

void Jogador::venderItem(tipos::Item_loja item)
{
	Jogador::venderItem(item,1);
}
void Jogador::venderItem(tipos::Item_loja item,int qtd)
{
	
	Jogador::inventario->addDinheiro(item.valor * qtd);
	Jogador::inventario->removerItem(item,qtd);

}


Save Jogador::getSave()
{
	Jogador::save.inventario=tipos::Inventario_t();
	//atualiza dinheiro
	Jogador::save.inventario.moedas = Jogador::getInventario()->getDinheiro();
	
	//atualiza itens
	vector<Inventario::Item> itens = Jogador::inventario->getItens();
	for(int i=0;i<itens.size();i++)
	{
		Inventario::Item item = itens[i];
		Jogador::save.inventario.itens.push_back(tipos::InventarioItem(item.item->id,item.quantidade));
	}
	return Jogador::save;
}