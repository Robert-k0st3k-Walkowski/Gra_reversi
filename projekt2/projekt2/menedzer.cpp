#include<iostream>
#include<iomanip>
#include<chrono>
#include<thread>
#include<fstream>
#include<string>
#include"menedzer.h"
#include"gracz.h"
#include"czlowiek.h"
#include"komputer.h"
#include"plansza.h"

using namespace std;

menedzer::menedzer() // Konstruktor g³ównego mened¿era gry
{
	p = NULL;
	g1 = NULL;
	g2 = NULL;
}

void menedzer::parametryGry() // Metoda w klasie "menedzer", która odpawia za odpowiednie ustawienie trybu gry oraz rozmiaru planszy
{
	int opcja = 0, opcja2 = 0;;
	int rozmiar = 0;

	cout << "-----------WITAJ W GRZE W REVERSI!!!-----------" << endl << endl;
	cout << "-----DOSTEPNE OPCJE GRY:-----" << endl;
	cout << "1. Rozgrywka: Czlowiek vs Czlowiek" << endl;
	cout << "2. Rozgrywka: Czlowiek vs Komputer" << endl;
	cout << "3. Rozgrywka: Komputer vs Komputer" << endl;
	cout << "4. Wczytaj stan gry z pliku" << endl << endl;
	cout << "Wybierz dostepna z menu opcje: ";
	cin >> opcja;
	cout << endl;

	switch (opcja)
	{
	case 1:

		cout << "Podaj rowniez rozmiar planszy do gry (minimum 6): ";
		cin >> rozmiar;

		if (rozmiar < 6)
		{
			cout << "Rozmiar planszy podany przez ciebie jest za maly. KONIEC GRY!" << endl;
			exit(0);
		}

		p = new Plansza(rozmiar, true);

		g1 = new czlowiek(CZARNE, p);
		g2 = new czlowiek(BIALE, p);

		break;
	case 2:

		cout << "Podaj rowniez rozmiar planszy do gry (minimum 6): ";
		cin >> rozmiar;

		if (rozmiar < 6)
		{
			cout << "Rozmiar planszy podany przez ciebie jest za maly. KONIEC GRY!" << endl;
			exit(0);
		}

		p = new Plansza(rozmiar, true);

		g1 = new czlowiek(CZARNE, p);
		g2 = new komputer(BIALE, p);

		break;
	case 3:

		cout << "Podaj rowniez rozmiar planszy do gry (minimum 6): ";
		cin >> rozmiar;

		if (rozmiar < 6)
		{
			cout << "Rozmiar planszy podany przez ciebie jest za maly. KONIEC GRY!" << endl;
			exit(0);
		}

		p = new Plansza(rozmiar, true);

		g1 = new komputer(CZARNE, p);
		g2 = new komputer(BIALE, p);

		break;
	case 4:
		p = new Plansza(0, false);

		p->WczytajZPliku("zapisGry.txt");

		cout << "-----------WITAJ W GRZE W REVERSI!!! (po wczytaniu stanu gry z pliku)-----------" << endl << endl;
		cout << "-----DOSTEPNE OPCJE GRY:-----" << endl;
		cout << "1. Rozgrywka: Czlowiek vs Czlowiek" << endl;
		cout << "2. Rozgrywka: Czlowiek vs Komputer" << endl;
		cout << "3. Rozgrywka: Komputer vs Komputer" << endl;
		cout << "Wybierz dostepna z menu opcje: ";
		cin >> opcja2;
		cout << endl;

		switch (opcja2)
		{
			case 1:
					g1 = new czlowiek(CZARNE, p);
					g2 = new czlowiek(BIALE, p);
				break;
			case 2:
					g1 = new czlowiek(CZARNE, p);
					g2 = new komputer(BIALE, p);
				break;
			case 3:
					g1 = new komputer(CZARNE, p);
					g2 = new komputer(BIALE, p);
				break;
			default:
				cout << "Nie ma takiej opcji gry.";
				exit(3);
				break;
		}
		break;
	default:
		cout << "Nie ma takiej opcji gry.";
		exit(5);
		return;
		break;
	}
}

void menedzer::gra() // Metoda g³ówna klasy "menedzer", która odpowiada za g³ówny przebieg rozgrywki
{
	int koniec = 0;
	int wybor = 0;
	int zapis = 0;

	menedzer::parametryGry();

	cout << "Rozpoczynamy gre!" << endl;

	while (koniec != 1)
	{
		cout << endl;
		p->Wypisz();
		cout << endl;
		_Thrd_sleep_for(2000);

		if (typeid(*g1).name() == typeid(czlowiek).name())
		{
			cout << "Czy \'gracz 1\' chcesz zapisac stan gry? (1 - tak, inna liczba - nie): ";
			cin >> zapis;
		}

		if (zapis == 1)
		{
			p->ZapiszDoPliku("zapisGry.txt");
			break;
		}
		else
		{
			cout << endl;
			g1->ruch(p);
		}

		koniec = p->CzyKoniecGry(p);
		if (koniec == 1)
		{
			cout << endl;
			p->Wypisz();
			cout << endl;

			if (p->CzyWygrana(CZARNE, 0, 0))
			{
				cout << "Koniec gry! Wygrywa gracz 1, gratulacje!" << endl;
			}
			else if (p->CzyWygrana(BIALE, 0, 0))
			{
				cout << "Koniec gry! Wygrywa gracz 2, gratulacje!" << endl;
			}
			else
			{
				cout << "Koniec gry! Remis!" << endl;
			}
			cout << endl;
			break;
		}

		cout << endl;
		p->Wypisz();
		cout << endl;
		_Thrd_sleep_for(2000);

		if (typeid(*g2).name() == typeid(czlowiek).name())
		{
			cout << "Czy \'gracz 2\' chcesz zapisac stan gry? (1 - tak, inna liczba - nie): ";
			cin >> zapis;
		}

		if (zapis == 1)
		{
			p->ZapiszDoPliku("zapisGry.txt");
			break;
		}
		else
		{
			cout << endl;
			g2->ruch(p);
		}

		koniec = p->CzyKoniecGry(p);
		if (koniec == 1)
		{
			cout << endl;
			p->Wypisz();
			cout << endl;

			if (p->CzyWygrana(CZARNE, 0, 0))
			{
				cout << "Koniec gry! Wygrywa gracz 1, gratulacje!" << endl;
			}
			else if (p->CzyWygrana(BIALE, 0, 0))
			{
				cout << "Koniec gry! Wygrywa gracz 2, gratulacje!" << endl;
			}
			else
			{
				cout << "Koniec gry! Remis!" << endl;
			}
			cout << endl;
			break;
		}
	}

	if (p != nullptr)
	{
		p->ZapiszDoPliku("zapisGry.txt");
	}

	delete g1;
	delete g2;
	delete p;
	p = nullptr;
	g1 = nullptr;
	g2 = nullptr;

	cout << "Czy chcesz rozpoczac kolejna rozgrywke? (1 <- tak, Cokolwiek innego <- nie): ";
	cin >> wybor;

	if (wybor == 1)
	{
		gra();
	}
	else
	{
		return;
	}

	return;
}