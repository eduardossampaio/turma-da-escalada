#pragma once
#include "tipos.h"
using namespace tipos;

class ItemDAO
{
public:
	ItemDAO(void);
	~ItemDAO(void);
	vector<tipos::Item_loja> getItens();
	tipos::Item_loja* getItem(int id);
private :
	std::string arquivo;

};

