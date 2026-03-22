#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include"plansza.h"
#include"gracz.h"
#include"czlowiek.h"

Plansza::Plansza(int roz, bool inicjalizacja) // Konstruktor planszy, który przyjmuje 2 argumenty: rozmiar planszy oraz czy j¹ inicjalizowaæ (zrobione na potrzeby metody WczytajStanGry)
{

	// Je¿eli inicjalizacja = "true" <- inicjalizuje podstawow¹ wersjê planszy

	if (inicjalizacja)
	{
		if (roz % 2 != 0 || roz <= 4)
		{
			return;
		}

		rozmiar = roz;
		tab = new stan * [rozmiar];
		for (int i = 0; i < rozmiar; i++)
		{
			tab[i] = new stan[rozmiar];
			for (int j = 0; j < rozmiar; j++)
			{
				if (i == 0 || i == rozmiar - 1)
				{
					tab[i][j] = GRANICA;
				}
				else if (((i > 0) && (i < rozmiar - 1)) && ((j == 0) || (j == rozmiar - 1)))
				{
					tab[i][j] = GRANICA;
				}
				else
				{
					tab[i][j] = PUSTE;
				}
			}
		}

		// Domyœlnie, na pocz¹tku gry ustawione s¹ 4 pionki, po 2 na ukos: 2 bia³e oraz 2 czarne

		tab[rozmiar / 2 - 1][rozmiar / 2 - 1] = BIALE;
		tab[rozmiar / 2 - 1][rozmiar / 2] = CZARNE;
		tab[rozmiar / 2][rozmiar / 2 - 1] = CZARNE;
		tab[rozmiar / 2][rozmiar / 2] = BIALE;
	}
}

Plansza::~Plansza() // Destruktor planszy
{
	for (int i = 0; i < rozmiar; i++)
	{
		delete[] tab[i];
	}

	delete[] tab;
}

int Plansza::PobierzRozmiar() const // Metoda potrzebna do pobierania rozmiaru planszy, gdy¿ pole "rozmiar" dla planszy jest domyœlnie prywatne
{
	if (rozmiar > 0)
	{
		return this->rozmiar;
	}
	else
	{
		return 0;
	}
}

stan Plansza::Pozycja(int x, int y) // Metoda zwracaj¹ca stan pola pod zadanym "x" oraz "y" planszy
{
	if (((x >= rozmiar) || (y >= rozmiar)) || ((x < 0) || (y < 0)))
	{
		return GRANICA;
	}

	return this->tab[x][y];
}

void Plansza::UstawSymbol(int x, int y, stan s) // Metoda potrzebna do ustawiania symbolu gracza na zadanych wspó³rzêdnych "x" oraz "y"
{
	if (tab[x][y] == PUSTE)
	{
		this->tab[x][y] = s;
		odwrocSymbole(x, y, s);
	}
	else
	{
		return;
	}
}

void Plansza::odwrocSymbole(int x, int y, stan s) // Metoda dla planszy, która sprawdza, w którym kierunku maj¹ byæ odwrócone symbole
{
	odwrocKierunek(x, y, s, 1, 0); // w prawo
	odwrocKierunek(x, y, s, -1, 0); // w lewo
	odwrocKierunek(x, y, s, 0, 1); // w dó³
	odwrocKierunek(x, y, s, 0, -1); // w górê
	odwrocKierunek(x, y, s, 1, 1); // na ukos w prawo w dó³
	odwrocKierunek(x, y, s, -1, -1); // na ukos w lewo w górê
	odwrocKierunek(x, y, s, 1, -1); // na ukos w prawo w górê
	odwrocKierunek(x, y, s, -1, 1); // na ukos w lewo w dó³
}

void Plansza::odwrocKierunek(int x, int y, stan s, int dx, int dy) // Metoda, która domyœlnie idzie w danym kierunku i zmienia ka¿de pole przeciwnika, dopóki nie natrafi ponownie na symbol danego gracza
{
	int i = x + dx;
	int j = y + dy;

	pair<int, int> innySymbol;
	vector<pair<int, int>> doOdwrocenia;

	while (i >= 0 && i < rozmiar && j >= 0 && j < rozmiar)
	{
		if (tab[i][j] == PUSTE || tab[i][j] == GRANICA)
		{
			return;
		}
		if (tab[i][j] != s)
		{
			innySymbol.first = i;
			innySymbol.second = j;

			doOdwrocenia.push_back(innySymbol);
		}
		else
		{
			for (pair<int, int> innySymbol : doOdwrocenia)
			{
				tab[innySymbol.first][innySymbol.second] = s;
			}
			return;
		}

		i += dx;
		j += dy;
	}
}

