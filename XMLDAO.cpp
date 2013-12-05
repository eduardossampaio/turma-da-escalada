#include "stdafx.h"
#include "XMLDAO.h"
#include "Conversoes.h"
#include "Globais.h"
XMLDAO::XMLDAO(void)
{
}


XMLDAO::~XMLDAO(void)
{
}

tipos::Vetor XMLDAO::lerTagComVetor(stringw tag,irr::io::IXMLReader *xml)
{
	bool abriuTag = true;
	printf("<%s> \n",tag.c_str());
	
	stringw tag_x				=	"x";
	stringw tag_y				=	"y";
	stringw tag_z				=	"z";
	tipos::Vetor vetor;
	while(abriuTag && xml->read())
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
			break;
		case EXN_ELEMENT_END:
			if(tag.equals_ignore_case(xml->getNodeName())){
			
				abriuTag=false;
				printf("</%s>\n",tag.c_str());
				
			}		
			break;
		}
	}
	return vetor;
}

std::string XMLDAO::lerString(irr::io::IXMLReader *xml)
{
	xml->read();
	const wchar_t * temp =  xml->getNodeName() ;
	std::string s = Conversoes::converteParaChar(temp);
	return s;

}

irr::IrrlichtDevice * XMLDAO::getDevice()
{
	return Globais::getIrrDevice();

}