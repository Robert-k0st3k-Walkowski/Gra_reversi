#pragma once
#include"gracz.h"
#include"plansza.h"

// Deklaracja klasy "komputer" oraz pól potrzebnych do jej dzia³ania (dziedziczy publicznie po klasie "gracz")

class komputer : public gracz
{
private:
	stan przeciwnikSymbol;

public:
	komputer(stan s, Plansza* p);
	void ruch(Plansza* p) override;
	bool czyLegalnyRuch(Plansza* p, int x, int y, stan symbol);
	bool sprawdzKierunek(Plansza* p, int x, int y, stan symbol, int dx, int dy);
};