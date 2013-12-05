#include "stdafx.h"
#include "FaseDAO.h"
#include "Irrlicht.h"
#include "Conversoes.h"
FaseDAO::FaseDAO(void)
{
}


FaseDAO::~FaseDAO(void)
{
}

tipos::Fase_Dados FaseDAO::getFase(std::string arquivo)
{
	tipos::FaseInfo fase;
	irr::IrrlichtDevice * device = irr::createDevice(irr::video::EDT_NULL);
	irr::io::IXMLReader * xml = device->getFileSystem()->createXMLReader(arquivo.c_str());
	irr::core::stringw tag_fase			= L"fase";
	irr::core::stringw tag_escala		= L"escala";
	irr::core::stringw tag_arquivo		= L"arquivo";
	irr::core::stringw tag_posicao		= L"posicao";
	irr::core::stringw tag_camera		= L"camera";
	irr::core::stringw tag_marcador		= L"marcador";
	irr::core::stringw tag_marcadores	= L"marcadores";
	irr::core::stringw tag_rotacao		= L"rotacao";
	irr::core::stringw tag_lookat		= L"lookat";
	irr::core::stringw tag_personagem	= L"personagem";
	irr::core::stringw tag_iluminacao	= L"iluminacao";
	irr::core::stringw tag_cume			= L"cume";
	
	tipos::Fase_Dados dados;
	while(xml->read())
	{
		switch (xml->getNodeType())
		{
		case irr::io::EXML_NODE::EXN_ELEMENT:
			//<arquivo>
			if(tag_arquivo.equals_ignore_case(xml->getNodeName()))
			{
				dados.ambiente.arquivo = lerString(xml);
			}
			//<posicao>
			if(tag_posicao.equals_ignore_case(xml->getNodeName()))
			{
				dados.ambiente.posicao = lerTagComVetor(tag_posicao,xml);
			}
			//escala
			if(tag_escala.equals_ignore_case(xml->getNodeName()))
			{
				dados.ambiente.escala = lerTagComVetor(tag_escala,xml);
			}
			//<rotacao>
			if(tag_rotacao.equals_ignore_case(xml->getNodeName()))
			{
				dados.ambiente.rotacao = lerTagComVetor(tag_rotacao,xml);
			}
			//<camera>
			if(tag_camera.equals_ignore_case(xml->getNodeName()))
			{
				bool abriuCamera = true;
				while(abriuCamera && xml->read())
				{
					stringw tag = xml->getNodeName();
					switch (xml->getNodeType())
					{
					case irr::io::EXML_NODE::EXN_ELEMENT:
						//<posicao>
						if(tag_posicao.equals_ignore_case(xml->getNodeName()))
						{
							dados.camera.posicao = lerTagComVetor(tag_posicao,xml);
						}
						//rotacao
						if(tag_rotacao.equals_ignore_case(xml->getNodeName()))
						{
							dados.camera.rotacao = lerTagComVetor(tag_rotacao,xml);
						}
						//lookat
						if(tag_lookat.equals_ignore_case(xml->getNodeName()))
						{
							dados.camera.lookat =  lerTagComVetor(tag_lookat,xml);
						}
						break;
					case irr::io::EXML_NODE::EXN_ELEMENT_END:
						if(tag_camera.equals_ignore_case(xml->getNodeName()))
						{
							abriuCamera = false;
						}
						break;
					}

				}

			}
			//<personagem>
			if(tag_personagem.equals_ignore_case(xml->getNodeName()))
			{
				bool abriuPersonagem = true;
				while(abriuPersonagem && xml->read())
				{
					stringw tag = xml->getNodeName();
					switch (xml->getNodeType())
					{
						case irr::io::EXML_NODE::EXN_ELEMENT:
							if(tag_posicao.equals_ignore_case(tag))
							{
								dados.personagem.posicao = lerTagComVetor(tag_posicao,xml);
							}
							if(tag_rotacao.equals_ignore_case(tag))
							{
								dados.personagem.rotacao = lerTagComVetor(tag_rotacao,xml);
							}
							if(tag_escala.equals_ignore_case(tag))
							{
								dados.personagem.escala = lerTagComVetor(tag_escala,xml);
							}
							break;
						case irr::io::EXML_NODE::EXN_ELEMENT_END:
							if(tag_personagem.equals_ignore_case(xml->getNodeName()))
								abriuPersonagem= false;
							break;
					}
				}
				
				
			}
			//<marcadores>
			if(tag_marcadores.equals_ignore_case(xml->getNodeName()))
			{
				bool abriuMarcador = true;
				while(abriuMarcador && xml->read())
				{
					switch (xml->getNodeType())
					{
					case irr::io::EXML_NODE::EXN_ELEMENT:
						if(tag_marcador.equals_ignore_case(xml->getNodeName()))
							dados.marcadores.push_back(lerTagComVetor(tag_marcador,xml));

						break;
					case irr::io::EXML_NODE::EXN_ELEMENT_END:
						if(tag_marcadores.equals_ignore_case(xml->getNodeName()))
						{
							abriuMarcador = false;
						}
						break;
					}

				}
			}
			//iluminacao
			if(tag_iluminacao.equals_ignore_case(xml->getNodeName()))
			{
				dados.luz = lerTagComVetor(tag_iluminacao,xml);
			}
			//cume
			if(tag_cume.equals_ignore_case(xml->getNodeName()))
			{
				xml->read();
				dados.cume  = Conversoes::converteParaFloat(xml->getNodeName());
			}


			break;
		default:
			break;
		}

	}


	return dados;

}