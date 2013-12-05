#include "stdafx.h"
#include "PerfilDao.h"
#include "Conversoes.h"
#include <fstream>
#include <stdio.h>

PerfilDao::PerfilDao(void)
{
	PerfilDao::arq			=	"perfis/perfis.xml";
	PerfilDao::arq_metadata	=	"perfis/metadata.xml";
}


PerfilDao::~PerfilDao(void)
{
}

int PerfilDao::gerarIdPersonagem()
{
	Metadata data = lerMetadata();
	data.id +=1;
	int id = data.id;
	salvarMetadata(data);
	return id;

}
void PerfilDao::criarPerfil(Save save)
{
	
	vector<Save> saves = carregarPerfis();
	
	irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_NULL);
	irr::io::IXMLWriter * writer = device->getFileSystem()->createXMLWriter(PerfilDao::arq.c_str());
	writer->writeXMLHeader();
	//<perfis>
	writer->writeElement(L"perfis");
	writer->writeLineBreak();

	//<perfil>
	
	
	for(int i=0;i<saves.size();i++){
		salvarPerfilXML(writer,saves[i]);
	}
	salvarPerfilXML(writer,save);

	//</perfis>
	writer->writeLineBreak();
	writer->writeClosingTag(L"perfis");
	writer->drop();
	

}

void PerfilDao::excluirPerfil(Save save)
{
	//Save save2 = PerfilDao::procuraPerfil(save); // tratar retorno.
	vector<Save> saves  = PerfilDao::carregarPerfis();
	irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_NULL);
	irr::io::IXMLWriter * writer = device->getFileSystem()->createXMLWriter(PerfilDao::arq.c_str());
	// Excluindo o perfil.
	vector<Save> savesAtualizado;
	for(int i=0;i<saves.size();i++)
	{
		if(saves[i].perfil.id != save.perfil.id) {
			savesAtualizado.push_back(saves[i]);
		}


	}
	saves.clear();
	

	writer->writeXMLHeader();
	//<perfis>
	writer->writeElement(L"perfis");
	writer->writeLineBreak();

	//<perfil>
	
	
	for(int i=0;i<savesAtualizado.size();i++){
		salvarPerfilXML(writer,savesAtualizado[i]);
	}
	//salvarPerfilXML(writer,save);
	//</perfis>
	writer->writeLineBreak();
	writer->writeClosingTag(L"perfis");
	writer->drop();
	

}



  bool PerfilDao::isExistPerfil(Save save) {
	vector<Save> saves  = PerfilDao::carregarPerfis();
	for(int i=0;i<saves.size();i++)
	{
		if(saves[i].perfil.id == save.perfil.id)
			return true; // existe o perfil
	}
	return false; // nao existe o perfil
  }


