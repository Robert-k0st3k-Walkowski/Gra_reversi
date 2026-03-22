#include"komputer.h"
#include<ctime>
#include<cstdlib>
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

komputer::komputer(stan s, Plansza* p) : gracz(s, p) // Konstruktor klasy "komputer" przypisuj¹ca planszê, po której gracz komputerowy bêdzie siê porusza³ i kolor jego pionków
{
	przeciwnikSymbol = (s == CZARNE) ? BIALE : CZARNE;
}

void komputer::ruch(Plansza* p) // Metoda g³ówna w tej klasie, odpowiadaj¹ca za ruch gracza komputerowego
{
	vector<pair<int, int>> pustePola = p->podajPustePola();

	cout << "Komputer wykonuje ruch.\n";

	srand(time(NULL));
	random_shuffle(pustePola.begin(), pustePola.end()); // Funkcja "random_shufle" sprawia, ¿e wartoœci w wektorze "pustePola" s¹ zamieniane losowo miejscami, co zmniejsza efekt "nietrafialnoœci" komputera

	for (auto& pole : pustePola)
	{
		int wspolX = pole.first;
		int wspolY = pole.second;

		if (czyLegalnyRuch(p, wspolX, wspolY, symbol))
		{
			p->UstawSymbol(wspolX, wspolY, symbol);
			p->odwrocSymbole(wspolX, wspolY, symbol);
			cout << "Komputer ustawil swoj symbol na polu: " << wspolX << ", " << wspolY << endl;
			return;
		}
	}

	cout << "Komputer nie znalazl legalnego ruchu.\n";
}

bool komputer::czyLegalnyRuch(Plansza* p, int x, int y, stan symbol) // Metoda wczeœniej u¿yta w klasie "czlowiek" sprawdzaj¹ca mo¿liwoœæ pójœcia w dany kierunek
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

bool komputer::sprawdzKierunek(Plansza* p, int x, int y, stan symbol, int dx, int dy) // Metoda równie¿ wykorzystana wczeœniej w klasie "czlowiek" odpowiadaj¹ca za sprawdzanie danego kierunku i jak daleko mo¿na iœæ w zadan¹ stronê
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