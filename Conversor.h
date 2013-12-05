#pragma once
#include "tipos.h"
#include "Nite.h"
using namespace tipos;

class Conversor
{
public:
	Conversor(void);
	~Conversor(void);
	inline static Esqueleto NiteSkeletonParaEsqueleto(const nite::Skeleton *skeleton)
	{
		Esqueleto esqueleto = Esqueleto();
		const nite::SkeletonJoint& cabeca				= skeleton->getJoint(nite::JOINT_HEAD);
		const nite::SkeletonJoint& cotovelo_esquerdo	= skeleton->getJoint(nite::JOINT_LEFT_ELBOW);
		const nite::SkeletonJoint& pe_esquerdo			= skeleton->getJoint(nite::JOINT_LEFT_FOOT);
		const nite::SkeletonJoint& mao_esquerda			= skeleton->getJoint(nite::JOINT_LEFT_HAND);
		const nite::SkeletonJoint& quadril_esquerdo		= skeleton->getJoint(nite::JOINT_LEFT_HIP);
		const nite::SkeletonJoint& joelho_esquerdo		= skeleton->getJoint(nite::JOINT_LEFT_KNEE);
		const nite::SkeletonJoint& ombro_esquerdo		= skeleton->getJoint(nite::JOINT_LEFT_SHOULDER);
		const nite::SkeletonJoint& pescoco				= skeleton->getJoint(nite::JOINT_NECK);
		const nite::SkeletonJoint& cotovelo_direito		= skeleton->getJoint(nite::JOINT_RIGHT_ELBOW);
		const nite::SkeletonJoint& pe_direito			= skeleton->getJoint(nite::JOINT_RIGHT_FOOT);
		const nite::SkeletonJoint& mao_direita			= skeleton->getJoint(nite::JOINT_RIGHT_HAND);
		const nite::SkeletonJoint& quadril_direito		= skeleton->getJoint(nite::JOINT_RIGHT_HIP);
		const nite::SkeletonJoint& joelho_direito		= skeleton->getJoint(nite::JOINT_RIGHT_KNEE);
		const nite::SkeletonJoint& ombro_direito		= skeleton->getJoint(nite::JOINT_RIGHT_SHOULDER);
		const nite::SkeletonJoint& torso				= skeleton->getJoint(nite::JOINT_TORSO);		
		esqueleto.cabeca								= niteJointParaVetor(cabeca);
		esqueleto.abdomen								= niteJointParaVetor(torso);
		esqueleto.cotovelo_direito						= niteJointParaVetor(cotovelo_direito);
		esqueleto.cotovelo_esquerdo						= niteJointParaVetor(cotovelo_esquerdo);
		esqueleto.joelho_direito						= niteJointParaVetor(joelho_direito);
		esqueleto.joelho_esquerdo						= niteJointParaVetor(joelho_esquerdo);
		esqueleto.mao_direita							= niteJointParaVetor(mao_direita);
		esqueleto.mao_esquerda							= niteJointParaVetor(mao_esquerda);
		esqueleto.ombro_direito							= niteJointParaVetor(ombro_direito);
		esqueleto.ombro_esquerdo						= niteJointParaVetor(ombro_esquerdo);
		esqueleto.pe_direito							= niteJointParaVetor(pe_direito);
		esqueleto.pe_esquerdo							= niteJointParaVetor(pe_esquerdo);
		
		return esqueleto;
	}

	inline static Vetor niteJointParaVetor(nite::SkeletonJoint joint){
		Vetor vetor;
		nite::Point3f pos = joint.getPosition();
		vetor.x = pos.x;
		vetor.y = pos.y;
		vetor.z = pos.z;
		
		return vetor;
	}
};


