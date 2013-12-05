#include "stdafx.h"
#include "IdentificadorMovimento.h"


IdentificadorMovimento::IdentificadorMovimento(void)
{
	
	indexAtual = 0;
}


IdentificadorMovimento::~IdentificadorMovimento(void)
{
}

	

void IdentificadorMovimento::adicionarMovimento(Movimento * movimento,float tempo)
{
	IdentificadorMovimento::itens.push_back(MovimentoItem(movimento,tempo));

}

EstadoCaptura IdentificadorMovimento::capturarMovimento(Esqueleto esqueleto)
{
	printf("itens %d posicao Atual: %d\n",itens.size(),indexAtual);
	if(IdentificadorMovimento::itens.size()>0)
	{
		EstadoCaptura estado = verificaEstadoPosicao(esqueleto);
		if(estado==EstadoCaptura::IDENTIFICANDO)
			return EstadoCaptura::IDENTIFICANDO;
		else if(estado == EstadoCaptura::VALIDO){
			//ultima posicao
			if(indexAtual == itens.size()-1){
				printf("ultimo\n");
				cronometro.pararContagem();
				indexAtual=0;
				return EstadoCaptura::VALIDO;
			}else{
				cronometro.pararContagem();
				indexAtual++;
				return IDENTIFICANDO;
			}
		}
		//invalido
		else{
			indexAtual=0;
			cronometro.pararContagem();
			return EstadoCaptura::INVALIDO;
		}
	
	}
	return EstadoCaptura::IDENTIFICANDO;
}

EstadoCaptura IdentificadorMovimento::verificaEstadoPosicao(Esqueleto esqueleto)
{
	if(!cronometro.iniciado())
		cronometro.iniciarContagem();
	if(cronometro.getTempoCorridoSegundos()<= itens[indexAtual].tempo){
		return itens[indexAtual].movimento->identificar(esqueleto);
	}else{
		cronometro.pararContagem();	
		return EstadoCaptura::INVALIDO;
	}

}