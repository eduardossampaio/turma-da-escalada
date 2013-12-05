#include "stdafx.h"
#include "PersonagemDAO.h"
#include "Conversoes.h"
#include "tipos.h"
using namespace tipos;


PersonagemDAO::PersonagemDAO(void)
{
	PersonagemDAO::arquivo = "modelos/personagens.xml";
}


PersonagemDAO::~PersonagemDAO(void)
{
}

vector<Mesh_Info> PersonagemDAO::getPersonagens()
{
	IrrlichtDevice * device		=	
		//irr::createDevice();
									getDevice();
	irr::io::IXMLReader *xml	=	device->getFileSystem()->createXMLReader(PersonagemDAO::arquivo.c_str());
	stringw tag_personagens		=	"personagens";
	stringw tag_personagem		=	"personagem";
	stringw tag_id				=	"id";
	stringw tag_arquivo			=	"arquivo";
	stringw tag_imagem			=	"imagem";
	stringw tag_escala			=	"escala";
	stringw tag_rotacao			=	"rotacao";
	stringw tag_material		=	"material";
	stringw tag_x				=	"x";
	stringw tag_y				=	"y";
	stringw tag_z				=	"z";
	vector<Mesh_Info> personagens;

	while(xml->read())
	{
		switch (xml->getNodeType())
		{
		case irr::io::EXN_ELEMENT:
			//<personagens>
			
			if(tag_personagens.equals_ignore_case(xml->getNodeName()))
			{

			}
			//<personagem>
			if(tag_personagem.equals_ignore_case(xml->getNodeName()))
			{
				Mesh_Info personagem;
				//enquanto ler e nao for fim de tag e a tag não for <personagem>
				bool abriuTagPersonagem = true;
				printf("<personagem>\n");
				while(abriuTagPersonagem && xml->read())
				{

					switch(xml->getNodeType())
					{
					case EXN_ELEMENT:
						//<id>
						if(tag_id.equals_ignore_case(xml->getNodeName()))
						{
							xml->read();
							const wchar_t * valor = xml->getNodeName();
							char * id = Conversoes::converteParaChar(valor);
							
							personagem.id = id;
							printf("id: %s\n",personagem.id.c_str());
						}
						//<arquivo>
						if( tag_arquivo.equals_ignore_case(xml->getNodeName()))
						{
							printf("<arquivo>: ");
							xml->read();
							const wchar_t * valor = xml->getNodeName();
							char * arquivo = Conversoes::converteParaChar(valor);
							printf("%s\n",arquivo);
							personagem.arquivo.append(arquivo);
							int a=0;
						}
						if( tag_imagem.equals_ignore_case(xml->getNodeName()))
						{
							printf("<imagem>: ");
							xml->read();
							const wchar_t * valor = xml->getNodeName();
							char * arquivo = Conversoes::converteParaChar(valor);
							printf("%s\n",arquivo);
							personagem.img.append(arquivo);
							int a=0;
						}
						//<escala>
						if(tag_escala.equals_ignore_case(xml->getNodeName()))
						{
							//bool abriuTagEscala = true;
							printf("<escala> \n");
							personagem.escala = lerTagComVetor(tag_escala,xml);
							
						}
						//<rotacao>
						if(tag_rotacao.equals_ignore_case(xml->getNodeName()))
						{
							printf("<rotacao>\n");
							personagem.rotacao = lerTagComVetor(tag_rotacao,xml);
						}
						if(tag_material.equals_ignore_case(xml->getNodeName()))
						{
							personagem.materiais =  vector<Mesh_Material>();
							while(xml->read() )
								if(xml->getNodeType()==EXN_ELEMENT_END && tag_material.equals_ignore_case( xml->getNodeName() ) )
									break;
						}
						break;
					case EXN_ELEMENT_END:
						stringw s = xml->getNodeName();
						if(tag_personagem.equals_ignore_case( xml->getNodeName())){
							abriuTagPersonagem = false;
							printf("</personagem>\n");
							personagens.push_back(personagem);
						}
						break;
					}
				}
			}

			break;
		case irr::io::EXN_ELEMENT_END:
			break;
		default:
			break;
		}


	}
	
	
	return personagens;
}

tipos::Vetor PersonagemDAO::lerTagComVetor(stringw tag,irr::io::IXMLReader *xml)
{
	bool abriuTag = true;
	printf("<escala> \n");
	
	stringw tag_x				=	"x";
	stringw tag_y				=	"y";
	stringw tag_z				=	"z";
	tipos::Vetor vetor;
	while(abriuTag & xml->read())
	{
		switch (xml->getNodeType())
		{
		case EXN_ELEMENT:
			if(tag_x.equals_ignore_case(xml->getNodeName()))
			{
				printf("X:");
				xml->read();
				const wchar_t * temp = xml->getNodeName();
				float x= Conversoes::converteParaInt(temp);
				printf("%f\n",x);
				vetor.x = x;
			}
			if(tag_y.equals_ignore_case(xml->getNodeName()))
			{
				printf("Y:");
				xml->read();
				const wchar_t * temp = xml->getNodeName();
				float y= Conversoes::converteParaInt(temp);
				printf("%f\n",y);
				vetor.y = y;

			}
			if(tag_z.equals_ignore_case(xml->getNodeName()))
			{
				printf("Y:");
				xml->read();
				const wchar_t * temp = xml->getNodeName();
				float z= Conversoes::converteParaInt(temp);
				printf("%f\n",z);
				vetor.z = z;

			}
		case EXN_ELEMENT_END:
			if(tag.equals_ignore_case(xml->getNodeName())){
				abriuTag=false;
				printf("</escala>\n");
				
			}
		default:
			break;
		}
	}
	return vetor;
}


tipos::Mesh_Info*	PersonagemDAO::getPersonagem(std::string id)
{
	vector<Mesh_Info> meshs = getPersonagens();
	for(int i=0;i<meshs.size();i++)
	{
		if(strcmp(meshs[i].id.c_str(),id.c_str()) == 0)
			return new Mesh_Info(meshs[i]);
	}
	return NULL;

}