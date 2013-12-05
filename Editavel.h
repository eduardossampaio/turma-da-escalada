#pragma once
#include <iostream>

using namespace std;
class Editavel
{
public:
	Editavel(void);
	~Editavel(void);
	virtual std::string getTexto() =0;
	virtual void setTexto(std::string texto) =0;
	virtual void addTexto(std::string texto) =0;
	virtual void apagaTexto()=0;
	
};

