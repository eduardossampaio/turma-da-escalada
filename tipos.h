#pragma once
#include "irrlicht.h"
#include <iostream>
#include <vector>

using namespace std;

namespace tipos{
	
	

	//IrrlichtDevice * irrDevice;
	
	typedef struct s_vetor{
		float x;
		float y;
		float z;	

		/*
		
		*/
		s_vetor(float _x,float _y,float _z) : x(_x),y(_y),z(_z)
		{}
		/*

		*/
		s_vetor(float _x,float _y) : x(_x),y(_y),z(0.0)
		{}
		/*

		*/
		s_vetor() : x(0),y(0),z(0)
		{}
	
	} Vetor;

	typedef struct s_area 
	{
		
		Vetor v1;
		Vetor v2;
		
		s_area(){}
		
		s_area(Vetor v1,Vetor v2):v1(v1),v2(v2){}
		
		s_area(float x1,float y1,float x2,float y2):v1(Vetor(x1,y1)),v2(Vetor(x2,y2)){}
		
		

	}Area;


	typedef struct s_esqueleto
	{
		static const int qtd=12;
		Vetor cabeca;
		Vetor ombro_direito;
		Vetor ombro_esquerdo;
		Vetor cotovelo_direito;
		Vetor cotovelo_esquerdo;
		Vetor mao_direita;
		Vetor mao_esquerda;
		Vetor abdomen;
		Vetor joelho_direito;
		Vetor joelho_esquerdo;
		Vetor pe_direito;
		Vetor pe_esquerdo;
		
		Vetor** getJoints(){
			Vetor * juntas[qtd];
			juntas[0]=&cabeca;
			juntas[1]=&ombro_direito;
			juntas[2]=&ombro_esquerdo
				;
			juntas[3]=&cotovelo_direito;
			juntas[4]=&cotovelo_esquerdo;
			juntas[5]=&mao_direita;
			juntas[6]=&mao_esquerda;
			juntas[7]=&abdomen;
			juntas[8]=&joelho_direito;
			juntas[9]=&joelho_esquerdo;
			juntas[10]=&pe_esquerdo;
			juntas[11]=&pe_direito;

			return juntas;
		}

		void escalarEsqueleto(float escala){
			cabeca.x*=escala;
			ombro_direito.x*=escala;
			ombro_esquerdo.x*=escala;
			cotovelo_direito.x*=escala;
			cotovelo_esquerdo.x*=escala;
			mao_direita.x*=escala;
			mao_esquerda.x*=escala;
			abdomen.x*=escala;
			joelho_direito.x*=escala;
			joelho_esquerdo.x*=escala;
			pe_direito.x*=escala;
			pe_esquerdo.x*=escala;

			cabeca.y*=escala;
			ombro_direito.y*=escala;
			ombro_esquerdo.y*=escala;
			cotovelo_direito.y*=escala;
			cotovelo_esquerdo.y*=escala;
			mao_direita.y*=escala;
			mao_esquerda.y*=escala;
			abdomen.y*=escala;
			joelho_direito.y*=escala;
			joelho_esquerdo.y*=escala;
			pe_direito.y*=escala;
			pe_esquerdo.y*=escala;
		}
		s_esqueleto inverter()
		{
			Vetor ** joints = getJoints();
			for(int i=0;i<qtd;i++){
				joints[i]->y*=-1;
			}
			return *this;
		}
		

	}Esqueleto;


	


	/*
	class Configuracoes{
	private:
		//static Vetor Configuracoes::resolucao = Vetor(1024,768)
	public:
		static Vetor Configuracoes::getConfiguracoes(){
			
			return Vetor(1024,768);
			//return Vetor(1920,1080);
		}
	};

	*/

	
	



	enum Mao{
		DIREITA,ESQUERDA
	};
	typedef struct s_configuracoes{
		Vetor resolucao;
		bool  fullscreen;
		int	bitsCor;
		Mao mao;

	}configuracoes;


	

	enum Sexo{
		MASCULINO,FEMININO
	};
	typedef struct s_perfil{
		s_perfil(int id,std::string nome,std::string personagem,int idade,float peso,Sexo sexo):
			id(id),nome(nome),personagem(personagem),idade(idade),peso(peso),sexo(sexo){}
		s_perfil(){}

		int				id;
		std::string		nome;
		std::string		personagem;
		int				idade;
		float			peso;
		Sexo			sexo;

	}Perfil;

	


	typedef struct s_inventario_item
	{
		s_inventario_item(){}
		s_inventario_item(int item,int qtd_)
		{
			itemId = item;
			qtd    = qtd_;
		}
		
		int qtd;
		int itemId;

	}InventarioItem;


	typedef struct s_inventario
	{
		s_inventario():moedas(0)
		{
			//teste
			//itens.push_back(InventarioItem(0,0));
		}
		
		int moedas;
		vector<InventarioItem> itens;

	}Inventario_t;

	
	typedef struct s_save
	{
		s_save(Perfil perfil,int pontos):perfil(perfil),pontos(pontos){}
		s_save(Perfil perfil,int pontos,Inventario_t inventario):perfil(perfil),pontos(pontos),inventario(inventario){}
		s_save(){}
		Perfil		perfil;
		int			pontos;
		Inventario_t	inventario;

	}Save;

	enum JanelaExibicao
	{
		Intro_Scene,
		Janela_Principal,
		Janela_Novo_Jogo,
		Janela_Configuracao,
		Janela_Escolha_Personagem,
		Janela_Escolha_Perfil,
		
	};

	enum tipo_item
	{
		OUTROS,			//0
		SAPATILHA,		//1
		CAPACETE,		//2
		CADEIRINHA,		//3
		MOSQUETAO,		//4
		CORDA,			//5
		MAGNESIO,		//6
		HALTER			//7
		
	};
	typedef struct s_item_loja{// caminho= imagem/ descrição
		s_item_loja(std::string caminho,std::string nome, std::string descricao,int valor, float peso):
			caminho(caminho),valor(valor),nome(nome),descricao(descricao), peso(peso){}
		s_item_loja(){}
		std::string caminho;
		std::string caminhoG;
		std::string descricao;
		std::string nome;
		float peso;
		int valor;
		int id;
		tipo_item tipo;
	}Item_loja;

	typedef struct mesh_material
	{
		mesh_material(){}
		mesh_material(int id,std::string arquivo):id(id),arquivo(arquivo){}
		int id;
		std::string arquivo;
	}Mesh_Material;
	typedef struct mesh_info_s
	{
		std::string arquivo;
		std::string img;
		tipos::Vetor posicao;
		tipos::Vetor escala;
		tipos::Vetor rotacao;
		std::string id;
		vector<Mesh_Material> materiais;
	}Mesh_Info;
	

	typedef struct s_camera_info
	{
		Vetor posicao;
		Vetor rotacao;
		Vetor lookat;
	}Camera_info;

	typedef struct s_fase_dados
	{
		
		Mesh_Info		ambiente;
		Mesh_Info		personagem;
		Camera_info		camera;
		vector<Vetor>	marcadores;
		Vetor			luz;
		float			cume;
		//marcadores
		//moedas
		//inimigos
		//MarcadorPedra marcador;
		//vid * marcador;



	}Fase_Dados;

	typedef struct s_fase_info{
		//Imagem * imagem
		std::string local;
		Vetor  coordenadas;
		std::string descricao;
		std::string infoFauna;
		std::string infoFlora;
		std::string curiosidades;
		Fase_Dados dados;
	}FaseInfo;

};