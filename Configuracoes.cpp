#include "stdafx.h"
#include "Configuracoes.h"
#include "Conversoes.h"
#include "Globais.h"


Configuracoes::Configuracoes(void)
{
	Configuracoes::arq			= "configuracoes/config.xml";
	Configuracoes::metadata		= "configuracoes/metadata.xml";

	device = irr::createDevice(irr::video::EDT_NULL);

}


Configuracoes::~Configuracoes(void)
{
}

void Configuracoes::salvarConfiguracoes(tipos::configuracoes config)
{
	irr::io::IXMLWriter * writer = device->getFileSystem()->createXMLWriter(Configuracoes::arq.c_str());
	writer->writeXMLHeader();
	writer->writeElement(L"configuracoes");
	writer->writeLineBreak();
	writer->writeElement(L"configuracao");
	writer->writeLineBreak();

	writer->writeElement(L"resolucao");
	writer->writeLineBreak();
	
	writer->writeElement(L"largura");

	
	
	wchar_t a [12];
	_itow_s(config.resolucao.x,a,sizeof(a)/2,10);
	

	writer->writeText( a );

	
	writer->writeClosingTag(L"largura");
	
	writer->writeLineBreak();

	writer->writeElement(L"altura");

	 wchar_t w [12];
	_itow_s(config.resolucao.y,w,sizeof(w)/2,10);

	writer->writeText( w );

	writer->writeClosingTag(L"altura");
	writer->writeLineBreak();
	writer->writeClosingTag(L"resolucao");
	writer->writeLineBreak();

	writer->writeElement(L"cor");


	wchar_t c [12];
	_itow_s(config.bitsCor,c,sizeof(c)/2,10);
	writer->writeText( c );


	writer->writeClosingTag(L"cor");
	writer->writeLineBreak();

	writer->writeElement(L"fullscreen");


	if(config.fullscreen)
		writer->writeText( L"true");
	else
		writer->writeText( L"false");

	


	writer->writeClosingTag(L"fullscreen");
	writer->writeLineBreak();

	writer->writeElement(L"mao");
	
	if(config.mao==tipos::Mao::DIREITA)
		writer->writeText(L"0");
	else
		writer->writeText(L"1");
	writer->writeClosingTag(L"mao");
	writer->writeLineBreak();

	writer->writeClosingTag(L"configuracao");
	writer->writeLineBreak();
	writer->writeClosingTag(L"configuracoes");
	writer->writeLineBreak();

	writer->drop();



}

tipos::configuracoes Configuracoes::carregarConfigucacoes()
{
	irr::io::IXMLReader *xml = device->getFileSystem()->createXMLReader(Configuracoes::arq.c_str());
	tipos::configuracoes config = tipos::configuracoes();
	
	irr::core::stringw tagConfiguracao	=L"configuracao";
	irr::core::stringw tagAltura		=L"altura";
	irr::core::stringw tagLargura		=L"largura";
	irr::core::stringw tagCor			=L"cor";
	irr::core::stringw tagFullScreen	=L"fullscreen";
	irr::core::stringw tagMao			=L"mao";
	while(xml->read())
	{
		switch (xml->getNodeType())
		{
		case irr::io::EXML_NODE::EXN_ELEMENT:
			if(tagConfiguracao.equals_ignore_case(xml->getNodeName()))
			{
				bool abriuConfiguracao=true;
				while(abriuConfiguracao && xml->read())
				{
					switch (xml->getNodeType())
					{
						case irr::io::EXML_NODE::EXN_ELEMENT:
							if(tagAltura.equals_ignore_case(xml->getNodeName()))
							{
								while(xml->read() && xml->getNodeType() != irr::io::EXML_NODE::EXN_ELEMENT_END)
								{
					
									const wchar_t * nome = xml->getNodeName();															
									config.resolucao.y = Conversoes::converteParaInt(nome);
					
					

								}
							}
							else if(tagLargura.equals_ignore_case(xml->getNodeName()))
							{
								while(xml->read() && xml->getNodeType() != irr::io::EXML_NODE::EXN_ELEMENT_END)
								{				
									const wchar_t * nome = xml->getNodeName();					
									config.resolucao.x = Conversoes::converteParaInt(nome);					
					
								}
							}
							else if(tagCor.equals_ignore_case(xml->getNodeName()))
							{
								while(xml->read() && xml->getNodeType() != irr::io::EXML_NODE::EXN_ELEMENT_END)
								{										
									const wchar_t * nome = xml->getNodeName();									
									config.bitsCor = Conversoes::converteParaInt(nome);					
								}
							}
							else if(tagFullScreen.equals_ignore_case(xml->getNodeName()))
							{
								while(xml->read() && xml->getNodeType() != irr::io::EXML_NODE::EXN_ELEMENT_END)
								{										
									const wchar_t * nome = xml->getNodeName();
									config.fullscreen = Conversoes::converteParaBool(nome);															
								}
							}
							else if(tagMao.equals_ignore_case(xml->getNodeName()))
							{
								while(xml->read() && xml->getNodeType() != irr::io::EXML_NODE::EXN_ELEMENT_END)
								{										
									const wchar_t * nome = xml->getNodeName();
									irr::core::stringw s = nome;
									if(s.equals_ignore_case(L"0"))
										config.mao = tipos::Mao::DIREITA;
									else
										config.mao = tipos::Mao::ESQUERDA;
								}
							}
							break;
						case irr::io::EXML_NODE::EXN_ELEMENT_END:
							if(tagConfiguracao.equals_ignore_case(xml->getNodeName()))
							{
								abriuConfiguracao =false;
							}
								
					}
				}
			}
			break;			

		}
		irr::io::EXML_NODE node =  xml->getNodeType();
		const wchar_t * nome = xml->getNodeName();
		int i =0;
		i++;
	}
	printf("%f X %f %d bits %d\n",config.resolucao.x,config.resolucao.y,config.bitsCor,config.fullscreen);
	xml->drop();

	return config;
}

