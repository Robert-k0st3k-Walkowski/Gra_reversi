#pragma once
#include"plansza.h"

// Deklaracja klasy "gracz" oraz jej pól, które s¹ potrzebne do prawid³owego jej funkcjonowania

class gracz
{
protected:
	stan symbol;
	Plansza* plansza;
public:
	gracz(stan s, Plansza* p);
	virtual void ruch(Plansza* p);
	stan PobierzSymbol();
	Plansza* PobierzPlansze();

};