vector<Save> PerfilDao::carregarPerfis()
{
	vector<Save> saves ;
	irr::core::stringw tagPerfil		= L"perfil";
	irr::core::stringw tagNome			= L"nome";
	irr::core::stringw tagIdade			= L"idade";
	irr::core::stringw tagPersonagem	= L"personagem";
	irr::core::stringw tagPeso			= L"peso";
	irr::core::stringw tagSexo			= L"sexo";
	irr::core::stringw tagPontos		= L"pontos";
	irr::core::stringw tagId			= L"id";
	irr::core::stringw tagInventario	= L"inventario";
	irr::core::stringw tagMoedas		= L"moedas";
	irr::core::stringw tagItem			= L"item";
	irr::core::stringw tagQuantidade	= L"quantidade";
	irr::IrrlichtDevice * devide = irr::createDevice(irr::video::E_DRIVER_TYPE::EDT_NULL);
	irr::io::IXMLReader * xml = devide->getFileSystem()->createXMLReader(PerfilDao::arq.c_str());
	if(xml==NULL)
		return saves;
	while(xml->read())
	{
		const wchar_t * node = xml->getNodeName();
		switch (xml->getNodeType())
		{
		case irr::io::EXML_NODE::EXN_ELEMENT:			
			if(tagPerfil.equals_ignore_case(xml->getNodeName()))
			{
				bool abriuPerfil = true;
				Save save;
				while(abriuPerfil && xml->read())
				{
					switch (xml->getNodeType())
					{
					case irr::io::EXML_NODE::EXN_ELEMENT:
						if(tagNome.equals_ignore_case(xml->getNodeName()))
						{
							xml->read();
							wstring val = xml->getNodeName();
							save.perfil.nome =  Conversoes::converteParaChar(val.c_str());
						}
						if(tagIdade.equals_ignore_case(xml->getNodeName()))
						{
							xml->read();
							wstring val = xml->getNodeName();
							save.perfil.idade = Conversoes::converteParaInt(val.c_str());
						}
						if(tagPeso.equals_ignore_case(xml->getNodeName()))
						{
							xml->read();
							wstring val = xml->getNodeName();
							save.perfil.peso = Conversoes::converteParaInt(val.c_str());
						}
						if(tagPersonagem.equals_ignore_case(xml->getNodeName()))
						{
							xml->read();
							wstring val = xml->getNodeName();
							save.perfil.personagem = Conversoes::converteParaChar(val.c_str());
						}
						if(tagSexo.equals_ignore_case(xml->getNodeName()))
						{
							xml->read();
							wstring val = xml->getNodeName();
							string	temp = std::string(val.begin(),val.end());

							if(strcmp(temp.c_str(),"Masculino")==0)
								save.perfil.sexo=Sexo::MASCULINO;
							else
								save.perfil.sexo=Sexo::FEMININO;
							//irr::core::stringw temp=new wstring( xml->getNodeName() );
							
							//if(temp.equals_ignore_case(L"Masculino"))
							//	save.perfil.sexo=Sexo::MASCULINO;
							//else
							//	save.perfil.sexo=Sexo::FEMININO;
							

							
						}
						if(tagPontos.equals_ignore_case(xml->getNodeName()))
						{
							xml->read();
							wstring val = xml->getNodeName();
							save.pontos = Conversoes::converteParaInt(val.c_str());
						}
						if(tagId.equals_ignore_case(xml->getNodeName()))
						{
							xml->read();
							save.perfil.id = Conversoes::converteParaInt(xml->getNodeName());
						}
						
						//<inventario>
						if(tagInventario.equals_ignore_case(xml->getNodeName()))
						{
							

							bool abriuInventario=true;
							while(abriuInventario &&  xml->read())
							{
								switch (xml->getNodeType())
								{

									case irr::io::EXML_NODE::EXN_ELEMENT:
										if(tagMoedas.equals_ignore_case(xml->getNodeName()))
										{
											xml->read();
											save.inventario.moedas = Conversoes::converteParaInt(xml->getNodeName());
										}
										if(tagItem.equals_ignore_case(xml->getNodeName()))
										{
											bool abriuItem = true;
											InventarioItem item;
											while(abriuItem && xml->read())
											{
												switch (xml->getNodeType())
												{
												case irr::io::EXML_NODE::EXN_ELEMENT:
													//<id>
													if(tagId.equals_ignore_case(xml->getNodeName()))
													{
														xml->read();
														item.itemId = Conversoes::converteParaInt(xml->getNodeName());
													}
													//<quantidade>
													if(tagQuantidade.equals_ignore_case(xml->getNodeName()))
													{
														xml->read();
														item.qtd = Conversoes::converteParaInt(xml->getNodeName());

													}

													break;
												case irr::io::EXML_NODE::EXN_ELEMENT_END:
													if(tagItem.equals_ignore_case(xml->getNodeName()))
													{
														abriuItem = false;
														save.inventario.itens.push_back(item);
													}
												}	
												
											}
										}

										break;
									case irr::io::EXML_NODE::EXN_ELEMENT_END:
										if(tagInventario.equals_ignore_case(xml->getNodeName()))
										{
											abriuInventario = false;											
										}
										printf("%s\n",xml->getNodeName());
										//break;
									
								}
							}
						}


						break;
					case irr::io::EXML_NODE::EXN_ELEMENT_END:
						if(tagPerfil.equals_ignore_case(xml->getNodeName()))
						{
							abriuPerfil=false;
							saves.push_back(save);
						}
					}

				}
			}
			break;
		case irr::io::EXML_NODE::EXN_ELEMENT_END:
			break;
		}
	}
	xml->drop();
	return saves;
}
void PerfilDao::atualizarPerfil(Save save)
{
	printf("atualizando perfil\n");
	vector<Save> saves = carregarPerfis();
	for(int i=0;i<saves.size();i++)
	{
		if(saves[i].perfil.id == save.perfil.id)
			saves[i]=save;
	}
	
//	vector<Save> saves = carregarPerfis();
	
	irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_NULL);
	irr::io::IXMLWriter * writer = device->getFileSystem()->createXMLWriter(PerfilDao::arq.c_str());
	writer->writeXMLHeader();
	//<perfis>
	writer->writeElement(L"perfis");
	writer->writeLineBreak();

	//<perfil>
	
	
	for(int i=0;i<saves.size();i++){
		salvarPerfilXML(writer,saves[i]);
	}
	//salvarPerfilXML(writer,save);

	//}

	

	//</perfis>
	writer->writeLineBreak();
	writer->writeClosingTag(L"perfis");
	writer->drop();
	
	
	
}

