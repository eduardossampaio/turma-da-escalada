#include "stdafx.h"
#include "CaixaMensagem.h"


CaixaMensagem::CaixaMensagem(Vetor pos,Vetor tamanho):Componente(pos)
{
	CaixaMensagem::tamanho = tamanho;
}


CaixaMensagem::~CaixaMensagem(void)
{
}
void CaixaMensagem::fechar()
{
	habilitar(false);
	Componente::desativarFoco();
	
}

