#pragma once
#include "tipos.h"
#include "irrlicht.h"

#include "Transformador.h"
#include "MarcadorPedra.h"
class Avatar
{
public:
        Avatar(irr::scene::ISceneManager * mgr,tipos::Mesh_Info info,vector<MarcadorPedra *> marcadores);
        ~Avatar(void);
        void atualizarPosicao(tipos::Esqueleto esqueleto);
        tipos::Esqueleto getPosicao();
        void setNode(irr::scene::IAnimatedMeshSceneNode * node);
        irr::scene::IAnimatedMeshSceneNode* getNode();

		//trava/libera membros
		void liberarBracoDireito(bool libera);
		void liberarBracoEsquerdo(bool libera);
		void liberarPernaDireita(bool libera);
		void liberarPernaEsquerda(bool libera);


		//temp
		//mover para private
		void subirPersonagem(float valParaSubir);
private:
        tipos::Esqueleto esqueleto;
        tipos::Mesh_Info info;
        irr::scene::ISceneManager * mgr;
        
        irr::scene::IAnimatedMesh * mesh;
        irr::scene::IAnimatedMeshSceneNode * node;

		vector<MarcadorPedra *> marcadores;
        
        void setarAnguloBone(std::string nome_bone,float angulo);
		void setarAnguloBraco(tipos::Vetor p1,tipos::Vetor p2,std::string nome_bone);
        float getAnguloBraco(tipos::Vetor p1,tipos::Vetor p2);

        static std::string root_bone ;
        static std::string scene_root_bone;
        static std::string root_root_bone;
        static std::string quadril_bone;
        static std::string coxa_esquerda_bone;
        static std::string perna_esquerda_bone ;
        static std::string pe_esquerdo_bone ;
        static std::string coxa_direita_bone;
        static std::string perna_direita_bone ;
        static std::string pe_direito_bone;
        static std::string coluna1_bone ;
        static std::string coluna2_bone;
        static std::string ombro_esquerdo_bone ;
        static std::string braco_esquerdo_bone ;
        static std::string mao_esquerda_bone;
        static std::string ombro_direito_bone ;
        static std::string braco_direito_bone ;
        static std::string mao_direita_bone;
        static std::string pescoco_bone ;
        static std::string cabeca_bone ;
        
		std::string bones[20];
        
		//travar os membros
		bool	moveBracoDireito;
		bool	moveBracoEsquerdo;
		bool	movePernaDireita;
		bool	movePernaEsquerda;
		
		
		bool primeiro;

		//teste
		Transformador * transformadorTeste;
		Transformador * transformadorSubir;
};