void PerfilDao::novaTag(irr::io::IXMLWriter * writer, wstring tag,std::string val)
{
	
	std::wstring ws = std::wstring (val.begin(),val.end());	
	
	writer->writeElement(tag.c_str());
	writer->writeText(ws.c_str());	
	writer->writeClosingTag(tag.c_str());
	writer->writeLineBreak();
	//</perfil>
	

}

void PerfilDao::salvarPerfilXML(irr::io::IXMLWriter * writer,Save save)
{
		writer->writeElement(L"perfil");
		writer->writeLineBreak();
		
		novaTag(writer,L"nome",save.perfil.nome);		
		novaTag(writer,L"idade",Conversoes::converteParaString(save.perfil.idade));
		novaTag(writer,L"personagem",save.perfil.personagem);
		novaTag(writer,L"peso",Conversoes::converteParaString(save.perfil.peso));
		if(save.perfil.sexo==Sexo::MASCULINO)
			novaTag(writer,L"sexo","Masculino");
		else
			novaTag(writer,L"sexo","Feminino");
		novaTag(writer,L"id",Conversoes::converteParaString(save.perfil.id));
		novaTag(writer,L"pontos",Conversoes::converteParaString(save.pontos));
		writer->writeElement(L"inventario");
		writer->writeLineBreak();

		novaTag(writer,L"moedas",Conversoes::converteParaString(save.inventario.moedas));
		for(int i=0;i<save.inventario.itens.size();i++)
		{
			writer->writeElement(L"item");
			writer->writeLineBreak();
			
			novaTag(writer,L"id",Conversoes::converteParaString(save.inventario.itens[i].itemId));
			novaTag(writer,L"quantidade",Conversoes::converteParaString(save.inventario.itens[i].qtd));
			writer->writeLineBreak();
			writer->writeClosingTag(L"item");
			writer->writeLineBreak();
		}


		writer->writeLineBreak();
		writer->writeClosingTag(L"inventario");

		writer->writeLineBreak();
		writer->writeClosingTag(L"perfil");
		writer->writeLineBreak();
}

PerfilDao::Metadata	PerfilDao::lerMetadata()
{
	PerfilDao::Metadata metadata = Metadata();
	irr::IrrlichtDevice * devide = irr::createDevice(irr::video::E_DRIVER_TYPE::EDT_NULL);
	irr::io::IXMLReader * xml = devide->getFileSystem()->createXMLReader(PerfilDao::arq_metadata.c_str());
	irr::core::stringw tag_metadata	= L"metadata";
	irr::core::stringw tag_id 		= L"id";
	if(xml == NULL)
	{
		metadata.id = 0;
		return metadata;
	}
	while(xml->read())
	{
		switch (xml->getNodeType())
		{
		case irr::io::EXML_NODE::EXN_ELEMENT:
			//<metadata
			if(tag_metadata.equals_substring_ignore_case(xml->getNodeName()))
			{
				bool abriuMetadata = true;
				while(xml->read() && abriuMetadata)
				{
					switch (xml->getNodeType())
					{
						case irr::io::EXML_NODE::EXN_ELEMENT:
							if(tag_id.equals_ignore_case(xml->getNodeName()))
							{
								xml->read();
								metadata.id = Conversoes::converteParaInt(xml->getNodeName());
							}
							break;
							
						case irr::io::EXML_NODE::EXN_ELEMENT_END:
							//</metadata>
							if(tag_metadata.equals_ignore_case(xml->getNodeName()))
								abriuMetadata = false;
					}
				}
			}
			break;
		}

	}

	return metadata;
}

void PerfilDao::salvarMetadata(PerfilDao::Metadata data)
{
	PerfilDao::Metadata metadata;
	irr::IrrlichtDevice * devide = irr::createDevice(irr::video::E_DRIVER_TYPE::EDT_NULL);
	irr::io::IXMLWriter * xml = devide->getFileSystem()->createXMLWriter(PerfilDao::arq_metadata.c_str());
	irr::core::stringw tag_metadata	= L"metadata";
	irr::core::stringw tag_id 		= L"id";
	wchar_t * temp;

	xml->writeXMLHeader();
	//<metadata>
	xml->writeElement(tag_metadata.c_str());
	xml->writeLineBreak();

	//<id>
	xml->writeElement(tag_id.c_str());
	
	//Conversoes::converteParaWChar(&temp,data.id);
	string s = Conversoes::converteParaString(data.id);
	
	//data.id
	xml->writeText(Conversoes::converteParaWChar((char *)s.c_str()));
	
	//</id>
	xml->writeClosingTag(tag_id.c_str());	
	xml->writeLineBreak();

	//</metadata>
	xml->writeClosingTag(tag_metadata.c_str());
	xml->drop();
}