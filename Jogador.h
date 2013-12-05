#pragma once
#include "tipos.h"
#include "Inventario.h"
#include "Avatar.h"
class Jogador
{
public:
	Jogador(void);
	Jogador(tipos::Save save);
	~Jogador(void);
	Inventario*		getInventario();
	void			setInventario(Inventario *inventario);
	int				getVidas();
	void			setVidas(int vidas);
	void			setPerfil(tipos::Perfil perfil);
	tipos::Perfil	getPerfil();
	void			setAvatar(Avatar * avatar);
	Avatar*			getAvatar();
	//void			subtrairDinheiro(int dinheiro);
	void			addDinheiro(int dinheiro);
	void			diminuiVida();
	void			aumentaVida();
	void			atualizaPosicaoAvatar(tipos::Esqueleto esqueleto);
	bool			podeComprarItem(tipos::Item_loja item);
	bool			podeComprarItem(tipos::Item_loja item,int qtd);
	bool			podeVenderItem(tipos::Item_loja item);
	void			comprarItem(tipos::Item_loja item);
	void			comprarItem(tipos::Item_loja item,int qtd);
	void			venderItem(tipos::Item_loja item,int qtd);
	void			venderItem(tipos::Item_loja item);
	Save			getSave();
private:
	//tipos::Perfil	perfil;
	Avatar			*avatar; 
	Inventario		*inventario;
	Save			save;
	int				vidas;
	
};

