#include "stdafx.h"
#include "ItemDAO.h"
#include "Conversoes.h"

ItemDAO::ItemDAO(void)
{
	arquivo="itens/itens.xml";
}


ItemDAO::~ItemDAO(void)
{
}

tipos::Item_loja* ItemDAO::getItem(int id)
{
	vector<Item_loja> itens = getItens();
	for(int i=0;i<itens.size();i++)
	{
		if(itens[i].id == id)
			return new Item_loja(itens[i]);
	}
	return NULL;
}

vector<Item_loja> ItemDAO::getItens()
{
	irr::IrrlichtDevice * device = irr::createDevice(irr::video::EDT_NULL);
	vector<Item_loja> itens;
	irr::core::stringw tag_itens=L"itens";
	irr::core::stringw tag_item=L"item";
	irr::core::stringw tag_arquivo=L"arquivo";
	irr::core::stringw tag_arquivoG=L"arquivoG";
	irr::core::stringw tag_nome=L"nome";
	irr::core::stringw tag_descricao=L"descricao";
	irr::core::stringw tag_preco=L"preco";
	irr::core::stringw tag_peso=L"peso";
	irr::core::stringw tag_id  =L"id";
	irr::core::stringw tag_tipo  =L"tipo";
	
	irr::io::IXMLReader * xml = device->getFileSystem()->createXMLReader(ItemDAO::arquivo.c_str());
	while(xml->read())
	{
		switch (xml->getNodeType())
		{

		case irr::io::EXML_NODE::EXN_ELEMENT:
			//abriu tag <item>
			if(tag_item.equals_ignore_case(xml->getNodeName()))
			{
				bool abriuItem = true;
				tipos::Item_loja item;
				while(abriuItem && xml->read())
				{
					switch (xml->getNodeType())
					{
					case irr::io::EXML_NODE::EXN_ELEMENT:
						//<nome>
						if(tag_nome.equals_ignore_case(xml->getNodeName()))
						{
							xml->read();
							item.nome = Conversoes::converteParaChar(xml->getNodeName());
						}
						//<arquivo>
						else if(tag_arquivo.equals_ignore_case(xml->getNodeName()))
						{
							xml->read();
							item.caminho = Conversoes::converteParaChar(xml->getNodeName());
						}
						//<arquivoG>
						else if(tag_arquivoG.equals_ignore_case(xml->getNodeName()))
						{
							xml->read();
							item.caminhoG = Conversoes::converteParaChar(xml->getNodeName());
						}
						//<descricao>
						else if(tag_descricao.equals_ignore_case(xml->getNodeName()))
						{
							xml->read();
							item.descricao = Conversoes::converteParaChar(xml->getNodeName());
						}
						//<preco>
						else if(tag_preco.equals_ignore_case(xml->getNodeName()))
						{
							xml->read();
							item.valor = Conversoes::converteParaInt(xml->getNodeName());
						}
						//<peso>
						else if(tag_peso.equals_ignore_case(xml->getNodeName()))
						{
							xml->read();
							item.peso = Conversoes::converteParaFloat (xml->getNodeName());													
						}
						//<id>
						else if(tag_id.equals_ignore_case(xml->getNodeName()))
						{
							xml->read();
							item.id = Conversoes::converteParaInt(xml->getNodeName());
						}
						//<tipo>
						else if(tag_tipo.equals_ignore_case(xml->getNodeName()))
						{
							xml->read();
							
							int tipo = Conversoes::converteParaInt(xml->getNodeName());
							if(tipo ==1)
								item.tipo = tipo_item::SAPATILHA;
							else if(tipo==2)
								item.tipo = tipo_item::CAPACETE;
							else if(tipo==3)
								item.tipo = tipo_item::CADEIRINHA;
							else if(tipo==4)
								item.tipo = tipo_item::MOSQUETAO;
							else if(tipo==5)
								item.tipo = tipo_item::CORDA;
							else if(tipo==6)
								item.tipo = tipo_item::MAGNESIO;
							else if(tipo==7)
								item.tipo = tipo_item::HALTER;
							else
								item.tipo = tipo_item::OUTROS;
						}
						break;
					case irr::io::EXML_NODE::EXN_ELEMENT_END:
						if(tag_item.equals_ignore_case(xml->getNodeName())){
							abriuItem=false;
							itens.push_back(item);
						}

					}
				}
			}
			
			
			
			break;

		case irr::io::EXML_NODE::EXN_ELEMENT_END:
			;
		}

	}


	return itens;
}