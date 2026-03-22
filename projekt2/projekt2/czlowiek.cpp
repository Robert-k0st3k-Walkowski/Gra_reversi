#include"czlowiek.h"
#include"gracz.h"
#include"plansza.h"
#include<iostream>

using namespace std;

czlowiek::czlowiek(stan s, Plansza* p) : gracz(s, p) {}; // Konstruktor dla klasy "czlowiek", która definiuje symbol dla gracza ludzkiego oraz planszê, na której bêdzie umieszcza³ swoje symbole

void czlowiek::ruch(Plansza* p) // Metoda g³ówna w klasie "czlowiek", która odpowiada za ruch gracza
{
	int x, y;

	while (true)
	{
		cout << "Podaj wartosc \'x\' (wiersza), gdzie chcesz wstawic symbol (notacja tablicowa, czyli od 0):";
		cin >> x;
		cout << endl;
		cout << "Podaj wartosc \'y\' (kolumny), gdzie chcesz wstawic symbol (notacja tablicowa, czyli od 0):";
		cin >> y;
		cout << endl;

		if (p->Pozycja(x, y) == PUSTE)
		{
			if (czyLegalnyRuch(p, x, y, symbol))
			{
				p->UstawSymbol(x, y, symbol);
				p->odwrocSymbole(x, y, symbol);
				break;
			}
			else
			{
				cout << endl <<"Nielegalny ruch!" << endl;
			}
		}
		else
		{
			cout <<"To pole jest zajete lub niedostepne (poza zakresem planszy)!" << endl << endl;
		}
	}
}

bool czlowiek::czyLegalnyRuch(Plansza* p, int x, int y, stan symbol) // Metoda "czyLegalnyRuch", sprawdzaj¹ca czy gracz mo¿e wykonaæ dany ruch, zgodnie z zasadami gry w "Reversi"
{
	return sprawdzKierunek(p, x, y, symbol, 1, 0) || // w prawo
		sprawdzKierunek(p, x, y, symbol, -1, 0) || // w lewo
		sprawdzKierunek(p, x, y, symbol, 0, 1) || // w dó³
		sprawdzKierunek(p, x, y, symbol, 0, -1) || // w górê
		sprawdzKierunek(p, x, y, symbol, 1, 1) || // na ukos w prawo w dó³
		sprawdzKierunek(p, x, y, symbol, -1, -1) || // na ukos w lewo w górê
		sprawdzKierunek(p, x, y, symbol, 1, -1) || // na ukos w prawo w górê
		sprawdzKierunek(p, x, y, symbol, -1, 1); // na ukos w lewo w dó³
}

bool czlowiek::sprawdzKierunek(Plansza* p, int x, int y, stan symbol, int dx, int dy) // Metoda sprawdzaj¹ca mo¿liwoœci pójœcia w dany kierunek
{
	int i = x + dx;
	int j = y + dy;
	bool przeciwnikZnaleziony = false;

	while (i >= 0 && i < p->PobierzRozmiar() && j >= 0 && j < p->PobierzRozmiar())
	{
		if (p->Pozycja(i, j) == PUSTE || p->Pozycja(i, j) == GRANICA)
		{
			return false;
		}

		if (p->Pozycja(i, j) != symbol)
		{
			przeciwnikZnaleziony = true;
		}
		else
		{
			return przeciwnikZnaleziony;
		}
		i += dx;
		j += dy;
	}

	return false;
}