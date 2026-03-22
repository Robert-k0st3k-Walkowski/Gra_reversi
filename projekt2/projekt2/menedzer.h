#pragma once
#include"plansza.h"
#include"czlowiek.h"
#include"komputer.h"
#include"gracz.h"

// Deklaracja klasy "menedzer" oraz potrzebnych na jej potrzeby pól

class menedzer
{
private:
	Plansza* p;
	gracz* g1;
	gracz* g2;
public:
	menedzer();
	void gra();
	void parametryGry();
};