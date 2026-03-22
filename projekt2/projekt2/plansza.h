#pragma once
#include<iostream>
#include<vector>

// Poni¿sza deklaracja wszystkich pól oraz metod dla klasy "Plansza"

using namespace std;

// Struktura "enum", która reprezentuje odpowiednie pola na planszy, za pomoc¹ cyfr

enum stan
{
	CZARNE,
	BIALE,
	PUSTE,
	GRANICA,
};

class Plansza
{
private:
	int rozmiar = 0;
	stan** tab = nullptr;
public:
	Plansza(int roz, bool inicjalizacja);
	~Plansza();
	int PobierzRozmiar() const;
	void Wypisz() const;
	stan Pozycja(int x, int y);
	void UstawSymbol(int x, int y, stan s);
	int CzyKoniecGry(Plansza* p);
	bool CzyWygrana(stan s, int x, int y);
	bool czyLegalnyRuch(Plansza* p, int x, int y, stan symbol);
	bool sprawdzKierunek(Plansza* p, int x, int y, stan symbol, int dx, int dy);
	void odwrocKierunek(int x, int y, stan s, int dx, int dy);
	void odwrocSymbole(int x, int y, stan s);
	vector<pair<int,int>> podajPustePola();
	void ZapiszDoPliku(const string& nazwaPliku);
	void WczytajZPliku(const string& nazwaPliku);
};