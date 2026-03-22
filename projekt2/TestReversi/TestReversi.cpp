#include "pch.h"
#include "CppUnitTest.h"
#include"../projekt2/czlowiek.h"
#include"../projekt2/plansza.h"
#include"../projekt2/komputer.h"
#include"../projekt2/gracz.h"
#include"../projekt2/menedzer.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestReversi
{
	TEST_CLASS(TestReversi)
	{
	public:
		
		TEST_METHOD(KONSTRUKTOR_PLANSZY_oraz_METODA_POBIERZ_ROZMIAR)
		{
			Plansza rozgrywka(6, true);
			int rozmiar = rozgrywka.PobierzRozmiar();
			Plansza rozgrywka2(10, true);
			int rozmiar2 = rozgrywka2.PobierzRozmiar();
			Plansza rozgrywka3(1000, true);
			int rozmiar3 = rozgrywka3.PobierzRozmiar();
			Plansza rozgrywka5(8, true);
			int rozmiar5 = rozgrywka5.PobierzRozmiar();
			Plansza rozgrywka6(888, true);
			int rozmiar6 = rozgrywka6.PobierzRozmiar();
			Plansza rozgrywka7(56, true);
			int rozmiar7 = rozgrywka7.PobierzRozmiar();

			Assert::IsTrue(rozmiar == 6);
			Assert::IsTrue(rozmiar2 == 10);
			Assert::IsFalse(rozmiar3 == 1001);
			Assert::IsTrue(rozmiar5 > 0);
			Assert::IsTrue(rozmiar6 == 888);
			Assert::IsFalse(rozmiar7 < 56);

			try
			{
				Plansza rozgrywka4(999, true);
			}
			catch (const std::invalid_argument&)
			{
				Assert::IsTrue(true);
			}

			try
			{
				Plansza rozgrywka8(0, false);
			}
			catch (const std::invalid_argument&)
			{
				Assert::IsTrue(true);
			}

			try
			{
				Plansza rozgrywka9(-10, true);
			}
			catch (const std::invalid_argument&)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(METODA_POZYCJA)
		{
			Plansza rozgrywka(6, true);
			Plansza rozgrywka2(10, true);
			Plansza rozgrywka3(1000, true);
			Plansza rozgrywka4(998, true);
			Plansza rozgrywka5(8, true);
			Plansza rozgrywka6(888, true);
			Plansza rozgrywka7(56, true);

			stan pole = rozgrywka.Pozycja(2, 1);
			stan pole2 = rozgrywka2.Pozycja(5, 5);
			stan pole3 = rozgrywka3.Pozycja(123, 321);
			stan pole4 = rozgrywka4.Pozycja(5, 2);
			stan pole5 = rozgrywka5.Pozycja(1, 1);
			stan pole6 = rozgrywka6.Pozycja(444, 444);
			stan pole7 = rozgrywka7.Pozycja(45, 12);
			stan pole8 = rozgrywka2.Pozycja(5, 4);

			Assert::IsTrue(pole == 2);
			Assert::IsTrue(pole2 != 3);
			Assert::IsFalse(pole3 == 1);
			Assert::IsTrue(pole4 == 2);
			Assert::IsFalse(pole5 == 1);
			Assert::IsFalse(pole6 == 3);
			Assert::IsFalse(pole7 == 0);
			Assert::IsTrue(pole8 != 3);

			try
			{
				Plansza rozgrywka8(10, true);
				stan pole8 = rozgrywka8.Pozycja(10, 10);
			}
			catch (const std::invalid_argument&)
			{
				Assert::IsTrue(true);
			}

			try
			{
				Plansza rozgrywka9(30, true);
				stan pole9 = rozgrywka9.Pozycja(-2, -5);
			}
			catch (const std::invalid_argument&)
			{
				Assert::IsTrue(true);
			}

			try
			{
				Plansza rozgrywka10(122, true);
				stan pole10 = rozgrywka10.Pozycja(-35, 52);
			}
			catch (const std::invalid_argument&)
			{
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(METODA_USTAW_POLE)
		{
			Plansza rozgrywka(6, true);
			Plansza rozgrywka2(10, true);
			Plansza rozgrywka3(1000, true);
			Plansza rozgrywka4(998, true);
			Plansza rozgrywka5(8, true);
			Plansza rozgrywka6(888, true);
			Plansza rozgrywka7(56, true);

			rozgrywka.UstawSymbol(1, 1, CZARNE);
			rozgrywka2.UstawSymbol(6, 5, BIALE);
			rozgrywka3.UstawSymbol(523, 160, CZARNE);
			rozgrywka4.UstawSymbol(1, 1, BIALE);
			rozgrywka5.UstawSymbol(1, 1, CZARNE);
			rozgrywka6.UstawSymbol(444, 80, BIALE);
			rozgrywka7.UstawSymbol(20, 20, CZARNE);

			Assert::IsTrue(rozgrywka.Pozycja(1, 1) == CZARNE);
			Assert::IsTrue(rozgrywka2.Pozycja(6, 5) == BIALE);
			Assert::IsTrue(rozgrywka3.Pozycja(523, 160) == CZARNE);
			Assert::IsTrue(rozgrywka4.Pozycja(1, 1) == BIALE);
			Assert::IsFalse(rozgrywka5.Pozycja(1, 1) == BIALE);
			Assert::IsFalse(rozgrywka6.Pozycja(444, 80) == CZARNE);
			Assert::IsTrue(rozgrywka7.Pozycja(20, 20) == CZARNE);

			try
			{
				Plansza rozgrywka10(10, true);
				rozgrywka10.UstawSymbol(0, 0, CZARNE);
			}
			catch (const std::invalid_argument&)
			{
				Assert::IsTrue(true);
			}

			try
			{
				Plansza rozgrywka11(10, true);
				rozgrywka11.UstawSymbol(4, 5, BIALE);
			}
			catch (const std::invalid_argument&)
			{
				Assert::IsTrue(true);
			}

		}

		TEST_METHOD(METODA_CZY_KONIEC_GRY)
		{
			Plansza rozgrywka(6, true);

			rozgrywka.UstawSymbol(1, 1, CZARNE);
			rozgrywka.UstawSymbol(1, 2, CZARNE);
			rozgrywka.UstawSymbol(1, 3, BIALE);
			rozgrywka.UstawSymbol(1, 4, CZARNE);
			rozgrywka.UstawSymbol(2, 1, BIALE);
			rozgrywka.UstawSymbol(2, 4, CZARNE);
			rozgrywka.UstawSymbol(3, 1, CZARNE);
			rozgrywka.UstawSymbol(3, 4, CZARNE);
			rozgrywka.UstawSymbol(4, 1, BIALE);
			rozgrywka.UstawSymbol(4, 2, BIALE);
			rozgrywka.UstawSymbol(4, 3, CZARNE);
			rozgrywka.UstawSymbol(4, 4, BIALE);

			Assert::IsTrue(rozgrywka.CzyKoniecGry(&rozgrywka));

			Plansza rozgrywka2(6, true);

			rozgrywka2.UstawSymbol(1, 1, CZARNE);
			rozgrywka2.UstawSymbol(1, 2, CZARNE);
			rozgrywka2.UstawSymbol(1, 4, CZARNE);
			rozgrywka2.UstawSymbol(2, 4, BIALE);
			rozgrywka2.UstawSymbol(3, 1, CZARNE);
			rozgrywka2.UstawSymbol(3, 4, CZARNE);
			rozgrywka2.UstawSymbol(4, 1, BIALE);
			rozgrywka2.UstawSymbol(4, 2, BIALE);

			Assert::IsFalse(rozgrywka2.CzyKoniecGry(&rozgrywka2));

			Plansza rozgrywka3(6, true);

			rozgrywka3.UstawSymbol(1, 1, CZARNE);
			rozgrywka3.UstawSymbol(1, 2, CZARNE);
			rozgrywka3.UstawSymbol(1, 4, CZARNE);
			rozgrywka3.UstawSymbol(2, 1, CZARNE);
			rozgrywka3.UstawSymbol(2, 4, CZARNE);
			rozgrywka3.UstawSymbol(3, 1, CZARNE);
			rozgrywka3.UstawSymbol(3, 4, CZARNE);
			rozgrywka3.UstawSymbol(4, 1, CZARNE);
			rozgrywka3.UstawSymbol(4, 2, CZARNE);
			rozgrywka3.UstawSymbol(4, 3, CZARNE);
			rozgrywka3.UstawSymbol(4, 4, CZARNE);

			Assert::IsTrue(rozgrywka3.CzyKoniecGry(&rozgrywka3));
		}

		TEST_METHOD(KONSTRUKTOR_CZLOWIEK)
		{
			Plansza p(10, true);

			gracz* g1 = new czlowiek(CZARNE, &p);
			gracz* g2 = new czlowiek(BIALE, &p);

			Assert::IsTrue(g1 != NULL);
			Assert::IsTrue(g1->PobierzSymbol() == CZARNE);
			Assert::IsTrue(g1->PobierzPlansze() == &p);

			Assert::IsTrue(g2 != NULL);
			Assert::IsTrue(g2->PobierzSymbol() == BIALE);
			Assert::IsTrue(g2->PobierzPlansze() == &p);

			delete g1;
			delete g2;
		}

		TEST_METHOD(KONSTRUKTOR_KOMPUTER)
		{
			Plansza p(10, true);
			Plansza p2(8, true);

			gracz* g1 = new komputer(CZARNE, &p);
			gracz* g2 = new komputer(BIALE, &p2);

			Assert::IsTrue(g1 != NULL);
			Assert::IsTrue(g1->PobierzSymbol() == CZARNE);
			Assert::IsTrue(g1->PobierzPlansze() == &p);

			Assert::IsTrue(g2 != NULL);
			Assert::IsTrue(g2->PobierzSymbol() == BIALE);
			Assert::IsTrue(g2->PobierzPlansze() == &p2);

			delete g1;
			delete g2;
		}

		TEST_METHOD(METODA_KOMPUTER_RUCH)
		{
			Plansza p(10, true);
			Plansza p2(8, true);
			gracz* g1 = new komputer(CZARNE, &p);
			gracz* g2 = new komputer(BIALE, &p2);

			//Dla gracza g1

			for (int i = 0; i < p.PobierzRozmiar(); i++)
			{
				for (int j = 0; j < p.PobierzRozmiar(); j++)
				{
					Assert::IsTrue(p.Pozycja(p.PobierzRozmiar() / 2 - 1, p.PobierzRozmiar() / 2 - 1) == BIALE);
					Assert::IsTrue(p.Pozycja(p.PobierzRozmiar() / 2 - 1, p.PobierzRozmiar() / 2) == CZARNE);
					Assert::IsTrue(p.Pozycja(p.PobierzRozmiar() / 2, p.PobierzRozmiar() / 2 - 1) == CZARNE);
					Assert::IsTrue(p.Pozycja(p.PobierzRozmiar() / 2, p.PobierzRozmiar() / 2) == BIALE);
				}
			}

			g1->ruch(&p);

			bool ruchWykonany = false;

			for (int i = 0; i < p.PobierzRozmiar(); i++)
			{
				for (int j = 0; j < p.PobierzRozmiar(); j++)
				{
					if (p.Pozycja(i, j) == CZARNE)
					{
						ruchWykonany = true;
						break;
					}
				}
				if (ruchWykonany) break;
			}

			Assert::IsTrue(ruchWykonany);

			// Dla gracza g2

			for (int i = 0; i < p2.PobierzRozmiar(); i++)
			{
				for (int j = 0; j < p2.PobierzRozmiar(); j++)
				{
					Assert::IsTrue(p2.Pozycja(p2.PobierzRozmiar() / 2 - 1, p2.PobierzRozmiar() / 2 - 1) == BIALE);
					Assert::IsTrue(p2.Pozycja(p2.PobierzRozmiar() / 2 - 1, p2.PobierzRozmiar() / 2) == CZARNE);
					Assert::IsTrue(p2.Pozycja(p2.PobierzRozmiar() / 2, p2.PobierzRozmiar() / 2 - 1) == CZARNE);
					Assert::IsTrue(p2.Pozycja(p2.PobierzRozmiar() / 2, p2.PobierzRozmiar() / 2) == BIALE);
				}
			}

			g2->ruch(&p2);

			bool ruchWykonany2 = false;

			for (int i = 0; i < p2.PobierzRozmiar(); i++)
			{
				for (int j = 0; j < p2.PobierzRozmiar(); j++)
				{
					if (p2.Pozycja(i, j) == BIALE)
					{
						ruchWykonany2 = true;
						break;
					}
				}
				if (ruchWykonany2) break;
			}

			Assert::IsTrue(ruchWykonany2);
		}

		TEST_METHOD(METODA_CZY_WYGRANA)
		{
			Plansza p(6, true);

			gracz* g1 = new czlowiek(CZARNE, &p);

			p.UstawSymbol(1, 1, CZARNE);
			p.UstawSymbol(4, 4, CZARNE);
			p.UstawSymbol(3, 4, BIALE);
			p.UstawSymbol(4, 1, CZARNE);
			p.UstawSymbol(1, 2, BIALE);

			Assert::IsTrue(p.CzyWygrana(CZARNE, 4, 4));
			Assert::IsFalse(p.CzyWygrana(BIALE, 2, 2));

			delete g1;

			Plansza p2(6, true);

			gracz* g2 = new komputer(BIALE, &p2);

			p2.UstawSymbol(1, 1, BIALE);
			p2.UstawSymbol(4, 4, BIALE);
			p2.UstawSymbol(3, 4, BIALE);
			p2.UstawSymbol(4, 1, BIALE);
			p2.UstawSymbol(1, 2, CZARNE);

			Assert::IsTrue(p2.CzyWygrana(BIALE, 4, 4));
			Assert::IsFalse(p2.CzyWygrana(CZARNE, 2, 2));

			delete g2;
		}
	};
}