vector<tipos::Vetor> Configuracoes::carregarResolucoes()
{
	vector<tipos::Vetor> resolucoes;

	irr::core::stringw tagAltura		=L"altura";
	irr::core::stringw tagLargura		=L"largura";
	irr::core::stringw tagResolucoes	=L"resolucoes";
	irr::core::stringw tagResolucao		=L"resolucao";

	irr::io::IXMLReader *xml = device->getFileSystem()->createXMLReader(Configuracoes::metadata.c_str());

	while(xml->read())
	{
		switch (xml->getNodeType())
		{
		case irr::io::EXML_NODE::EXN_ELEMENT:
			if(tagResolucoes.equals_ignore_case(xml->getNodeName()))
			{
				bool abriuResolucoes = true;
				//<resolucoes>
				while(abriuResolucoes && xml->read())
				{
					switch (xml->getNodeType())
					{
						case irr::io::EXML_NODE::EXN_ELEMENT:
							//<resolucao>
							
							if(tagResolucao.equals_ignore_case(xml->getNodeName()))
							{
								bool abriuResolucao=true;
								printf("<resolucao>\n");
								tipos::Vetor res = tipos::Vetor();
								while(abriuResolucao && xml->read())
								{
									switch (xml->getNodeType())
									{									
									case irr::io::EXML_NODE::EXN_ELEMENT:
										if(tagAltura.equals_ignore_case(xml->getNodeName()))
										{
											while(xml->read() && xml->getNodeType() != irr::io::EXML_NODE::EXN_ELEMENT_END)
											{					
												const wchar_t * nome = xml->getNodeName();															
												res.y = Conversoes::converteParaInt(nome);		
												
											}
										}
										else if(tagLargura.equals_ignore_case(xml->getNodeName()))
										{
											while(xml->read() && xml->getNodeType() != irr::io::EXML_NODE::EXN_ELEMENT_END)
											{				
												const wchar_t * nome = xml->getNodeName();					
												res.x = Conversoes::converteParaInt(nome);										
											}
										}
										break;
									case irr::io::EXML_NODE::EXN_ELEMENT_END:
										if(tagResolucao.equals_ignore_case(xml->getNodeName()))
										{
											printf("</resolucao>\n");
											resolucoes.push_back(res);
											abriuResolucao = false;
										}

									}
								}

							}
							break;
						case irr::io::EXML_NODE::EXN_ELEMENT_END:
							if(tagResolucoes.equals_ignore_case(xml->getNodeName()))
								abriuResolucoes=false;
					}

				}

			}
			break;
		}
	}
	xml->drop();


	return resolucoes;

}