void Plansza::Wypisz() const // Prosta metoda wypisuj¹ca na ekran planszê o zadanym rozmiarze i odpowiednio zmieniaj¹c wartoœci liczbowe na znaki
{
	cout << "  ";

	for (int j = 0; j < rozmiar; j++)
	{
			cout << j;
	}
	cout << endl;

	for (int i = 0; i < rozmiar; i++)
	{
		cout << i << " ";
		for (int j = 0; j < rozmiar; j++)
		{
			switch (this->tab[i][j])
			{
			case GRANICA:
				cout << "#";
				break;
			case CZARNE:
				cout << "C";
				break;
			case BIALE:
				cout << "B";
				break;
			case PUSTE:
				cout << "-";
				break;
			default:
				break;
			}
		}
		cout << endl;
	}
}

int Plansza::CzyKoniecGry(Plansza* p) // Metoda sprawdzaj¹ca, czy nastêpuje koniec gry po ruchu wykonanym przez któregoœ z graczy
{
	bool pelnaPlansza = true;
	bool gracz1MozeRuch = false;
	bool gracz2MozeRuch = false;

	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			if (tab[i][j] == PUSTE)
			{
				pelnaPlansza = false;
				if (!gracz1MozeRuch && czyLegalnyRuch(p, i, j, CZARNE))
				{
					gracz1MozeRuch = true;
				}
				if (!gracz2MozeRuch && czyLegalnyRuch(p, i, j, BIALE))
				{
					gracz2MozeRuch = true;
				}
			}
		}
	}

	if (pelnaPlansza || (!gracz1MozeRuch && !gracz2MozeRuch))
	{
		return 1;
	}

	return 0;
}

bool Plansza::CzyWygrana(stan symbol, int x, int y) // Metoda zliczaj¹ca iloœæ pól bia³ych oraz czarnych i decyduj¹ca o tym, który z graczy zwyciê¿y³
{
	int liczbaCzarne = 0;
	int liczbaBiale = 0;

	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			if (tab[i][j] == CZARNE)
			{
				liczbaCzarne++;
			}
			else if (tab[i][j] == BIALE)
			{
				liczbaBiale++;
			}
		}
	}

		if (liczbaCzarne > liczbaBiale)
		{
			return symbol == CZARNE;
		}
		else if (liczbaBiale > liczbaCzarne)
		{
			return symbol == BIALE;
		}
		else
		{
			return false;
		}

}

bool Plansza::czyLegalnyRuch(Plansza* p, int x, int y, stan symbol) // Metoda sprawdzaj¹ca mo¿liwoœæ wykonania ruchu, wed³ug zasad gry w "Reversi"
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

bool Plansza::sprawdzKierunek(Plansza* p, int x, int y, stan symbol, int dx, int dy) // Metoda sprawdzaj¹ca, czy zosta³ znaleziony w danym kierunku symbol przeciwnika i ile tych symboli jest, tyle razy pêtla siê wykona
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

vector<pair<int, int>> Plansza::podajPustePola()
{
	pair<int, int> puste;
	vector<pair<int, int>> wektorPustych;
	vector<pair<int, int>> wynikowy = wektorPustych;

	for (int i = 0; i < PobierzRozmiar(); i++)
	{
		for (int j = 0; j < PobierzRozmiar(); j++)
		{
			if (tab[i][j] == PUSTE)
			{
				puste.first = i;
				puste.second = j;
				wynikowy.insert(wynikowy.end(), puste);
			}
		}
	}

	return wynikowy;
}

void Plansza::ZapiszDoPliku(const string& nazwaPliku) // Metoda zapisuj¹ca dany stan planszy do pliku
{
	//W pliku mamy zapisana plansze za pomoca liczb, gdzie: liczba u gory - rozmiar planszy (wliczajac w to granice), 3 - GRANICA, 2 - PUSTE, 1 - BIALE, 0 - CZARNE

	ofstream plik(nazwaPliku);

	if (!plik.is_open())
	{
		cerr << "Nie mo¿na otworzyæ pliku do zapisu." << endl;
		return;
	}

	plik << rozmiar << endl;
	
	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			plik << tab[i][j] << " ";
		}
		plik << endl;
	}

	plik.close();
}

void Plansza::WczytajZPliku(const string& nazwaPliku) // Metoda pozwalaj¹ca natomiast wczytaæ stan gry z pliku
{

	ifstream plik(nazwaPliku);
	if (!plik.is_open())
	{
		cerr << "Nie mo¿na otworzyæ pliku: " << nazwaPliku << endl;
		return;
	}

	plik >> rozmiar;

	if (tab != nullptr)
	{
		for (int i = 0; i < rozmiar; i++)
		{
			delete[] tab[i];
		}
		delete[] tab;
	}

	tab = new stan * [rozmiar];
	for (int i = 0; i < rozmiar; i++)
	{
		tab[i] = new stan[rozmiar];
	}

	int temp;
	for (int i = 0; i < rozmiar; i++)
	{
		for (int j = 0; j < rozmiar; j++)
		{
			plik >> temp;
			tab[i][j] = static_cast<stan>(temp);
		}
	}

	plik.close();
}


