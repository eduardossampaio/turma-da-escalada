#pragma once
class Focavel
{
public:
	Focavel(void);
	~Focavel(void);
	void ativarFoco();
	void desativarFoco();
	bool temFoco();


private :
	bool focus;
};

