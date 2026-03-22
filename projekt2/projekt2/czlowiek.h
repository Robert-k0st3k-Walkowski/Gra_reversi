#pragma once
#include"gracz.h"
#include"plansza.h"

// Deklaracja klasy "czlowiek" oraz potrzebnych do jej prawid³owego dzia³ania pól (dziedziczy publicznie po klasie "gracz")

class czlowiek : public gracz
{
public:
	czlowiek(stan s, Plansza* p);
	void ruch(Plansza* p) override;
	bool czyLegalnyRuch(Plansza* p, int x, int y, stan symbol);
	bool sprawdzKierunek(Plansza* p, int x, int y, stan symbol, int dx, int dy);
};