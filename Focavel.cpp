#include "stdafx.h"
#include "Focavel.h"


Focavel::Focavel(void)
{
	Focavel::focus = true;
}


Focavel::~Focavel(void)
{
}
bool Focavel::temFoco()
{
	return Focavel::focus;
}

void Focavel::ativarFoco()
{
	Focavel::focus = true;
}
void Focavel::desativarFoco()
{
	Focavel::focus = false;
}